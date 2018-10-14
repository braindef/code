#include "GDef.h"
#include "Utilities.h"


//Initialisierung der Protokoll.txt
int g_InitUtilities ()
{
	FILE* prot;

	prot = fopen("Protokoll.txt","w+r");

	fprintf(prot,"Started %s",AHVER);

	fclose(prot);

	return OK;
}


//Praktische Funktion um ins Protokoll zu schreiben
int g_PrintProt (const char* list,...)
{
	va_list valist;
	FILE* prot;

	va_start(valist,list);
	prot = fopen("Protokoll.txt","r+");
	fseek(prot ,0 , SEEK_END);
	vfprintf(prot,list,valist);
	fclose(prot);
	va_end(valist);

	return OK;
}


//Praktische Funktion für Fehler die zum Programmabbruch oder eben zu keinem abbruch führen
int g_FailBox (int end,const char* list,...)
{
	va_list valist;
	FILE* prot;
	char* error;

	va_start(valist,list);
	prot = fopen("Protokoll.txt","a");
	fseek(prot ,0 , SEEK_END);
	error = new char[strlen(list)+256];
	vsprintf(error,list,valist);
	fprintf(prot,error);
	fclose(prot);
	va_end(valist);

	MessageBox(NULL, error, AHVER, MB_OK | MB_ICONEXCLAMATION);

	if(end > 0) g_Shutdown();

	return OK;
}


