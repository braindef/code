// CreateDirect3DWindow.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "stdafx.h"
#include "CreateDirect3DWindow.h"

#define MAX_LOADSTRING 100

// Globale Variablen:
HINSTANCE hInst;								// Aktuelle Instanz
TCHAR szTitle[MAX_LOADSTRING];					// Titelleistentext
TCHAR szWindowClass[MAX_LOADSTRING];			// Klassenname des Hauptfensters

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Hier Code einfügen.
	MSG msg;
	HACCEL hAccelTable;

	// Globale Zeichenfolgen initialisieren
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CREATEDIRECT3DWINDOW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Anwendungsinitialisierung ausführen:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_CREATEDIRECT3DWINDOW);

	// Hauptmeldungsschleife:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


void initD3D(HWND hWnd)

{
	//Create Direct3D Object
	IDirect3D9* g_pD3D = NULL;
	if(NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3DCreate9() failed", "InitD3D()", MB_OK);
		//return E_FAIL;
	}
	
	//Choose the Presentation Settings
	D3DPRESENT_PARAMETERS d3dpp = {0};
	d3dpp.Windowed = TRUE;												//
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;


	//Create a Direct3D Device
	IDirect3DDevice9*   g_pd3dDevice = NULL;
	if(FAILED(g_pD3D->CreateDevice( 
									D3DADAPTER_DEFAULT,                  // Primary display adapter ID.
									D3DDEVTYPE_HAL,                      // Use a HAL device.
									hWnd,                                // Window handle.
									D3DCREATE_HARDWARE_VERTEXPROCESSING, // Vertex processing mode.
									&d3dpp,                              // Presentation parameters.
									&g_pd3dDevice                        // Device to create.
								   )))
{
  MessageBox(0, "Direct3DCreate9() failed", "InitD3D()", MB_OK);
      //return E_FAIL;
}

	//Clear Back Buffer

  g_pd3dDevice->Clear( 
						0, 
						NULL,                     // Clear the entire viewport.
						D3DCLEAR_TARGET,          // What surface in the view port to clear. 
						D3DCOLOR_XRGB(0, 0, 255), // Color to clear with 
						0,                        // Z-Buffer (Not Used)
						0                         // Stencil data (Not Used)
					);

	//Begin und END SCENE
  if(SUCCEEDED(g_pd3dDevice->BeginScene()))
{
     // Custom rendering code belongs here...
	
     g_pd3dDevice->EndScene();
} 

	//Display the output

	g_pd3dDevice->Present( 
						NULL, // Pointer to the source RECT.
						NULL, // Pointer to the destination RECT.
						hWnd, // Destination window for present.
						NULL  // Minimal set of pixels to be updated.
						);


	//Release the window

	if(g_pd3dDevice != NULL)
{
    g_pd3dDevice->Release();
    g_pd3dDevice = NULL;
}

if(g_pD3D != NULL)
{
    g_pD3D->Release();
    g_pD3D = NULL;
}


}


//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
//  KOMMENTAR:
//
//    Sie müssen die Funktion zu verwenden, wenn Sie möchten, dass der Code
//    mit Win32-Systemen kompatibel ist, bevor die Funktion 'RegisterClassEx'
//    zu Windows 95 hinzugefügt wurde. Der Aufrud der Funktion ist wichtig,
//    damit die kleinen Symbole, die mit der Anwendung verknüpft sind,
//    richtig formatiert werden.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_CREATEDIRECT3DWINDOW);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_CREATEDIRECT3DWINDOW;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNKTION: InitInstance(HANDLE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTAR:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   initD3D(hWnd);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, unsigniert, WORD, LONG)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND	- Verarbeiten des Anwendungsmenüs
//  WM_PAINT	- Zeichnen des Hauptfensters
//  WM_DESTROY	- Beenden-Meldung anzeigen und zurückgeben
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Menüauswahl bearbeiten:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_D3D:
			
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Fügen Sie hier den Zeichnungscode hinzu...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Meldungshandler für Infofeld.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
