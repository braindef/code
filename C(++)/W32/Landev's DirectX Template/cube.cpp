#include "cube.h"

#include <d3d9.h>
#include <d3dx9shape.h>		//for D3DXCreateLine, D3DXVECTOR2 ...

LPDIRECT3DDEVICE9 CubeRenderingDevice;

D3DXVECTOR2* Vector2 =  new D3DXVECTOR2[ 2 ]; 
LPD3DXLINE CubeLine;

bool CubeInit=true;

HRESULT landev::cube::getDevice(LPDIRECT3DDEVICE9 device)
{
	CubeRenderingDevice = device;
	return S_OK;
}

HRESULT landev::cube::draw()
{
	if (CubeInit) D3DXCreateLine( CubeRenderingDevice, &CubeLine ); 

	Vector2[ 0 ] = D3DXVECTOR2( 640, 0 ); 
	Vector2[ 1 ] = D3DXVECTOR2( 0, 458 ); 

	CubeLine->SetWidth(2);
	CubeLine->SetAntialias(true);

	CubeLine->Begin();
	CubeLine->Draw(Vector2, 2, 0x99ff0000);
	CubeLine->End();

	CubeInit=false;
	return S_OK;

}

landev::cube::cube()
{
}
