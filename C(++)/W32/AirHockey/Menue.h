#ifndef Menue_h

class g_MenueItem
{
public:
	char* text; //Text des Menüpunktes
	void (*MenueFunc)(void); //Funktion die ausgeführt wird wenn der Menüpunkt angeklickt wird
	int sx,bx; //koordinaten eines Rechtecks um den Text, mit Hilfe dessen
	int sy,by; //wir überprüfen können ob die Maus über einem Menü´punkt steht

	g_MenueItem* next; //Zeiger auf das nächste g_MenueItem Objekt.
};

class g_Menue
{
public:
	void Init(char* nname); //Initialisierung
	int Add(char* ntext, void(*MFunc)(void)); //Hinzufügen eines Menüpunktes zum Menü
	int DrawMenue(int x, int y); //Zeichnen des Menüs
	int ExecMenue(int x, int y); //Ausführen der Funktion des jeweiligen Menüpunktes auf den die Maus klickt

	int GetItems(void); //Anzahl der Menüpunkte abfragen

private:
	int items; //Anzahl der Menüpunkte
	char* name; //name/Überschrift des Menüs

	g_MenueItem* start; //Zeiger auf das erste Objekt der Linked-List
};

void g_Start(void);
void g_Optionen(void);

#endif
#define Menue_h
