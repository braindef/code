
#include <GDI01.h>
#include <windows.h>
#include <string.h>  //für strcpy

#define MAXSIZE 500

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

double hektor(long);

HINSTANCE hProgram;
HWND hWnd;
HDC hDC;

double x[MAXSIZE*MAXSIZE+1], y[MAXSIZE*MAXSIZE+1];
double z[MAXSIZE*MAXSIZE+1];
double result;

int itoggle=1;

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   PSTR scCmdLine, int iCmdShow)
{
	extern HINSTANCE hProgram;
	extern HWND hWnd;
	MSG msg;
	WNDCLASSEX wndclass;
	char capname[3];

	hProgram=hInstance;

	strcpy(capname, "W4");

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hProgram;
	wndclass.hIcon = LoadIcon(hprogram, MB_ICONERROR);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	wndclass.lpszMenuName = capname;
	wndclass.lpszClassName = capname;
	wndclass.hIcon = NULL;

	RegisterClassEx(&wndclass);

	hWnd=CreateWindow(capname, "Windows Programm", WS_OVERLAPPEDWINDOW, 100, 100, 540, 140, NULL, NULL, hProgram, NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&msg);
	{
		TranslateMessage(&msg)
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM l Param)
{
	extern HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	extern double result;
	extern int itoggle;
	switch(Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_RECHNE:
			hDC=GetDC(hWnd);
			TextOut(hDC, 10, 10 "Start der Berechnung",20);
			ReleaseDC(hWnd,hDC);

			SetCursor(LoadCursor(NULL, IDC_WAIT));

			result=hektor((long)MAXSIZE);

			SetCursor(LoadCursor(NULL, IDC_ARROW));

			hDC = GetDC(hWnd);
			TextOut(hDC,10,70,"Ende der Berechnung!",20);
			ReleaseDC(hWnd, hDC);
		return 0;
		
		case IDM_LOESCHEN:
			rect.left=0;
			rect.top=0;
			rect.right=270;
			rect.bottom=70;
			InvalidateRect(hWnd, &rect, TRUE);
		return 0;

		case IDM_WERISTS_
			MessageBox(NULL, "Windows Programm W4", "W4W, MB_OK | MB_ICONINFORMATION);
		return 0;

		case IDM_ENDE:
			PostQuitMessage(0);
		return 0;
		}
		
	case WM_PAINT:
		hDC=BeginPaint(hWnd, &ps);
		if(itoggle==1)
		{
			TextOut(hDC,300, 10, "WM_PAINT gesendet!   ",22);
			itoggle=0;
		}
		else
		{
			TextOut(hDC, 300, 10, "  WM_PAINT gesendet !", 22);
			itoggle=1;
		}
		EndPaint(hWnd, &ps);
	return 0;

	case WM_MOVE:
		InvalidateRect(hWnd, NULL, TRUE);
	return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
	return 0;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
}



			case

				   