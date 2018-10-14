#ifndef GDef_h

#define AHVER "Air Hockey 0.0.1"


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <d3d9.h>
#include <dinput.h>
#include <dsound.h>


#define FAIL -1
#define OK 1


//Globale Windows Variablen
extern HINSTANCE HInstance;
extern HWND Hwnd;


//Globale Allgemeine Variablen
extern int ScreenWidth, ScreenHeight;


//Globale Allgemeine Funktionen
void g_Shutdown(void);
int g_Initialisation(void);
int g_StartLoop(void);


#endif
#define GDef_h