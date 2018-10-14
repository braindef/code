#include "TextureRenderer.h"

LPDIRECT3D9				landev::TextureRenderer::MyDx9Interface = NULL;
LPDIRECT3DDEVICE9		landev::TextureRenderer::MyRenderingDevice = NULL;
LPDIRECT3DSURFACE9		landev::TextureRenderer::mySurface = NULL;
LPDIRECT3DTEXTURE9		landev::TextureRenderer::myTexture = NULL;


const int ScreenWidth=640;
const int ScreenHeight=480;


bool landev::TextureRenderer::init=true;



landev::TextureRenderer::TextureRenderer()
{
																	//Speichern der Startzeit

	MyDx9Interface = Direct3DCreate9(D3D_SDK_VERSION);				//Das Interface erstellen

	D3DPRESENT_PARAMETERS d3dpp;																//Parameter Struktur erstellen
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed=TRUE;
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;

	//ChangeToFullscreen(true);

	MyDx9Interface->CreateDevice(NULL,									//Das Renderingdevice erstellen
											D3DDEVTYPE_HAL,
											NULL,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,				//D3DCREATE_HARDWARE_VERTEXPROCESSING unter xp lahm, allenfalls wegen meiner grafikkarte...
											&d3dpp,
											&MyRenderingDevice);

	ID3DXFont *myFont;
	RECT myRect;

	MyRenderingDevice->CreateTexture(500, 2000, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &myTexture, NULL);
	
	char* TextString = new char[10];
	sprintf(TextString, "XXXXX");
	SetRect( &myRect, 0, 0, 200, 200 );        
	if( FAILED( 
		D3DXCreateFont( landev::TextureRenderer::MyRenderingDevice, 15, 0, FW_LIGHT, 1, FALSE, DEFAULT_CHARSET, 
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
					"Arial", &myFont )
				)
		)
	return;

	landev::TextureRenderer::MyRenderingDevice->SetRenderTarget(NULL, landev::TextureRenderer::mySurface);
	landev::TextureRenderer::MyRenderingDevice->Clear(
							0,
                           NULL,
                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                           D3DCOLOR_XRGB(100,100,100),
                           1.0f,
                           0);
	landev::TextureRenderer::MyRenderingDevice->BeginScene();
	myFont->DrawText(NULL, "TEST", -1, &myRect, NULL, 0xffffffff);
	landev::TextureRenderer::MyRenderingDevice->EndScene();
	myTexture->GetSurfaceLevel(NULL, &mySurface);
	


}

/*
void landev::TextureRenderer::Cleanup()
{
	if( MyRenderingDevice != NULL )       
		MyRenderingDevice->Release();

	if( MyRenderingDevice != NULL ) 
		MyRenderingDevice->Release();
}

*/


void landev::TextureRenderer::Render()
{

}



