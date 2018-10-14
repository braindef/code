#include "GDef.h"
#include "Utilities.h"
#include "Input.h"



LPDIRECTINPUT8				Di;	
LPDIRECTINPUTDEVICE8		Dikeyboard;	
LPDIRECTINPUTDEVICE8		Dimouse;
char						Keys[256];
int							MouseX,MouseY;
char						MouseB;



int g_InitDi(void)
{
	int r = 0;	

	r = DirectInput8Create(HInstance ,DIRECTINPUT_VERSION ,IID_IDirectInput8 ,(void**)&Di ,NULL);	
		if(FAILED(r)) g_FailBox(1,"Failed to create DirectInput Object!");

	r = g_CreateDIStandartDevices();
		if(FAILED(r)) return r;

	r = g_CreateDIMouseDevice();
		if(FAILED(r)) return r;

	MouseX = MouseY = MouseB = 0;

	return OK;
}



int g_CreateDIStandartDevices(void)
{	
	int r = 0;	

	r = Di->CreateDevice(GUID_SysKeyboard ,&Dikeyboard ,NULL);	
		if(FAILED(r)) g_FailBox(1,"Failed to Create Keyboard Device!");

	r = Dikeyboard->SetDataFormat(&c_dfDIKeyboard);	
		if(FAILED(r)) g_FailBox(1,"Failed to Set Keyboard Data Format1");	
		
	r = Dikeyboard->SetCooperativeLevel(Hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(r)) g_FailBox(1,"Failed to Set Keyboard Cooperative Level!");

	r = Dikeyboard->Acquire();	

	return OK;
}


//Funktion zur Mausinitialisierung
int g_CreateDIMouseDevice(void)
{
	int r = 0;	

	//Device mit dem GUID der Standartmaus erzeugen
	r = Di->CreateDevice(GUID_SysMouse ,&Dimouse ,NULL);	
		if(FAILED(r)) g_FailBox(1,"Failed to Create Mouse Device!");
	//Device Format setzen, dieses mal aber auf das einer Maus, also z.B. c_dfDIMouse	
	r = Dimouse->SetDataFormat(&c_dfDIMouse);	
		if(FAILED(r)) g_FailBox(1,"Failed to Set Keyboard Data Format1");	
	//Wie beim Keyboard den Cooperative Level setzen	
	r = Dimouse->SetCooperativeLevel(Hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(r)) g_FailBox(1,"Failed to Set Keyboard Cooperative Level!");
	//Und eben erst mal darauf zugreifen
	r = Dimouse->Acquire();
	
	return OK;
}



void g_GetKeyboardState(void)
{
	Dikeyboard->GetDeviceState(sizeof(Keys) ,&Keys);	//Lies den Zustand des Keyboard-Devices
}

//Funktion zur Maus-Device-State-Abfrage
void g_GetMouseState(void)
{
	DIMOUSESTATE stat; //Eben der richtige Maus-Daten-Format

	//Wie beim Keyboard den Device State abfragen
	Dimouse->GetDeviceState(sizeof(stat) ,&stat); 

	//In stat sind lX und lY abgelegt, die die relative Veränderung der Maus-Position angeben!
	//In den globalen MouseX und MouseY Variablen verrechnen wir dann diese Veränderung
	MouseX += stat.lX;
	MouseY += stat.lY;

	//In MouseB speichern wir im ersten Bit den Zustand der linken Maustaste im zweiten Bit den der Rechten
	MouseB = ((stat.rgbButtons[0] >> 1) | stat.rgbButtons[1]) >> 6;
}
