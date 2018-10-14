#include "FPS.h"



landev::FPS::FPS(LPDIRECT3DDEVICE9* parentDevice, int x, int y)
{

	landev::FPS::LastFrame=0;
	landev::FPS::FrameTime=0;

	FPSString = new char[10];
	sprintf(FPSString, "FPS=");
	SetRect( &FPSRect, x, y, x+60, y+15 );        
	if( FAILED( 
		D3DXCreateFont( *parentDevice, 15, 0, FW_LIGHT, 1, FALSE, DEFAULT_CHARSET, 
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
					"Arial", &FPSText )
				)
		);

}
void landev::FPS::Draw()
{
	FrameTime = GetTickCount() - LastFrame;																//Zeit zwischen den Frames
	
	if(((LastFrame%1000)>900)&&FrameTime!=0) sprintf(FPSString, "FPS=%d", 1000/FrameTime);				//...!=0 keine DivbyZero
		FPSText->DrawText( NULL, FPSString , -1, &FPSRect, DT_NOCLIP, 0xffffffff);	
	
	LastFrame = GetTickCount();
}

void landev::FPS::Draw(int x, int y)
{
	SetRect( &FPSRect, x, y, x+60, y+15 );
	Draw();
}