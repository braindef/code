#include "RenderToTexture.h"

#include "d3d9.h"

LPDIRECT3D9				MyDx9Interface2 = NULL;
LPDIRECT3DDEVICE9		MyRenderingDevice2 = NULL;
LPDIRECT3DTEXTURE9		myTexture = NULL;
LPDIRECT3DSURFACE9		mySurface= NULL;

landev::RenderToTexture::RenderToTexture()
{

	MyDx9Interface2 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;																//Parameter Struktur erstellen
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed=TRUE;
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;

	MyDx9Interface2->CreateDevice(NULL, 									//Das Renderingdevice erstellen
											D3DDEVTYPE_HAL,
											NULL,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,				//D3DCREATE_HARDWARE_VERTEXPROCESSING unter xp lahm, allenfalls wegen meiner grafikkarte...
											&d3dpp,
											&MyRenderingDevice2) ;

	MyRenderingDevice2->CreateTexture(512, 512,1, D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &myTexture, NULL);

	MyRenderingDevice2->SetRenderTarget(NULL, mySurface);

	char* TextString = new char[10];
	sprintf(TextString, "XXXXX");
	
	ID3DXFont* myFont;
	RECT topLeft;
	SetRect(&topLeft , 0, 0, 200, 200 );        
	if( FAILED( 
		D3DXCreateFont( MyRenderingDevice2, 15, 0, FW_LIGHT, 1, FALSE, DEFAULT_CHARSET, 
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
					"Arial", &myFont)
				)
		)

	myTexture->GetSurfaceLevel(NULL, &mySurface);
	
}



void landev::RenderToTexture::Draw()
{

	
}

/*void landev::RenderToTexture::Draw(int x1, int y1, int x2, int y2)
{


	//Draw();
}*/



