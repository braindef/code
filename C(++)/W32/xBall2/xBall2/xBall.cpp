
#include "xBall.h"
#include <stdio.h>
#include <windows.h>
//#include <Commctrl.h>
#include "resource.h"
#include "K8055D_C.h"
#include "mmsystem.h"

#define DEFAULT_TIME 600
#define DEFAULT_PAUSE_TIME 120

HWND hwnd;                                                              // Dialog
HWND hDialog;
//HDC myDeviceContext;
HDC hDC;


int intCurrentCard=0;
bool cardFound=false;
bool TeamA=false;
bool TeamB=false;
bool terminate=true;						//fürs beenden
bool lockJudging=false;
bool lockGlobalPause=false;

bool valid=false;

bool running=false;
int startTime=0;							//inizialer tick count
//int defaultTime;							//Zeit die zur Berechnung initial verwendet wird

bool pause=false;
int globalPauseStartTime=0;					
int globalPauseTime=0;						//zeit in der die pause gedrückt wurde

int defaultPauseTime=0;
int localPauseStartTime=0;

bool lockInvalid=false;

//Forward declarations
void start();
void stop();
void resume();
void cont();
void clear();
void localPause();
void globalPause();
void sound(int sound);
LONG BeepThread(LPVOID pParam);




LONG fadeInThread(LPVOID pParam)
{
	if (IsDlgButtonChecked(hDialog, IDC_AdjustVolume)==0) return 0;
	//Beep(9000,1000);
	for(int i=0; i<=0xfff0fff0; i+=0x000f000f)
		waveOutSetVolume(0,i);
	return 0;
}

LONG fadeOutThread(LPVOID pParam)
{
	if (IsDlgButtonChecked(hDialog, IDC_AdjustVolume)==0) return 0;
	//Beep(9000,1000);
	for(DWORD i=0xffffffff; i>=0x000f000f; i-=0x000f000f)
		waveOutSetVolume(0,i);
	return 0;
}

void fadeIn()
{

	DWORD dwID;
    HANDLE threadHandle = CreateThread(NULL,NULL,
                           (LPTHREAD_START_ROUTINE)fadeInThread,
                           NULL, NULL, &dwID);	
}
void fadeOut()
{

	DWORD dwID;
    HANDLE threadHandle = CreateThread(NULL,NULL,
                           (LPTHREAD_START_ROUTINE)fadeOutThread,
                           NULL, NULL, &dwID);	
}

LRESULT CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	hDialog=hDlg;
	switch (message)
	{
			case WM_INITDIALOG:   

				//int intDevices;
				//intDevices=SearchDevices();					//macht noch probleme
				//waveOutSetVolume(0,0xffffffff);

				hwnd = GetDesktopWindow(); 

				if (OpenDevice(0)==-1) 
				{
					MessageBox(NULL, L"Karte nicht gefunden, Bitte Stellen Sie die Karte auf die Adresse 0 ein", L"Karte nicht gefunden", MB_OK | MB_ICONERROR);
				}
				else
				{
					cardFound=true;
					Beep(2000,50);Beep(1000,50);
					SetCounterDebounceTime(1, 0);
					ClearAllDigital();
					ClearAllAnalog();
				}
				SetDlgItemInt(hDlg, IDC_TimeDefault, DEFAULT_TIME, false);
				SetDlgItemInt(hDlg, IDC_PauseDefault, DEFAULT_PAUSE_TIME, false);
				SetTimer(hDlg, IDT_TIMER, 10, 0);
				SetTimer(hDlg, IDT_REDRAW, 250, 0);
				// Window initialisation
				//MessageBox(NULL, L"Hello World", L"Hello", MB_OK | MB_ICONQUESTION);
				EnableWindow(GetDlgItem(hDlg, IDD_DIALOG), true);
			return TRUE;

		case WM_CLOSE:
			return TRUE;

		case WM_PAINT:
			hDC = GetDC(hDlg);
			if(!cardFound) TextOut(hDC, 310, 20, L"Karte NICHT gefunden", 20);
			//if(running)
			//{    
			//	TextOut(hDC, 310, 20, L"RUNNING", 7);
			//}
			//if(!running) 
			//{    
			//	TextOut(hDC, 310, 20, L"STOPPED", 7);
			//}
			//ReleaseDC(hDlg,hDC);
			//Beep(200,100);
			break;

		case WM_COMMAND:
			if (LOWORD(wParam) == ID_ENDE) {    
				if (terminate) EndDialog(hDlg, LOWORD(wParam));
			}
			if (LOWORD(wParam) == IDC_TeamA) {
				if(!TeamA && !TeamB && running) 
				{
					TeamA=true;
					localPause();
				}
			}
			if (LOWORD(wParam) == IDC_TeamB) {
				if(!TeamA && !TeamB && running) 
				{
					TeamB=true;
					localPause();
				}
			}

			if (LOWORD(wParam) == IDC_INVALID)
			{
				if(TeamA || TeamB) resume();
			}		
			if (LOWORD(wParam) == IDC_VALID)
			{
				if(TeamA || TeamB) cont();
			}
			if (LOWORD(wParam) == IDC_START)					//START
			{
				start();
			}
			
			if (LOWORD(wParam) == IDC_STOP)						//STOP
			{
				stop();
			}
				
			if (LOWORD(wParam) == IDC_PAUSE)					//Pause
			{
				globalPause();
			}
			if (LOWORD(wParam) == IDC_FadeIn)					//Pause
			{
				fadeIn();
			}
			if (LOWORD(wParam) == IDC_FADEOUT)					//Pause
			{
				fadeOut();
			}
			break;
		
    break;
		case WM_DESTROY :
            PostQuitMessage(0);
			ClearAllDigital();
			ClearAllAnalog();
			CloseDevice();                                              // Close the device connection (if any)
			EndDialog(hDlg, LOWORD(wParam));                            // Close the dialog
            break;
		
		case WM_TIMER:                                                  // Timer event
			if (LOWORD(wParam) == IDT_TIMER) 
			{
				LONG lngInputs = ReadAllDigital();                           // Read all digital inputs
				if(!TeamA && !TeamB && running) 
				{
					if(cardFound) TeamA=lngInputs & 1;
					if (TeamA) 
					{
						
						localPause();
					}			
					if(cardFound) TeamB=(lngInputs & 2) / 2;
					if (TeamB) 
					{
						
						localPause();
					}
				}
				if(cardFound)
					if((lngInputs & 4)/4) 
						if(TeamA || TeamB) 
							if(!lockJudging)
							{
								lockJudging=true;
								cont();
							}
				if(cardFound)
					if((lngInputs & 8)/8) 
						if(TeamA || TeamB) 
							if(!lockJudging)
							{
								lockJudging=true;
								resume();
							}
				
				if(cardFound)
					if((lngInputs & 16)/16) 
						if(!running&&!pause) start();
						else globalPause();

				CheckDlgButton(hDlg, IDC_TeamA, TeamA);
				if(TeamA) SetDigitalChannel(1);
				CheckDlgButton(hDlg, IDC_TeamB, TeamB);
				if(TeamB) SetDigitalChannel(2);
				SetTimer(hDlg, IDT_TIMER, 1, 0);
				if (running)
				{
					TCHAR myTimeString[16];

					int givenTime = GetDlgItemInt(hDlg, IDC_TimeDefault, NULL, false);
					int elapsedTime=(GetTickCount()-startTime)/1000 /*minus BEEP*/ -3;
					wsprintf(myTimeString,L"%d", elapsedTime);
					SetDlgItemText(hDlg, IDC_Timer, (LPCWSTR)myTimeString);
					if (elapsedTime>=givenTime)
					{
						sound(END_BEEP);
						running=false;
						fadeIn();
					}
					localPauseStartTime=GetTickCount();
				}
				if (pause)
				{
					TCHAR myTimeString[16];
					int elapsedPauseTime=(GetTickCount()-localPauseStartTime)/1000-defaultPauseTime+1;
					wsprintf(myTimeString,L"%d", elapsedPauseTime);
					SetDlgItemText(hDlg, IDC_PauseTime, (LPCWSTR)myTimeString);
				}
				
				

			}
			if (LOWORD(wParam) == IDT_PAUSETIMER)
			{
				if(valid)
				{
					sound(CONTINUE_BEEP);
					clear();
					valid=false;
					lockInvalid=false;
				}
				
			}
			if (LOWORD(wParam) == IDT_STARTWARNING)
			{
				sound(PREWARN_BEEP);
				KillTimer(hDlg, IDT_STARTWARNING);
			}
			
			if (LOWORD(wParam) == IDT_REDRAW)
			{	
				RECT myRect;
				myRect.top=0;
				myRect.left=0;
				myRect.bottom=100;
				myRect.right=300;
				RedrawWindow(hDlg,&myRect,NULL, RDW_INTERNALPAINT);
			}
			
			if (LOWORD(wParam) == IDT_PAUSE_LOCK)
			{
				lockGlobalPause=false;
			}	
			break;	

      default :
            return( DefWindowProc( hDlg, message, wParam, lParam ));

	}
	return 0L;
}

void reset()
{
	running=false;
	pause=false;
}

void start()
{
	fadeOut();	
	sound(START_BEEP);	
	clear();
	startTime=GetTickCount();
	running=true;
	pause=false;
	valid=false;
}

void globalPause()
{
	if(lockGlobalPause) return;						//
	lockGlobalPause=true;
	SetTimer(hDialog, IDT_PAUSE_LOCK, 1000, 0);
	if (running) 
	{ 
		sound(STOP_BEEP);
		running=false;
		globalPauseTime=GetTickCount();
		
		return;
	}
	if (!running) 
	{ 
		sound(START_BEEP);
		startTime+=GetTickCount()-globalPauseTime;
		localPauseStartTime+=GetTickCount()-globalPauseTime;
		running=true;
	
		return;
	}
}

 void stop()
 {
	 running=false;
	 pause=false;
	 sound(END_BEEP);
	 fadeIn();
 }

void localPause()
{
	lockJudging=false;
	//------------------
	defaultPauseTime = GetDlgItemInt(hDialog,IDC_PauseDefault,NULL,false);
	SetTimer(hDialog, IDT_PAUSETIMER, (defaultPauseTime)*1000, 0);
	SetTimer(hDialog, IDT_STARTWARNING, (defaultPauseTime-10)*1000, 0);
	
	sound(INTERRUPT_BEEP);
	
	
	

	localPauseStartTime=GetTickCount();
	running=false;
	pause=true;
	valid=true;
}

void resume()			//invalid
{
	if(lockInvalid) return;
	fadeOut();
	sound(INVALID_BEEP);
	clear();
	running=true;
	pause=false;
	localPauseStartTime=0;
	valid=false;
	KillTimer(hDialog,IDT_STARTWARNING);
}

void cont()				//valid
{
	startTime+=defaultPauseTime*1000;
	running=false;
	pause=true;
	valid=true;
	lockInvalid=true;
	
}

void clear()
{
	TeamA=false;
	ClearDigitalChannel(1);
	TeamB=false;
	ClearDigitalChannel(2);
	// ADDENDUM
	running=true;
	pause=false;
	//defaultPauseTime=0;
	KillTimer(hDialog,IDT_PAUSETIMER);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), (HWND)hwnd, (DLGPROC)DialogProc);
	MessageBox(NULL, L"Beenden?", L"Beenden?", MB_OKCANCEL | MB_ICONQUESTION);
	return 0;
}

int signal;

void sound(int sound)
{
	signal=sound;
	DWORD dwID;
    HANDLE threadHandle = CreateThread(NULL,NULL,
                           (LPTHREAD_START_ROUTINE)BeepThread,
                           NULL, NULL, &dwID);		
}

LONG BeepThread(LPVOID pParam)
{
	switch (signal)
	{
	case START_BEEP:			//vorlaufzeit anpassen
		fadeOut();
		Beep(600,100);
		Sleep(900);
		Beep(600,100);
		Sleep(900);
		Beep(600,100);
		Sleep(900);
		Beep(1200,100);
	break;
	case STOP_BEEP:
		Beep(1200,100);
		Sleep(900);
		Beep(600,100);
		fadeIn();
	break;
	case END_BEEP:
		Beep(4000,100);
		Beep(3000,100);
		Beep(2000,100);
		Beep(1000,100);
		Beep(500,100);
		Beep(250,100);
		fadeIn();
	break;
	case INVALID_BEEP:
		Beep(600,250);
		Beep(50,100);
		Beep(600,500);
	break;
	case INTERRUPT_BEEP:
		Beep(600,500);
		fadeIn();
	break;
	case PREWARN_BEEP:
		fadeOut();
		Beep(600,1000);
	break;
	case CONTINUE_BEEP:
		Beep(1200,500);
	break;
	}
	return 0;
}