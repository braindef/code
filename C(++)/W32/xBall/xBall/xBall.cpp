#include <stdio.h>
#include <windows.h>
#include <Commctrl.h>
#include "resource.h"
#include "K8055D_C.h"

HINSTANCE hDLL = 0;
                                                                        // Handle declarations

HWND hwnd;                                                              // Dialog
HWND lngScrAD1;                                                         // Scrollbar DA1
HWND lngScrAD2;                                                         // Scrollbar DA2
HWND lngScrDA1;                                                         // Scrollbar AD1
HWND lngScrDA2;                                                         // Scrollbar AD2

char strBuffer[5];                                                      // Convertion buffer for string output
bool bConnected;                                                        // Indicates if a card is connected
long lngDigValue;                                                       // Temp. digital value for the output test
long lngVScroll;                                                        // Scroll values
int intCount;                                                           // Iteration counter
int intCurrentCard;                                                     // Current connected card
bool bMulticardExample;                                                 // Multicard flag


LRESULT CALLBACK WinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
