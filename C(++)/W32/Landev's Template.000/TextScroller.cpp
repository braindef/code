#include "TextScroller.h"
#include "RenderToTexture.h"

//#include<iostream>
#include<fstream>
#include<string>
#include<iostream>

using namespace std;

string buffer, fileText;
LPD3DXSPRITE myTextSprite;
LPDIRECT3DTEXTURE9 Texture=NULL;

landev::RenderToTexture myRenderedTexture;


landev::TextScroller::TextScroller(LPDIRECT3DDEVICE9* parentDevice, int x, int y)
{
	D3DXCreateSprite(*parentDevice,&myTextSprite);

	D3DXCreateTextureFromFile(*parentDevice,"mann.tga",&Texture);

	TextString= new char[1000];
	ifstream file("text.txt");

	file.read(TextString, 100  );
	file.close();
	
	//sprintf(TextString, "asdfasdf\nasdfasdfasdf");

	SetRect( &FPSRect, 00, 00, 100, 100 );        
	if( FAILED( 
		D3DXCreateFont( *parentDevice, 15, 0, FW_LIGHT, 1, FALSE, DEFAULT_CHARSET, 
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
					"Arial", &FontObject )
				)
		)

		myRenderedTexture = new landev::RenderToTexture();

		//FontObject->DrawText(myTextSprite, TextString , -1, NULL, DT_NOCLIP, 0xffffff00);	
		myTextSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR2 pos=D3DXVECTOR2(100,20);
	D3DXVECTOR2 scaling(2.0f,1.0f);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,NULL,0,&pos);
	
	myTextSprite->SetTransform(&mat);
	FontObject->DrawText(myTextSprite, TextString , -1, &FPSRect, DT_NOCLIP, 0xffffff00);	
	myTextSprite->Draw(,&FPSRect,NULL,NULL,0xFFFFFFFF);
	
	//myTextSprite->Draw(NULL,&FPSRect,NULL,NULL,0xffffff00);
	myTextSprite->End();
	

	return;
}

void landev::TextScroller::Draw(int x, int y, char text[], int color)
{
	
	sprintf(TextString, "XXXXX");				//...!=0 keine DivbyZero
	FontObject->DrawText( NULL, TextString , -1, &FPSRect, DT_NOCLIP, color);	
	SetRect( &FPSRect, x, y, x+60, y+15 );
	Draw();	
}


void landev::TextScroller::Draw()
{
	myTextSprite->Draw(
}

void landev::TextScroller::Draw(int x, int y)
{
	SetRect( &FPSRect, x, y, x+60, y+15 );
	Draw();
}