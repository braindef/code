// Dies ist eine Vorlage für DirectX9 Fenster

#include "DX9Window.h"

#include <d3d9.h>

LPDIRECT3D9             MyDx9Interface			= NULL;
LPDIRECT3DDEVICE9		MyRenderingDevice		= NULL;

MSG msg;

const int ScreenWidth=640;
const int ScreenHeight=480;
int StartTime=0;
bool active=true;
bool init=true;


// --------
// Methoden
// --------
HRESULT ChangeToFullscreen(bool fullscreen)
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


HRESULT InitD3D(HWND hWnd)
{
	StartTime = GetTickCount();																	//Speichern der Startzeit

	if ( (MyDx9Interface=Direct3DCreate9(D3D_SDK_VERSION)) == NULL ) return E_FAIL;				//Das Interface erstellen

	D3DPRESENT_PARAMETERS d3dpp;																//Parameter Struktur erstellen
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed=TRUE;
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;

	if( S_OK==(MyDx9Interface->CreateDevice(D3DADAPTER_DEFAULT,									//Das Renderingdevice erstellen
											D3DDEVTYPE_HAL,
											hWnd,
											D3DCREATE_HARDWARE_VERTEXPROCESSING,
											&d3dpp,
											&MyRenderingDevice))) 
	{
		return S_OK;
	}
	else return E_FAIL;

	return S_OK;
}


VOID Cleanup()
{
    if( MyRenderingDevice != NULL )       
        MyRenderingDevice->Release();

	if( MyDx9Interface != NULL ) 
        MyDx9Interface->Release();
}


VOID Render()
{
	MyRenderingDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0 );					//Den Hintergrund Löschen

    if( S_OK==( MyRenderingDevice->BeginScene() ) )											//Szenen beginnen
    { 
		//Hier die GRAFIKBEFEHLE einfügen
		MyRenderingDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    MyRenderingDevice->Present( NULL, NULL, NULL, NULL );

	init=false;																					//hier, nach dem ersten Druchgang von Render Setzen wir die global Variabel init auf false, so dass beim zweiten durchgang gewisser code zum inizialisieren nicht mehr ausgeführt wird, so haben wir alles beisammen und dennoch kein überfülltes Heap infolge mehrfacherstellung gleicher Objekte.
}


LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) PostQuitMessage ( 0 );
			break;
		case WM_ACTIVATE:							// Wird der Zustand des Fensters geändert?
		{
			if (!HIWORD(wParam)) active=TRUE;		// Minimierung überprüfen, wenn nicht minimiert active=true;
			
			else active=FALSE;						// Programm nicht aktiv active=false;
		}
		break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}	// MsgProc

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )	//Winmain ist die funktion, die nach dem Starten des Prozesses aufgerufen wird
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,							//Window-Klasse erstellen
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "MyWindow", NULL };
    RegisterClassEx( &wc );																		//Window-Klasse Registrieren

    HWND hWnd = CreateWindow( "MyWindow", "Landev's DiretcX Template",			//Fenster erstellen
                              WS_OVERLAPPEDWINDOW, 0, 0, ScreenWidth, ScreenHeight,						//WS_POPUP für fenster ohne Rahmen --> fullscreen
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );


    if( SUCCEEDED( InitD3D( hWnd ) ) )															//Direct3D initialisieren
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
				if (active) Render();															//Gerendert wird nur, wenn das Fenster aktiv ist
				//if (active) computeModel();
				if (!active) Sleep(500);														//sonst geben wir die CPU zurück an das System
			}
		}
    }
	else return E_FAIL;
    UnregisterClass( "MyWindow", wc.hInstance );
	return 0;
}	// WinMain
