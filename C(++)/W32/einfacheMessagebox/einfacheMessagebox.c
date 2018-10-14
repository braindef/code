#include <windows.h>



int WINAPI WinMain(HINSTANCE hInstance,										// # define WINAPT __stdcall ??
				   HINSTANCE hPrevInstance,									// UINT for unsigned INT
				   LPSTR lpCmdLine,											// LPSTRing for char*		LPCSTR LongPointerConstantSTRing = pointer to constant string
				   int nCmdShow)											// int passed to ShowWindow(). 		
{
																			
	MessageBox(NULL, "Hello World", "Hello", MB_OK | MB_ICONQUESTION);								 
	return 0;																			
	//MessageBox(NULL, "Error!", "Error!",
	MB_ICONEXCLAMATION | MB_OKCANCEL);
																										


}