#include "GDef.h"
#include "Menue.h"
#include "Text.h"


//Funktion zum Initialisieren eines Men�s
void g_Menue::Init(char* nname)
{
	name = nname; //Name geben
	items = 0; //bis jetzt 0 Items

	start = NULL; //Zun�chst haben wir ja noch kein Item!
}


//Hinzuf�gen eines g_MenueItem Objekts zu einer Men�-Liste
int g_Menue::Add(char* ntext, void(*MFunc)(void))
{
	//Falls wir das erste Item hinzuf�gren (also wenn der start Zeiger gliech NULL ist)
	if(start == NULL)
	{
		start = new g_MenueItem; //neues item
		start->text = ntext; //Werte und texte des Men�punktes setzen
		start->sx = 200;
		start->sy = 200;
		start->bx = 200 + strlen(start->text)*textw;
		start->by = 200 + texth;
		start->MenueFunc = MFunc; //Auch die Funktion die ausgef�hrt werden soll muss gesetzt werden
		start->next = NULL; //Momentan steht nach start nichts, also der Zeiger auf das n�chste Objekt = NULL
		items++; //den Item-Z�hler erh�h�n

		return OK; //dann sofort die Funktion beenden
	}

	//Falls wir schon das erste Item in der Liste habe, am Ende der Liste ein Objekt einf�gen:
	g_MenueItem* neu = new g_MenueItem; //neues g_MenueItem Objekt erzeugen 
	neu->text = ntext; //Werte setzen...
	neu->sx = 200;
	neu->sy = 200 + texth * items;
	neu->bx = 200 + strlen(start->text)*textw;
	neu->by = 200 + texth * (items + 1);
	neu->MenueFunc = MFunc;
	neu->next = NULL; //Da wir am Ende einf�gen, muss das neue Objekt als n�chstes Objekt NULL haben!
	//Mit dieser schleife gehen wir vom ersten bis zum bis jetzt noch letzten Objekt durch
	//Dabei initialisieren wir ein g_MenueItem* Objekt (cur) auf start und gehen dann durch cur = cur->next
	//Item f�r Item der Liste durch, bis cur = NULL wird (d.h. solange wie cur != NULL)
	for(g_MenueItem* cur = start; cur != NULL; cur = cur->next)
	{
		//Falls cur->next == NULL ist, muss es sich um das letzte item der momentanen Liste handeln 
		if (cur->next == NULL)
		{
			//Dann m�ssen wir diesen cur->nect Zeiger aber weg von NULL auf unser neues frisch einzuf�gendes
			//Objekt (neu) setzen damit es dann endg�ltig in der Liste ist
			cur->next = neu;
			//Dann aber sofort die Schleife beenden
			break;
		}
	}
	items++;//Wieder den Z�hler erh�hen

	return OK;
}


//Funktion zum Zeichnen des Men�s
//x und y stellen dabei die Maus-Position dar, die als Parameter �bergeben werden kann
int g_Menue::DrawMenue(int x, int y)
{
	int i = 0;

	//Die �berschrift des Men�s zeichnen
	g_DrawText(0xfe00,260,150,name);

	//Wie oben die Men�-Linked-List durchgehen (dabie auch gleich noch i erh�hen)
	for(g_MenueItem* cur = start; cur != NULL; cur = cur->next, i++)
	{
		//Falls die Maus �ber unserem Men�punkt liegt, diesen in einer anderen Farbe zeichnen!
		if (x > cur->sx && x < cur->bx && y > cur->sy && y < cur->by)
		{
			g_DrawText(0x000f,250,200 + i* (texth+2),cur->text);
		}else
		{
			//Ansonsten in normaler r�tlicher Farbe zeichnen
			g_DrawText(0xfe00,250,200 + i* (texth+2),cur->text);
		}
	}
	
	return OK;
}


//Funktion die die jeweilige Funktion ausf�hrt, Falls x und y innerhalb unserer Men�punkt-Fl�che liegen
int g_Menue::ExecMenue(int x, int y)
{
	//Wie oben Liste durchgehen
	for(g_MenueItem* cur = start; cur != NULL; cur = cur->next)
	{
		//und falls wir mit x und y �ber dem Men�punkt liegen
		if (x > cur->sx && x < cur->bx && y > cur->sy && y < cur->by)
		{
			//die jeweilige Men�punktfunktion ausf�hren
			cur->MenueFunc();
		}
	}
	return OK;
}


//Funktion zur R�ckgabe von items
int g_Menue::GetItems(void){return items;}


