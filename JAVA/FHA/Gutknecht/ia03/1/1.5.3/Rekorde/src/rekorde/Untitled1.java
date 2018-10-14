package rekorde;

/**
 * <p>Title: Rekorde</p>
 * <p>Description: 100 Rekorde, Mathematische Lösung?</p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Company: </p>
 * @author M.Landolt
 * @version 1.0
 */

public class Untitled1 {
  public static void main(String[] args) {
    int n=0;
    double wurf=0;
    int rekorde=0;//-1
    double rekord=0;
    for (n=0; n<100; n++) {     //oder while mit einer Variabel weniger?,  oder oder.-...
      wurf=Math.random();
      if (wurf>rekord) {
        rekorde++;
        rekord=wurf;
        System.out.print("Rekord: ");
      }
      System.out.println(wurf);
    }
    System.out.print("Total Rekorde: "); //konkationierungsoperator +
    System.out.println(rekorde);
  }
}

//FH-Nord: 258, code red, f(x) vs f(a) --> ' -->
//"Angst ist kein guter Begleiter"
// eiffel: n_rekorde, auch ada
//hittler hat am schluss gesponnen
//man muss den scientologen, den Verbindungstypen ect und so weiter ihre "perspektiven" lassen, sie wollen sich nicht bekehren lassen
//prof droht bei grimasse mit rausschmiss, damit het er bewisen, dass die FH nichts mit bildung sondern mit homöostase zu tun hat.
//arme bilder, dolch --> zeile-- lim
//wenn er sich angegriffen fühlt fängt er mit assembler an --> homöostase seines geistes, -->krank
//nicht drogenkonsumenten sind SCHÜTZENSWERT, da drogensysteme homöostatisch --> FILZ, macht,
//gabe:jeder der studiert hat hat einen knall.... da ist was drann, jedoch ist diese these falsifizierbar