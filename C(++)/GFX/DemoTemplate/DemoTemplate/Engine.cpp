// Dies ist eine Vorlage für DirectX9 Fenster

#include "Engine.h"
#include "SurfaceDisplay.h"



//Wenn man eine Variable in einer Klasse als static deklarierst, dann muss man die entsprechende Variable auch in der zur Klasse zugehörigen .cpp-Datei anlegen.
LPDIRECT3D9				landev::Engine::MyDx9Interface = NULL;
LPDIRECT3DDEVICE9		landev::Engine::MyRenderingDevice = NULL;

bool					landev::Engine::active=true;
int						landev::Engine::StartTime=0;
int						landev::Engine::lastTime=0;

MSG msg;

HWND hWnd=NULL;

const bool debug=false;							//const, da ein guter Compiler so bei debug=false eine if (debug) anweisung gar nicht kompiliert

const int ScreenWidth=1024;
const int ScreenHeight=768;

// --------
// Methoden
// --------
HRESULT landev::Engine::ChangeToFullscreen(bool fullscreen)
{
	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
	dmScreenSettings.dmSize=sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth=ScreenWidth;
	dmScreenSettings.dmPelsHeight=ScreenHeight;
	dmScreenSettings.dmBitsPerPel=16;
	dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
	
	if (fullscreen) ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
	else ChangeDisplaySettings(NULL,0);
	
	if (fullscreen) ShowCursor(false);
	else ShowCursor(true);

	return S_OK;
}


HRESULT landev::Engine::InitD3D(HWND hWnd)
{
	StartTime = GetTickCount();																	//Speichern der Startzeit

	if ( (MyDx9Interface = Direct3DCreate9(D3D_SDK_VERSION)) == NULL ) return E_FAIL;				//Das Interface erstellen

	D3DPRESENT_PARAMETERS d3dpp;																//Parameter Struktur erstellen
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed=TRUE;
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;

	ChangeToFullscreen(true);

	if( S_OK==(MyDx9Interface->CreateDevice(D3DADAPTER_DEFAULT,									//Das Renderingdevice erstellen
											D3DDEVTYPE_HAL,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,				//D3DCREATE_HARDWARE_VERTEXPROCESSING unter xp lahm, allenfalls wegen meiner grafikkarte...
											&d3dpp,
											&MyRenderingDevice))) 
	{
		return S_OK;
	}
	else return E_FAIL;

	return S_OK;
}


void landev::Engine::Cleanup()
{
	if( MyRenderingDevice != NULL )       
		MyRenderingDevice->Release();

}


LPWSTR FPSString= new wchar_t[50];
int landev::Engine::ticks=0;

void landev::Engine::FPS()
{
	int tick=GetTickCount();
	int FPS;
	if(tick != landev::Engine::lastTime) FPS = 1000/(tick-landev::Engine::lastTime);
	
	
    ticks++;
	if(landev::Engine::ticks>50) 
	{
		ticks=0;
		wsprintf(FPSString, L"%d FPS", FPS);
	}
	
		HDC hDC=GetDC(hWnd);
		TextOut(hDC, ScreenWidth-70, 15, (LPCWSTR)FPSString, wcslen(FPSString));
		ReleaseDC(hWnd,hDC);
	
	landev::Engine::lastTime=GetTickCount();
}

void landev::Engine::Render()
{

	MyRenderingDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0 );					//Den Hintergrund Löschen

    if( S_OK==( MyRenderingDevice->BeginScene() ) )											//Szenen beginnen
    { 

		MyRenderingDevice->EndScene();
    }

	landev::SurfaceDisplay::RenderSurface();
    // Present the backbuffer contents to the display
    MyRenderingDevice->Present( NULL, NULL, NULL, NULL );
	
	FPS();
	

}





LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
			landev::Engine::Cleanup();
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) PostQuitMessage ( 0 );
			break;
		case WM_ACTIVATE:							// Wird der Zustand des Fensters geändert?
		{
			if (!HIWORD(wParam)) landev::Engine::active=TRUE;		// Minimierung überprüfen, wenn nicht minimiert active=true;
			
			else landev::Engine::active=FALSE;						// Programm nicht aktiv active=false;
		}
		break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}	// MsgProc




INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )	//Winmain ist die funktion, die nach dem Starten des Prozesses aufgerufen wird
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,							//Window-Klasse erstellen
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      L"MyWindow", NULL };
    RegisterClassEx( &wc );																		//Window-Klasse Registrieren

    hWnd = CreateWindow( L"MyWindow", (LPCWSTR)"Landev's DiretcX Template",			//Fenster erstellen
                              WS_OVERLAPPEDWINDOW, 0, 0, ScreenWidth, ScreenHeight,						//WS_POPUP für fenster ohne Rahmen --> fullscreen
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

	

	if( SUCCEEDED( landev::Engine::InitD3D( hWnd ) ) )															//Direct3D initialisieren
    {
		ShowWindow( hWnd, SW_SHOWDEFAULT );														//Fenster anzeigen
		UpdateWindow( hWnd );
		

		// Enter the message loop
		while( msg.message!=WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				if (landev::Engine::active) landev::Engine::Render();															//Gerendert wird nur, wenn das Fenster aktiv ist
				//if (active) computeModel();
				if (!landev::Engine::active) Sleep(500);														//sonst geben wir die CPU zurück an das System
			}
		}
    }
	else 
	{
		MessageBox(NULL, L"DirectX 9 Initialisation failed", L"Initialisation Failed", MB_OK | MB_ICONEXCLAMATION);
		return E_FAIL;
	}
    UnregisterClass( L"MyWindow", wc.hInstance );			//wobei das L long heist anstelle des castens mit (LPCWSTR)
	return 0;
}	// WinMain
