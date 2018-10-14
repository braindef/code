#include "Engine.h"
#include <vector>

#include "Text.h"	// zum testen
#include "Linie.h"
//#include "TextScroller.h"
#include "Sprite.h"

// zum Testen

landev::Text* myText;
landev::Linie* myLinie;
//landev::TextScroller* myScroller;
//landev::Sprite* testSprite;



landev::artObject::artObject(LPDIRECT3DDEVICE9* parentDevice, int factor) 
{
	myText=new landev::Text(parentDevice, 300,300);
	myLinie=new landev::Linie(parentDevice, 300, 300);
//	myScroller=new landev::TextScroller(parentDevice, 300, 300);
	landev::artObject::x=200;
	landev::artObject::initFactor=factor;
//	testSprite=new landev::Sprite(parentDevice, 50, 50);
	
}

landev::artObject::~artObject() 
{
	

}




HWND hwnd;

int vorzeichen=1;

HRESULT landev::artObject::Calculate() 
{

	//MessageBox(hwnd, "calculate Artobject", "calculate", NULL);
	return 0;
}

unsigned int count=0;
unsigned int color=0xffffffff;
char text[10]="-=88=-";
bool reverse=true;

HRESULT landev::artObject::Draw()
{
	if((count++%40)>35)
	{
		if(count%255==0) reverse=!reverse;
		if (reverse) color-=0x010101;
		else color+=0x010101;
	}
	
//	myScroller->Draw();	
	//testSprite->Draw();
	myLinie->Draw(280+2*initFactor*cos(initFactor*sin(GetTickCount()*0.00005)),220+2*initFactor*sin(initFactor*GetTickCount()*0.00005),280+2*initFactor*cos(initFactor*sin((GetTickCount()-200)*0.00005)),220+2*initFactor*sin(initFactor*(GetTickCount()-200)*0.00005));
	myLinie->Draw(280+2*initFactor*cos(initFactor*sin(GetTickCount()*0.00005)),220+2*initFactor*sin(initFactor*GetTickCount()*0.00005),280+2*initFactor*cos(initFactor*cos((GetTickCount()-200)*0.00005)),220+2*initFactor*sin(initFactor*(GetTickCount()-200)*0.00005));
	myLinie->Draw(280+2*initFactor*cos(initFactor*sin(GetTickCount()*0.00005)),220+2*initFactor*sin(initFactor*GetTickCount()*0.00005),280+2*initFactor*cos(initFactor*cos((GetTickCount()-200)*0.00005)),220+2*initFactor*cos(initFactor*(GetTickCount()-200)*0.00005));
	

	return 0;
}
