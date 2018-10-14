#ifndef ModelEngine_h
#define ModelEngine_h

#include "d3d9.h"
#include "d3dx9shape.h"
#include "DX9Window.h"

namespace landev
{
	class Dx9Window;

	class ModelEngine
	{
	public:
		LPD3DXLINE Line;
		ModelEngine();
		ModelEngine(LPDIRECT3DDEVICE9 parentDevice);
		~ModelEngine();
		void getDevice(LPDIRECT3DDEVICE9 parentDevice);
		void ActualFrame();
		void ModelThread();
		void RestartModelThread();
		int x,y;
	};
}
#endif
