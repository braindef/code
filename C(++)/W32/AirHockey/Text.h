#ifndef Text_h

int g_InitText (void);
int g_PrintText(int color, const char* list,...);
int g_DrawText(int color, int x, int y, const char* list,...);
int g_DrawCompleteText (void);
int g_DrawCursor(int p,int x,int y);

extern int textw,texth;

#endif
#define Text_h 