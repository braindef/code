#ifndef SurfaceDisplay_h
#define SurfaceDisplay_h

#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib") 
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "d3dxof.lib")
//#pragma comment(lib, "d3dx9dt.lib")
//#pragma comment(lib, "winmm.lib")

#include "d3d9.h"
#include "windows.h"
#include "Engine.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

namespace landev
{
	class SurfaceDisplay
	{
	public:
		static void RenderSurface();
	
		


	};
}


#endif

