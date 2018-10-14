#ifndef Text_h
#define Text_h

#include "d3d9.h"
#include "d3dx9shape.h"

#include "stdio.h"			//sprintf

namespace landev
{
	class RenderToTexture
	{
	public:
		
		LPDIRECT3DTEXTURE9		myTextur;
		

		RenderToTexture();
		
		void Draw();
		void Draw(int x, int y);
		void Draw(int x, int y, char text[], int color);
	};
}


#endif