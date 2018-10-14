#include <d3d9.h>

#ifndef cube_h
#define cube_h

namespace landev
{
	class cube
	{
	public:
		cube();
		HRESULT getDevice(LPDIRECT3DDEVICE9 MyRenderingDevice);
		HRESULT draw();
		int x, int y;
	};
}


#endif
