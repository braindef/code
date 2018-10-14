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
#include <iostream.h>										// by the way
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

LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	switch(msg)
	{	
		case WM_CREATE: 
		{
			// Initialisation
			return(0);
		} break;
        

		case WM_DESTROY: 
		{		
			PostQuitMessage(0);
			return(0);
		} break;

		default:break;
	} 

	return (DefWindowProc(hwnd, msg, wparam, lparam));
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
#include <d3d8.h>										// Headerdatei fuer Direct3D
#include <d3dx8.h>										// Eine in D3D integrierte Hilfsbibliothek

// Ein paar nützliche Defines
#define SCREEN_WIDTH			800
#define SCREEN_HEIGHT			600
#define SCREEN_BPP				16						// Bits Per Pixel

// Tasturabfrage
#define KEY_DOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// D3D Globals
LPDIRECT3D8					lpD3D = NULL;				// Direct3D Hauptobjekt
LPDIRECT3DDEVICE8			lpD3DDevice = NULL;			// Device
D3DDISPLAYMODE				d3ddm;						// Display Mode
D3DPRESENT_PARAMETERS		d3dpp;						// Anzeige Eigenschafen
D3DCAPS8 d3dcaps;										// Caps - welche Möglichkeiten bietet uns die Hardware?

LPDIRECT3DTEXTURE8          lpSprite = NULL;			// Stoppt den Mißbrauch von Texturen als Sprites ;)
LPDIRECT3DVERTEXBUFFER8     lpVBSprite = NULL;			// VertexBuffer fuer das Sprite


#define D3DFVF_VERTEX2D (D3DFVF_XYZ|D3DFVF_TEX1)		// FVF

// Vertex Stucktur fuer die Sprites
struct VERTEX2D
{
	float x, y, z;
	float u, v;
};

#define SPRITE_WIDTH		69.0f						// Sprite Breite
#define SPRITE_HEIGHT		110.0f						// Sprite Höhe

D3DXMATRIX matProj;										// Projektionsmatrix

// Die Vertices des Sprites
VERTEX2D sprite_vertices[] = 
{
	{-SPRITE_WIDTH/2,SPRITE_HEIGHT/2,0.0f,0.0f,0.0f,},
	{-SPRITE_WIDTH/2,-SPRITE_HEIGHT/2,0.0f,0.0f,SPRITE_HEIGHT/256,},
	{SPRITE_WIDTH/2,SPRITE_HEIGHT/2,0.0f,SPRITE_WIDTH/256,0.0f,},
	{SPRITE_WIDTH/2,-SPRITE_HEIGHT/2,0.0f,SPRITE_WIDTH/256,SPRITE_HEIGHT/256,},
}; 


/*
 *	GameInit
 */


bool Game_Init(void)
{
	lpD3D = Direct3DCreate8(D3D_SDK_VERSION);

	if(lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)!=D3D_OK)
		return FALSE;

	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferCount = 1;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.hDeviceWindow = main_window_handle;

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

	// Setzen der Projektionsmatrix (Orthogonal = Senkrecht = Draufsicht)
	D3DXMatrixOrthoLH(&matProj, 800, 600, 0, 1);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

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

	// Liefert DviceCaps, falls die Hardware HAL unterstützt - ansonsten wird etwas ungleich D3D_OK zurückgegeben
	lpD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps);

	// Aktiviert Alphablending und setzt die Eigenschaften des Alphablendings - wir benutzen es als Art Colorkey
	if(lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE)!=D3D_OK)
		return FALSE;

	if(lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA)!=D3D_OK)
		return FALSE;
	 
	if(lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA)!=D3D_OK)
		return FALSE;

	if(d3dcaps.AlphaCmpCaps & D3DPCMPCAPS_GREATER)
	{
		if(lpD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER)!=D3D_OK)
			return FALSE;

		if(lpD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000000)!=D3D_OK)
			return FALSE;

		if(lpD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE)!=D3D_OK)
			return FALSE;
	}

	D3DXCreateTextureFromFileExA(lpD3DDevice, "joe256.bmp", D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 
		                         D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255,0,255), 
								 NULL, NULL, &lpSprite);

	VOID *lpVertices;
	if(lpD3DDevice->CreateVertexBuffer(sizeof(sprite_vertices), 0, D3DFVF_VERTEX2D, D3DPOOL_DEFAULT, &lpVBSprite)!=D3D_OK)
		return FALSE;

	// Füllt den VertexBuffern mit den Vertices unseres Sprites
	lpVBSprite->Lock(0, sizeof(sprite_vertices), (BYTE**)&lpVertices, 0);

	memcpy(lpVertices, sprite_vertices, sizeof(sprite_vertices));

	lpVBSprite->Unlock();

	return 1;
}


/*
 *	GameMain
 */

bool Game_Main(void)
{
	if(KEY_DOWN(VK_ESCAPE))
		PostMessage(main_window_handle, WM_DESTROY,0,0);

	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 100, 0), 1.0f, 0);
	lpD3DDevice->BeginScene();

	lpD3DDevice->SetTexture(0, lpSprite);
	lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTA_TEXTURE);

	lpD3DDevice->SetVertexShader(D3DFVF_VERTEX2D);
	lpD3DDevice->SetStreamSource(0, lpVBSprite, sizeof(VERTEX2D));
	lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	lpD3DDevice->EndScene();
	lpD3DDevice->Present(NULL, NULL, NULL, NULL);

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

	if(lpVBSprite!=NULL)
		lpVBSprite->Release();

	if(lpD3DDevice!=NULL)
		lpD3DDevice->Release();

	if(lpD3D!=NULL)
		lpD3D->Release();
}

