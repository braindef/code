#ifndef Menue_h

class g_MenueItem
{
public:
	char* text; //Text des Men�punktes
	void (*MenueFunc)(void); //Funktion die ausgef�hrt wird wenn der Men�punkt angeklickt wird
	int sx,bx; //koordinaten eines Rechtecks um den Text, mit Hilfe dessen
	int sy,by; //wir �berpr�fen k�nnen ob die Maus �ber einem Men��punkt steht

	g_MenueItem* next; //Zeiger auf das n�chste g_MenueItem Objekt.
};

class g_Menue
{
public:
	void Init(char* nname); //Initialisierung
	int Add(char* ntext, void(*MFunc)(void)); //Hinzuf�gen eines Men�punktes zum Men�
	int DrawMenue(int x, int y); //Zeichnen des Men�s
	int ExecMenue(int x, int y); //Ausf�hren der Funktion des jeweiligen Men�punktes auf den die Maus klickt

	int GetItems(void); //Anzahl der Men�punkte abfragen

private:
	int items; //Anzahl der Men�punkte
	char* name; //name/�berschrift des Men�s

	g_MenueItem* start; //Zeiger auf das erste Objekt der Linked-List
};

void g_Start(void);
void g_Optionen(void);

#endif
#define Menue_h
