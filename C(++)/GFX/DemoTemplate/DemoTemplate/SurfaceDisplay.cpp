#include "SurfaceDisplay.h"

struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
};

void landev::SurfaceDisplay::RenderSurface()
{
	LPDIRECT3DSURFACE9 mySurface;
	landev::Engine::MyRenderingDevice->CreateRenderTarget(800,600, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE,0, true, &mySurface, NULL);
	

	
	CUSTOMVERTEX vertices[] =
	{
		{ 150.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
		{ 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
		{  50.0f, 250.0f, 0.5f, 1.0f, 0xff00ffff, },
	};

	LPDIRECT3DVERTEXBUFFER9 myVertexBuffer;

	landev::Engine::MyRenderingDevice->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &myVertexBuffer, NULL);

	void* pVertices;
	myVertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0);

	memcpy(pVertices, vertices, sizeof(vertices));

	myVertexBuffer->Unlock();

	landev::Engine::MyRenderingDevice->BeginScene();
	landev::Engine::MyRenderingDevice->SetStreamSource(0, myVertexBuffer, 0, sizeof(CUSTOMVERTEX));
	landev::Engine::MyRenderingDevice->SetFVF( D3DFVF_CUSTOMVERTEX);
	landev::Engine::MyRenderingDevice->DrawPrimitive( D3DPT_POINTLIST, 0, 1);
	landev::Engine::MyRenderingDevice->EndScene();


}
