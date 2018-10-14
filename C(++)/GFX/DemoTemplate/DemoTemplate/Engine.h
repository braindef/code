#ifndef Engine_h
#define Engine_h

#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib") 
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "d3dxof.lib")
//#pragma comment(lib, "d3dx9dt.lib")
//#pragma comment(lib, "winmm.lib")

#include "d3d9.h"
#include "windows.h"
#include "SurfaceDisplay.h"
//#include <vector>
//#include "math.h"			//sin
//#include "stdio.h"			//sprintf
//#include "d3dx9shape.h"		//dx-line
//#include "Engine.h"
//#include "FPS.h"
#include "stdio.h"			//für sprintf
//#include "DX9Window.h"
//#include "FPS.h"



namespace landev
{
	namespace anotherNamespace
	{
		class anotherClass
		{
		};
	}

	class Engine
	{
	public:

		//Device
		//Atributes
		static bool init;
		static LPDIRECT3DDEVICE9 MyRenderingDevice;
		static LPDIRECT3D9 MyDx9Interface;						
		static int StartTime;									//getTime zum start des Programms
		static int lastTime;
		static int frameTime;
		static int ticks;
		static bool active;										//wird beim minimiere auf false gesetzt

		//Methods

		Engine();
		~Engine();

		HRESULT Draw();

		static HRESULT ChangeToFullscreen(bool fullscreen);														//Fullscreen modus wechseln
		static HRESULT InitD3D(HWND hWnd);																		//DX9 initialisieren
		static void Cleanup();																					//Gerät/Interface entfernen
		static void Render();
		static void FPS();
		static LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
		static INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow );	//Winmain ist die funktion, die nach dem Starten des Prozesses aufgerufen wird


	};
}


#endif

