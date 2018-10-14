#ifndef Sprite_h
#define Sprite_h


#include "d3d9.h"
#include "d3dx9shape.h"

#include "stdio.h"			//sprintf

namespace landev
{
	class Sprite
	{
	public:
		
		static LPD3DXSPRITE mySprite;

		Sprite(LPDIRECT3DDEVICE9* parentDevice, int x, int y);
		
		void Draw();
		//void Draw(int x, int y);
		void Draw(int x1, int y1, int x2, int y2);
	};
}


#endif