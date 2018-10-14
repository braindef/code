#ifndef Scroller
#define Scroller

#include <windows.h>
#include "d3d9.h"
#include "d3dx9.h"
#include "math.h"
#include <stdio.h>
//#include io irgendwas, für ein logfile zum fehler finden

#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib")

#define SCREEN_WIDTH			800									// Aufloesung Breite
#define SCREEN_HEIGHT			600									// Aufloesung Hoehe
#define SCREEN_BPP				32									// Bits Per Pixel, Farbtiefe

#define WIN32_LEAN_AND_MEAN											// Selten gebrauchte Header nicht brauchen



namespace landev
{
	class Scroller
	{
		bool Init(void);											// Initialisation
		bool Main(void);											// Main "Loop"
		void Kill(void);											// Löschen der Objekte
	};

}

#endif
