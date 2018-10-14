#include "GDef.h"
#include "Utilities.h"
#include "D3d.h"
#include "Text.h"
#include <d3dx9tex.h>


LPDIRECT3DSURFACE9 textbitmap;
char* text;		//ein Zeiger, der genrell allen Text speichert, der am Bildschirm erscheinen soll"
int* textcolor;	//die Farbe jedes Zeichens, das im text Zeiger steht
int textlen;	//die Summe aller Zeichen die wir zeichenen müssen
int textw,texth;//relative Höhe und Breite jedes Zeichens in dem
int* tsign[256];//gewaltigen Zeiger in dem die Bildinfo jedes zeichens abgelegt wir
int tsignc[256];//Zeiger des die Anzahl der Pixel jedes Zeichens von tsign speichert


int g_InitText (void)
{
	int r = 0;
	HDC pdc;
	RECT rect;
	char si = 0;
	D3DLOCKED_RECT pr,prr;
	char* p;

	textw = 15;
	texth = 18;

	//erstellen eines Surfaces in DirectX9: dürfte nicht weiter verwirrend sein, oder?)
	r = De->CreateOffscreenPlainSurface(256*textw, texth, D3DFMT_R5G6B5, D3DPOOL_SYSTEMMEM, &textbitmap, NULL);
		if (FAILED(r)) g_FailBox(1,"Failed to create Offscreen Surface for Textmap!");

	//Wir holen und eine HDC, also einen Device-Handel des Surfaces ab, so dass wir mit der WINAPI in das Surface zeichenen können
	r = textbitmap->GetDC(&pdc);
		if (FAILED(r)) g_FailBox(1,"Failed to get Surface DC!");

	//Generell: schwarz auf weiss
	SetTextColor(pdc,0x00ffffff);
	SetBkColor(pdc,0x00000000);

	//Schleife, die die Zeichen hintereinander in das Surface schreibt
	for(int i = 0; i < 256; i++)
	{
		rect.left = i*textw;
		rect.top = 0;
		rect.bottom = texth;
		rect.right = i*textw + textw;
		r = DrawText(pdc, &si, 1, &rect, DT_BOTTOM | DT_CENTER);
		si++;
	}

	textbitmap->ReleaseDC(pdc);

	//Abholen eines Zeigers auf den Speicher des Sufraces, in dem jetzt unsere Zeichen stehen
	textbitmap->LockRect(&pr,NULL,NULL);

	//p ist nun dieser Zeiger
	p = (char*)pr.pBits;

	//Das backbuffer Surface, stellt dann einfach unseren Backbuffer dar
	//Wir müssen ihn nur einmal locken, um dessen Pitch (also Anzahl der Pixel pro Zeile) zu erhalten
	LPDIRECT3DSURFACE9 backbuffer;
	De->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	backbuffer->LockRect(&prr,NULL,NULL);
	backbuffer->UnlockRect();

	//Die mega-Schleife, die die Info des Surfaces zu unseren gunsten umbaut
	//Zeichen für Zeichen durchegehen...
	for(int i = 0; i < 256; i++)
	{
		int c = 0;
		int s = 0;
		//Zunächst einmal zählen wir durch wieviele Pixel denn zu malen sind und speichern diese Zahl in c
		for(int x = 0; x < textw; x++)
		{
			for(int y = 0; y < texth; y++)
			{
				if(*(short*)(p + i*textw*2 + y*pr.Pitch + x*2) != 0) c++;
			}
		}
		//Das können wir für später auch gleich mal Speichern
		tsignc[i] = c;
		//Und so können wir dann auch für jedes Zeichen in tsign eben gerade genug Speicher belegen und verwenden
		tsign[i] = new int[tsignc[i]];
		//Jetzt nochmal die Doppelschleife, die alle Pixel des momentanen Zeichens durcheght
		for(int x = 0; x < textw; x++)
		{
			for(int y = 0; y < texth; y++)
			{
				//heisst so viel wie: Falls Pixel dann
				if(*(short*)(p + i*textw*2 + y*pr.Pitch + x*2) != 0)
				{
					//Speichere Momentane relative Speicherposition (allerdings mit der Pitch des Backbuffers!!!) für jeden Pixel
					//nach und nach in tsign ab
					tsign[i][s] = y*prr.Pitch + x*2;
					//s ist also der Zähler für die Anzahl der Pixel eines jeden Zeichens
					s++;
				}
			}
		}
	}

	//Das surface für die Zeichen können wir wieder vernichten!
	textbitmap->UnlockRect();
	textbitmap->Release();
	textbitmap = NULL;



	//Und zum Schluss initialisieren wir nur noch unsere Zischenspeicher für Text und dessen Farbe
	text = new char[4096];
	ZeroMemory(text, 4096);
	textcolor = new int[4096];
	ZeroMemory(textcolor, 4096*4);

	textlen = 0;

	return OK;
}


//Schreibt einen Text in den Zischenspeicher text mit der Farbe color
int g_PrintText(int color, const char* list,...)
{
	va_list valist;
	char* ntext;
	int otext = textlen;

	ntext = new char[strlen(list) + 256];

	//Das übliche Spiel mit der Argumentlist... (sollte ja von den vorigen Tutoials schon bekannt sein
	va_start(valist,list);
	vsprintf(ntext,list,valist);
	va_end(valist);

	//Und dann nur noch in text an die richtige Stelle kopieren
	memcpy((void*)(text + textlen), ntext, strlen(ntext));
	
	//und den Refernez-Zeichen-Zähler textlen um die Anzahl der zu schreibenden Zeichen erhöhen
	textlen += strlen(ntext);

	for(int i = otext; i < textlen ; i++) textcolor[i] = color;

	free(ntext);

	return OK;
}


//Funktion zum Zeichnen eines Textes an einer best. Position
int g_DrawText(int color, int x, int y, const char* list,...)
{
	//Vorneweg sinnlose Fälle auschließen!!
	if( x < 0 || y < 0 || x > 800 || y > 600) return OK;
	//Folgende Zeilen sollten ja schon von weiter oben oder unten ziemlich klar sein
	va_list valist;
	char* ntext;
	int textl = strlen(list);

	ntext = new char[strlen(list) + 256];

	va_start(valist,list);
	vsprintf(ntext,list,valist);
	va_end(valist);

	//Wieder Locken usw...
	int col = 0; 
	LPDIRECT3DSURFACE9 backbuffer; 
	D3DLOCKED_RECT pr; 

	De->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	backbuffer->LockRect(&pr,NULL,NULL);

	//Diesesmal berücksichtigen wir keine Zeilensprünge aber dafür relative x und y Position des Textes
	int re = (int)((x << 1) + pr.Pitch * y + (char*)(pr.pBits));
	int rx = textw << 1;
	int rs = 1600 - (x << 1);
	
	//Ansonsten sieht die Schleife ziemlich gleich aus
	for(int i = 0; i < textl; i++)
	{
		//Dieses mal ohne row (da keine Zeilensprünge) und nur mit einer relativen Anfangsposition (re)
		int offs = (int)(col * rx);

		//Beenden wenn wir aus dem Bildschirm zeichnen!!
		if(offs > rs) continue;

		//N bisschen verschoben, weils vielleicht der Performance hilft!
		offs += re;

		//Das ist das selbe wie beim vorigem mal
		for(int j = 0; j < tsignc[*(ntext + i)]; j++)
		{
			*(short int*)(tsign[*(ntext + i)][j] + offs) = color;
		}

		col++;
	}

	backbuffer->UnlockRect();

	free(ntext);

	return OK;
}


//Funktion zum Zeichnen eines MouseCursors (Warum beim Text?: Hat wohl minimal am meisten damit zu tun!)
int g_DrawCursor(int p,int x,int y)
{
	if( x < 9 || y < 9 || x > 791 || y > 591) return OK;

	//Der übliche Lock zeug um an Pointer und Pitch zu gelangen
	LPDIRECT3DSURFACE9 backbuffer; 
	D3DLOCKED_RECT pr; 

	De->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	backbuffer->LockRect(&pr,NULL,NULL);

	char* rp = (char*)(pr.pBits) + (x << 1) + y * pr.Pitch;

	//Zeichnet nichts anderes als ein Fadenkreuz!
	for (int i = -9; i < 10 ; i++)
	{
		*(short int*)(rp + (i << 1)) = 0xffff;
		*(short int*)(rp + (i * pr.Pitch)) = 0xffff;
	}

	backbuffer->UnlockRect();

	return OK;
}


//Funktion die während der laufzeit des Programms den Text Zeichen für Zeichen und pixel für Pixel in den Backbuffer schreibt
int g_DrawCompleteText (void)
{
	int row = 0; //Anzahl der Zeilen
	int col = 0; //Anzahl der Spalten
	LPDIRECT3DSURFACE9 backbuffer; //Ein Surface für unseren Backbuffer
	D3DLOCKED_RECT pr; //Eben das Ding das wir brauchen um an einen Zeiger auf den Backbuffer zu gelangen

	//Backbuffer "abfragen"
	De->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	//Zeiger abholen
	backbuffer->LockRect(&pr,NULL,NULL);

	int ry = pr.Pitch * texth;
	int rx = textw << 1;
	
	//und los gehts: den ganzen Zwischenspeicher text durch (es stehen ja textlen Zeichen darin!)
	for(int i = 0; i < textlen; i++)
	{
		//Den Generellen Offset des Zeichens berechnen, also im Bezug auf Reihen und Spalten 
		//unter Berücksichtigung aller Pitches und Auflösungen, usw.
		int offs = (int)(col * rx + row * ry + (char*)(pr.pBits));
		if (*(text + i) == '\n' || col > 100)
		{
			row++;
			col = 0;
			continue;
		}

		//Dann einfach unser tsign des entsprechenden Zeichens runterratern und überall, wo 
		//unsere relativ gespeicherte Offset-Info hinzeigt, die Farbe color in den Backbuffer ablegen
		//also eine Pixel mit der Farbe color mahlen
		for(int j = 0; j < tsignc[*(text + i)]; j++)
		{
			*(short int*)(tsign[*(text + i)][j] + offs) = textcolor[i];
		}

		col++;
	}

	//Wieder der Abschlusskram!
	backbuffer->UnlockRect();

	//Das darf man auf keinen Fall vergessen!!
	textlen = 0;
	
	return OK;
}
		


