#ifndef TexturLaden_h
#define TexturLaden_h

#include "d3d9.h"
#include "d3dx9shape.h"

#include "stdio.h"			//sprintf

namespace landev
{
	class TexturLaden
	{
	public:
		

		TexturLaden(LPDIRECT3DDEVICE9* parentDevice, int x, int y);
		
		void Draw();
		//void Draw(int x, int y);
		void Draw(int x1, int y1, int x2, int y2);
	};
}


#endif