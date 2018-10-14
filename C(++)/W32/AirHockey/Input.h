#ifndef Input_h

extern LPDIRECTINPUT8				Di;	
extern LPDIRECTINPUTDEVICE8			Dikeyboard;	
extern LPDIRECTINPUTDEVICE8			Dimouse;
extern char							Keys[256];
extern int							MouseX,MouseY;
extern char							MouseB;

#define Taste(b) (Keys[b] & 0x80)

int g_InitDi(void);
int g_CreateDIStandartDevices(void);
int g_CreateDIMouseDevice(void);
void g_GetKeyboardState(void);
void g_GetMouseState(void);

#endif
#define Input_h