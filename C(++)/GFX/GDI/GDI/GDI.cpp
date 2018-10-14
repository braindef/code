// GDI.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "stdafx.h"
#include "GDI.h"

// GDI01b.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

// LPCWSTR long pointer to a constant unicode [hier gleich wide] string

#include "GDI.h"
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

	strcpy_s(capname, "W4");

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hProgram;
	//wndclass.hIcon = LoadIcon(hProgram, MB_ICONERROR);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	wndclass.lpszMenuName = (LPCWSTR)capname;
	wndclass.lpszClassName = (LPCWSTR)capname;
	wndclass.hIcon = NULL;

	RegisterClassEx(&wndclass);

	hWnd=CreateWindow((LPCWSTR)capname, (LPCWSTR)"Windows Programm", WS_OVERLAPPEDWINDOW, 100, 100, 540, 140, NULL, NULL, hProgram, NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0));
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
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
			TextOut(hDC, 10, 10, (LPCWSTR)"Start der Berechnung",20);
			ReleaseDC(hWnd,hDC);

			SetCursor(LoadCursor(NULL, IDC_WAIT));

			result=hektor((long)MAXSIZE);

			SetCursor(LoadCursor(NULL, IDC_ARROW));

			hDC = GetDC(hWnd);
			TextOut(hDC,10,70,(LPCWSTR)"Ende der Berechnung!",20);
			ReleaseDC(hWnd, hDC);
		return 0;
		
		case IDM_LOESCHEN:
			rect.left=0;
			rect.top=0;
			rect.right=270;
			rect.bottom=70;
			InvalidateRect(hWnd, &rect, TRUE);
		return 0;

		case IDM_WERISTS:
			MessageBox(NULL, (LPCWSTR)"Windows Programm W4", (LPCWSTR)"W4W", MB_OK | MB_ICONINFORMATION);
		return 0;

		case IDM_ENDE:
			PostQuitMessage(0);
		return 0;
		}
		
	case WM_PAINT:
		hDC=BeginPaint(hWnd, &ps);
		if(itoggle==1)
		{
			TextOut(hDC,300, 10, (LPCWSTR)"WM_PAINT gesendet!   ",22);
			itoggle=0;
		}
		else
		{
			TextOut(hDC, 300, 10, (LPCWSTR)"  WM_PAINT gesendet !", 22);
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


				   