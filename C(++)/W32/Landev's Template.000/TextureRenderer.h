#ifndef TextureRenderer_h
#define TextureRenderer_h

#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib") 
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "d3dxof.lib")
//#pragma comment(lib, "d3dx9dt.lib")

#pragma comment(lib, "winmm.lib")


#include "d3d9.h"
#include "Engine.h"
#include "FPS.h"
#include "stdio.h"

//TODO Singelton restCPUtime

namespace landev 
{
	class Engine;
	class DisplayFPS;

	//Forward declaration
	class TextureRenderer
	
	//Class declaration
	{
	public:

		TextureRenderer();
		static bool init;
		static LPDIRECT3D9 MyDx9Interface;
		static LPDIRECT3DDEVICE9 MyRenderingDevice;
		static LPDIRECT3DSURFACE9 mySurface;
		static LPDIRECT3DTEXTURE9 myTexture;
		static HRESULT ChangeToFullscreen(bool fullscreen);														//Fullscreen modus wechseln
		static HRESULT Init();																		//DX9 initialisieren
		static VOID Cleanup();																					//Gerät/Interface entfernen
		static VOID Render();
	};
}

#endif
