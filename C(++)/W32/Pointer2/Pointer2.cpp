// 
// Marc Landolt (http://ml.buzzernet.com), 15.04.2007
//

#include "Pointer2.h"									//eine Headerdatei für schön
#include "stdio.h"										//für printf und scanf die wir in unserem Programm brauchen

int main(int argc, char* argv[])						//main ist die routine, die vom Betriebssystem aufgerufen wird...
														//ARGumentCount ist die Anzahl Parameter und ARGumentValue sind die Parameter
{
	printf("Pointer Test (Details im Source)\n");		//printf steht für "Print Formated" also gib den Text formatiert aus das \n bedeutet "Neue Linie"
	printf("--------------------------------\n\n");		//es ist eine sogenannte Escape-Sequenz die jeweils durch \ eigeleitet wir, also 2 Zeilen nach unten

	int a0;												//wir definieren eine Variabel a0 als integer (Vorzeichenbehaftete Ganzzahl)
	a0 = 7;												//und geben ihr den wert 7

	printf("a0 hat den Wert: %d und liegt an ", a0);	//der wert von a0 wird beim Text an der stelle %d eingefügt
	printf("der virtuellen Adresse %p \n\n", &a0);		//das & vor einer Varialel liefert uns die Adresse wo der Wert gespeichert ist
														//das %p stellt uns diese auch im Format einer Adresse dar (s. PrintfParameters.txt)

	unsigned int *a1;									//es wird ein Pointer (mit Sternchen) *a1 für eine nicht-vorzeichenbehaftete (unsigned) Ganzzahl erzeugt.
														//(dies ist eine Stelle im Heap mit einer Adresse, die im Moment noch ins Nirvana zeigt)
	//printf("unser Nirvana: %d", a1);					//würden wir hier versuchen darauf zuzugreifen, würden wir einen Fehler bekommen

	a1 = new unsigned int;								//der Integer wird nun erzeugt (new) und an die Stelle wo a1 hinzeigt geschrieben, 
														//"new int" gibt nämlich die Adresse des neuen Ganzzahl zurück
														//(im heap ist nun ein pointer "a1" an einer Speicherstelle und zeigt auf eine andere "*a1" die den neuen int enthält)
	printf("Zeiger auf die Adresse: %p ", a1);
	printf("und ihr aktuellen Inhalt: %u\n", *a1);
	
	*a1 = 123;											//der Speicher wo a1 hinzeigt wird mit 123 beschrieben, nicht aber der Pointer auf diesen Speicher, der bleibt gleich

	printf("Zeiger noch wie vorher: %p, enthaltener Wert nun: %d \n\n", a1, *a1);

	int *a2 = new int[3];								//es wird ein Pointer erstellt, der auf den Anfang eines Arrays (Feldes) aus 3 neue int's zeigt, mit der new Anweisung werden diese gleich angelegt
	a2[0]=-100;											//wir beschreiben den ersten mit -100 den zweiten mit -200 den 3. lassen wir leer
	a2[1]=-200;

	printf("1. Feld = %d   ", a2[0]);
	printf("2. Feld = %d   ", a2[1]);
	printf("3. Feld = %d\n\n", a2[2]);					//das dritte Feld des Arrays hatten wir ja nicht definiert

	//wir gehen nun hin und spielen ein bisschen mit den Adressen
	int *p = &a2[0] + 1;								//wir erstellen einen neuen Pointer *p und geben ihm die Adresse von a2[0] + 1
														//a2[0] ist die erste Adresse useres Feldes, addieren wir eins dazu, sollten
														//wir ja theoretisch zur zweiten kommen:

	printf("Alte Pointeradresse: %p, enthaltener Wert: %d \n", &a2[0], a2[0]);
	printf("Neue Pointeradresse: %p, enthaltener Wert: %d \n\n", p, *p);
	
	printf("Weiter mit Enter!");
	scanf(new char);									//hier warten wir auf eine Eingabe die durch einen Enter abgschlossen wird und schicken sie
														//sozusagen ins Nirvana, da wir ja die Adresse des neuen Zeichens nirgens ablegen

	return 1;											//dies ist der Rückgabewert an das Betriebssystem, welcher dann am CLI allenfalls
														//ausgewertet werden könnte siehe test.cmd im debug Verzeichnis
}
