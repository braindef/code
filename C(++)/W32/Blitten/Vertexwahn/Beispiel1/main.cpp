//////////////////////////////////////////////////////////////////////////////////////////
// GRUNDGERUEST //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*
	Hier ist der Code für das Grundgeruest auf dem unsere Anwendung basiert
 */

/*
 *	Header-Dateien
 */

// Standard Header-Dateien
#define WIN32_LEAN_AND_MEAN									// say no to mfc
#include <windows.h>										// oh my god
#include <iostream>										    // by the way
#include <stdio.h>											// I/O


/*
 *	Defines
 */


#define WINDOW_CLASS_NAME		"WINCLASS1"					// Fensterklassenname
#define WINDOW_TITLE			"Tutorial_Beispiel1"		// Fenstertitel	
#define WINDOW_X				0							// x	
#define WINDOW_Y				0							// y


/*
 *	Globals
 */

HWND main_window_handle = NULL;								// Fenster-Handle
HINSTANCE main_instance = NULL;								// Main Instanz


/*
 *	Prototypen
 */

bool Game_Init(void);										// Initialisation
bool Game_Main(void);										// Main Game Loop
void Game_Shutdown(void);									// Reinitialisation - ein schönes Wort ;)


/*
 *	WinProc
 */

LRESULT CALLBACK WindowProc(HWND hWnd, 
						    UINT msg, 
                            WPARAM wParam, 
                            LPARAM lParam)
{
	switch(msg)
	{	
		case WM_CREATE: 
		{
			// Initialisation
			return(0);
		} break;
        
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) PostQuitMessage ( 0 );
			break;

		case WM_DESTROY: 
		{		
			PostQuitMessage(0);
			return(0);
		} break;

		default:break;
	} 

	return (DefWindowProc(hWnd, msg, wParam, lParam));
}


/*
 *	WinMain
 */

int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{
	WNDCLASS winclass;							// Fensterklasse
	HWND	 hWnd;								// Fenster-Handle
	MSG		 msg;								// Message-Handler

	// Fensterklasse einrichten
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
		                      CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= WINDOW_CLASS_NAME;

	// Fensterklasse anmelden
	if(!RegisterClass(&winclass))
		return(0);

	// Hauptfenster wird erstellt
	if(!(hWnd = CreateWindow(WINDOW_CLASS_NAME,								// Fensterklasse
							 WINDOW_TITLE,									// Fenstertitel
							 WS_POPUP | WS_VISIBLE,
						 	 WINDOW_X,WINDOW_Y,								// x,y
							 GetSystemMetrics(SM_CXSCREEN),					// Breite
							 GetSystemMetrics(SM_CYSCREEN),					// Höhe
							 NULL,
							 NULL,
							 hinstance,		
							 NULL)))
		return(0);

	main_window_handle = hWnd;	// Globaler Fenster-Handle
	main_instance = hinstance;

	if(Game_Init()==0)
		return 0;

	// Main Event Loop
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
	        if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}    
		
		if(Game_Main()==0)
			return 0;
	} 

	Game_Shutdown();

	return(msg.wParam);
}

//////////////////////////////////////////////////////////////////////////////////////////
// GRUNDGERUEST - ENDE ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*
	Oben wird nur ein Fenster erzeugt - hier folgt der wesentliche Code
 */

// Direct3D Headerdateien
#include <d3d8.h>								// Headerdatei fuer Direct3D
#include <d3dx8.h>								// Eine in D3D integrierte Hilfsbibliothek

// Ein paar nützliche Defines
#define SCREEN_WIDTH			800             // Aufloesung Breite
#define SCREEN_HEIGHT			600             // Aufloesung Hoehe
#define SCREEN_BPP				32              // Bits Per Pixel, Farbtiefe

// Tasturabfrage
#define KEY_DOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)	

// D3D Globals
LPDIRECT3D8						lpD3D = NULL;				// Direct3D Hauptobjekt
LPDIRECT3DDEVICE8				lpD3DDevice = NULL;			// Device Objekt 
D3DDISPLAYMODE					d3ddm;						// Display Mode
D3DPRESENT_PARAMETERS	        d3dpp;						// Anzeige Eigenschafen 


LPDIRECT3DSURFACE8				lpBackbuffer = NULL;		// Backbuffer
LPDIRECT3DSURFACE8				lpSprite = NULL;			// Surface für ein Sprite

POINT SpritePosition;										// Position des Sprites
RECT rcSprite;												// Ein Rect fuer das Sprite

bool first=true;



/*
 *	GameInit
 */


bool Game_Init(void)
{

	if((lpD3D = Direct3DCreate8(D3D_SDK_VERSION))==NULL)
		return FALSE;
	
	// Fuellt die d3ddm Struktur, die uns u. a. Informationen über den Speicheraufbau der Grafikkarte liefert
	if(lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)!=D3D_OK)
		return FALSE;

	memset(&d3dpp, 0, sizeof(d3dpp));


	d3dpp.Windowed = FALSE;							// Vollbild = TRUE
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;			// Flippen
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;      //Sympathisches Format  
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferCount = 1;						// Dopplebuffering
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.hDeviceWindow = main_window_handle;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;	//Damit der backbuffer gelockt werden kann
	
	// Unterstuetzt das Device HAL?
	if(lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format, d3ddm.Format, FALSE)==D3D_OK)
	{
			if(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, main_window_handle,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)!=D3D_OK)
						return FALSE;  
	}
    else
	{
			if(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF , main_window_handle,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)!=D3D_OK)
						return FALSE;  
	}

	// Kein Culling
	if(lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)!=D3D_OK)
		return FALSE;

	// Kein Lighting
	if(lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE)!=D3D_OK)
		return FALSE;

	// Kein Z-Buffer
	if(lpD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE)!=D3D_OK)
		return FALSE;

	if(lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE)!=D3D_OK)
		return FALSE;

	// Backbuffer übernehmen
	if(lpD3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &lpBackbuffer)!=D3D_OK)
		return FALSE;

	

	// Erzeugt das Surface fuer das Sprite
	lpD3DDevice->CreateImageSurface(100, 100, D3DFMT_A8R8G8B8, &lpSprite);
	
	// Bitmap wird aus Datei geladen
	D3DXLoadSurfaceFromFile(lpSprite, NULL, NULL, "test.bmp", NULL, D3DX_FILTER_POINT, 0, NULL);



	
	D3DLOCKED_RECT rcLocked;

	lpBackbuffer->LockRect(&rcLocked, NULL, 0);
	
	unsigned int pitch = rcLocked.Pitch>>2;
    DWORD *color = (DWORD *)rcLocked.pBits;

    for (DWORD y = 0; y < 300; y++)
    {
        for (DWORD x = 0; x < 300; x++)
        {
            color[((y+100)*pitch +x+100) ]=0x33ffffaa;
        }
    }

    lpBackbuffer->UnlockRect();

	
	//int a = 0, r = 0, g = 0, b = 0;
	//GetBitsForFormat(Format,&a,&r,&g,&b);

	// Position des Sprites
	SpritePosition.x = 300;
	SpritePosition.y = 300;

	// Rect Struktur wird gefuelt
	rcSprite.left = 0;
	rcSprite.top = 0;
	rcSprite.right = 100;
	rcSprite.bottom = 100;

	return 1;
}

/*
 *	GameMain
 */

bool Game_Main(void)
{
	// Wurde die Escape-Taste gedrueckt?
	//if(KEY_DOWN(VK_ESCAPE))
	//	PostMessage(main_window_handle, WM_DESTROY,0,0);
	
	// Loescht den Backbuffer
	//if(lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0)!=D3D_OK)
	//	return FALSE;

	// Blitten
	if(lpD3DDevice->CopyRects(lpSprite, &rcSprite, 1, lpBackbuffer, &SpritePosition)!=D3D_OK)
		return FALSE;

	// Zeigt das Bild an
	if (first)
	{
		if(lpD3DDevice->Present(NULL, NULL, NULL, NULL)!=D3D_OK)
		return FALSE;
	}
	first=false;
		
	return 1;
}


/*
 *	GameShutdown
 */

void Game_Shutdown(void)
{
	// Bevor das Programm beendet wird, wird schnell noch Aufgeraeumt
	if(lpSprite!=NULL)
		lpSprite->Release();

	if(lpBackbuffer!=NULL)
		lpBackbuffer->Release();

	if(lpD3DDevice!=NULL)
		lpD3DDevice->Release();

	if(lpD3D!=NULL)
		lpD3D->Release();
}