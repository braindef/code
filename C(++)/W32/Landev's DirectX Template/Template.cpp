//#include "Template.h"
#include "cube.h"

#include "ClassTemplate.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9shape.h>		//for D3DXCreateLine, D3DXVECTOR2 ...
//#include <windows.h>
#include <stdio.h>			//for sprintf


LPDIRECT3D9             MyDx9Interface			= NULL;
LPDIRECT3DDEVICE9		MyRenderingDevice		= NULL;
LPDIRECT3DVERTEXBUFFER9	MyVertexBuffer			= NULL;
landev::cube	MyCube;

const int ScreenWidth=640;
const int ScreenHeight=480;
const float Pi = 3.14159265;

//ID3DXSprite*        MyTextSprite = NULL;   // Sprite for batching draw text calls

int StartTime=0;

MSG msg;
bool active=true;
bool init=true;

struct MyVertex
{
	FLOAT x, y, z, rhw;			// X-,Y-,Z-Achse und Z-Buffer (reciprocal homogeneous w)
	DWORD color;				// Farbe
};

//Forward declarations





#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

HRESULT InitD3D(HWND hWnd)
{
	StartTime = GetTickCount();
	//Fullscreen
	/*DEVMODE dmScreenSettings;
	memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
	dmScreenSettings.dmSize=sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth=ScreenWidth;
	dmScreenSettings.dmPelsHeight=480;
	dmScreenSettings.dmBitsPerPel=16;
	dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
	
	ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
	//ChangeDisplaySettings(NULL,0);
	//ShowCursor(false);
*/
	//Create the Interface
	if ( (MyDx9Interface=Direct3DCreate9(D3D_SDK_VERSION)) == NULL ) return E_FAIL;

	//Create the Parameter Structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed=TRUE;
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;

	if( FAILED(MyDx9Interface->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_HAL,
											hWnd,
											D3DCREATE_HARDWARE_VERTEXPROCESSING,
											&d3dpp,
											&MyRenderingDevice))) 
		return E_FAIL;




	return S_OK;
}




VOID Cleanup()
{

	if( MyVertexBuffer != NULL )        
        MyVertexBuffer->Release();

    if( MyRenderingDevice != NULL )       
        MyRenderingDevice->Release();

	if( MyDx9Interface != NULL ) 
        MyDx9Interface->Release();

}

D3DXVECTOR2* Vector1 =  new D3DXVECTOR2[ 2 ]; 
LPD3DXLINE Line;

HRESULT DrawLine()
{
    if (init) D3DXCreateLine( MyRenderingDevice, &Line ); 

	Vector1[ 0 ] = D3DXVECTOR2( 0, 0 ); 
	Vector1[ 1 ] = D3DXVECTOR2( ScreenWidth, 458 ); 

	Line->SetWidth(2);
	Line->SetAntialias(true);

	Line->Begin();
	Line->Draw(Vector1, 2, 0x99ff0000);
	Line->End();

	return S_OK;
}


ID3DXFont*          MyFont = NULL;
RECT rc; 
int MyTime = NULL;
float yCord = NULL;

HRESULT DrawFont()
{
		if (init) //Wir wollen das Font-Objekt nur einmal erstellen!
			if( FAILED( D3DXCreateFont( MyRenderingDevice, 30, 0, FW_LIGHT, 1, FALSE, DEFAULT_CHARSET, 
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
                         "Arial", &MyFont ) ) );
        
        
		//LPCSTR = const char * und LPSTR = char *
		
		char MyTimeString[10];
		MyTime = GetTickCount();
		int dTime = (MyTime-StartTime);
		

		//int MySin(float startPhi, float stopPhi,

		SetRect( &rc,(dTime/10)%700-60,200-abs(100*(sin((float)dTime/1800*Pi))), 0, 0 );        
		
		sprintf(MyTimeString,"%d",dTime);
		MyFont->DrawText( NULL, MyTimeString , -1, &rc, DT_NOCLIP, 0xff0000ff);
		//MyFont->Release();


return S_OK;
}




VOID Render()
{
    // Clear the backbuffer to a blue color
	MyRenderingDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( MyRenderingDevice->BeginScene() ) )
    { 
		//Motion Blur
		//DrawLine();
		MyCube.getDevice(MyRenderingDevice);
		MyCube.draw();
		DrawFont();
        // End the scene
        MyRenderingDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    MyRenderingDevice->Present( NULL, NULL, NULL, NULL );

	init=false;		//hier, nach dem ersten Druchgang von Render Setzen wir die global Variabel init auf false, so dass beim zweiten durchgang gewisser code zum inizialisieren nicht mehr ausgeführt wird, so haben wir alles beisammen und dennoch kein überfülltes Heap infolge mehrfacherstellung gleicher Objekte.
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
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}
		break;

    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}	// MsgProc


HRESULT InitVB()
{
    // Initialize three vertices for rendering a triangle
    MyVertex vertices[] =
    {
        { 150.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
        {  50.0f, 250.0f, 0.5f, 1.0f, 0xff00ffff, },
    };

    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
	if( FAILED( 
		MyRenderingDevice->CreateVertexBuffer( 
												3*sizeof(MyVertex), 0, D3DFVF_CUSTOMVERTEX,
												  D3DPOOL_DEFAULT, &MyVertexBuffer, NULL 
											)
				) 
		)
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if( FAILED( MyVertexBuffer->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, vertices, sizeof(vertices) );
    MyVertexBuffer->Unlock();

    return S_OK;
}	// InitVB


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )					//Winmain ist die funktion, die nach dem Starten des Prozesses aufgerufen wird
{

    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,							//Window-Klasse erstellen
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "Landev's DiretcX Template", NULL };
    RegisterClassEx( &wc );																		//Window-Klasse Registrieren

    // Create the application's window
    HWND hWnd = CreateWindow( "Landev's DiretcX Template", "Landev's DiretcX Template",
                              WS_OVERLAPPEDWINDOW, 0, 0, ScreenWidth, 480,					//WS_POPUP
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );
	
	// Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the vertex buffer
        
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

//	landev::ClassTemplate MyTemplate2(100,100);
//	landev::ClassTemplate MyTemplate3();

	
	//MessageBox(hWnd, (char)MyTemplate2.X(),NULL, NULL);


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
					if (active) Render();
					//if (active) computeModel();
					if (!active) Sleep(300);		//for not wasting CPU when minimized...
				}

            }
    }

    UnregisterClass( "Landev's DiretcX Template", wc.hInstance );
    return 0;
}	// WinMain



/*
MOUSE IMPLEMENTATION (LATER)

case WM_MOUSEMOVE:
{

  // Retrieve mouse screen position
  int x=(short)LOWORD(lParam);
  int y=(short)HIWORD(lParam);

  // Check to see if the left button is held down:
  bool leftButtonDown=wParam & MK_LBUTTON;

  // Check if right button down:
  bool rightButtonDown=wParam & MK_RBUTTON;

}

COMMANDS

case WM_COMMAND:
{

   switch(LOWORD(wParam))
   {
        case IDM_SAVE:
          SaveProject()
        break;
        case IDM_LOAD:
          LoadProject()
        break;
        default:
        break;
    }
}
In your game you may want to control a camera rotation dependant on the change in the mouse position. To do this you need to remember the previous mouse position and use the difference to map onto camera rotations. If you are running your game in a window you can get into problems when the mouse leaves the window area as you stop receiving mouse messages. To solve this you can capture the mouse, this means only your window receives messages from the mouse. Obviously you do not want to do this all the time or the user would not be able to work outside of your program so one way to do it is to capture the mouse only when the left button is first held down and then release it when the button is lifted. 

To capture the mouse:

SetCapture(hWnd);

To release the mouse:

ReleaseCapture();

Messages: WM_LBUTTONDOWN, WM_RBUTTONDOWN

These are sent if the left button or right button on the mouse has been pressed.

Messages: WM_LBUTTONUP, WM_RBUTTONUP
 

*/


