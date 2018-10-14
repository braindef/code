package schachbrett;

/**
 * <p>�berschrift: Schachbrett aufgabe</p>
 * <p>Beschreibung: </p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Organisation: al kaida</p>
 * @author Marc Landolt
 * @version 0.1
 */

//Startbedingung (weiss oder schwarz)
//n x n Schachbrett
//Kantenl�nge / a = n = 8
//Startkoordinaten (100,100)
//Feldchenbreite a = 20

//TODO ...grep...
//als komplexe zahlen darstellen? <---
//while(i<=n/2), rekursion <---
//man kann damit noch ein bisschen spielen, BZW permutieren und z.b. in der mitte anfagnen, oder unten oder abwechslungsweise?<--


import java.applet.*;
import java.awt.*;

public class Schachbrett extends Applet{
  public Schachbrett() {
  }

  public void init() {
    setBackground(Color.blue);
  }

  public void paint(Graphics g) {
    zeichneSchachbrett(100, 100, 12, 8, g);
  }

public static void zeichneSchachbrett(int x, int y, int a, int n, Graphics g) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if(i%2==j%2) {
          g.setColor(Color.black);
          g.fillRect(x+i*a, y+j*a, a, a);
        }
        else {
          g.setColor(Color.white);
          g.fillRect(x+i*a, y+j*a, a, a);
        }
      }
    }
  }
}