package fensterdimensionen;

/**
 * <p>Überschrift: Herausholen des Fensters im Browser</p>
 * <p>Beschreibung: </p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Organisation: al kaida</p>
 * @author Marc Landolt
 * @version 0.1
 */

public class FensterDimension extends java.applet.Applet{

  public void init() {}

  public void paint(java.awt.Graphics g) {
    java.awt.Dimension dim = getSize();      //TODO
    int width = dim.width;
    int height = dim.height;
    int xm= width/2, ym=height/2;            //Mittelpunkt d. Windows
    int n=8, a=20;
    int left= xm-2*n/2;
    int right= ym-2*n/2;
    Rest unverändert                         //Dinge die ausserhalb des Fensters sind werden nicht! dargestellt

  }


}