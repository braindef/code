#include "ModelEngine.h"

#include "d3d9.h"
#include "d3dx9shape.h"

D3DXVECTOR2* Vector1 =  new D3DXVECTOR2[ 2 ]; 
LPD3DXLINE Line;



landev::ModelEngine::ModelEngine(LPDIRECT3DDEVICE9 parentDevice)
{
	D3DXCreateLine( parentDevice, &Line ); 

	Vector1[ 0 ] = D3DXVECTOR2( 0, 0 ); 
	Vector1[ 1 ] = D3DXVECTOR2( 640, 480 ); 
}

void landev::ModelEngine::ActualFrame()
{
	//Line->SetWidth(2);
	//Line->SetAntialias(true);

	Line->Begin();
	Line->Draw(Vector1, 2, 0x99ff0000);
	Line->End();

	return;
}