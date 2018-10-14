package uhr;

/**
 * Überschrift:   Uhr
 * Beschreibung:
 * Copyright:     Copyright (c) 2002
 * Organisation:  keine
 * @author Marc Landolt
 * @version 1.01
 */

import java.awt.*;
import java.math.*;


public class AnalogUhr extends Frame {


  private int h, m, s;

  public AnalogUhr(int[] zeit) {

    this.h=zeit[0];
    this.m=zeit[1];
    this.s=zeit[2];

    setTitle("Analog Uhr");
    setSize(200,200);
    setResizable(false);
    setVisible(true);
  }

  public void paint(Graphics g) {

    int mittelpunktX = 100;
    int mittelpunktY = 100;

    //h=20;
    //m=30;
    g.drawLine(mittelpunktX, mittelpunktY, (int)(40*Math.sin((h*60+m)*Math.PI/360) )+mittelpunktX, (int)(40*(-Math.cos((h*60+m)*Math.PI/360)) )+mittelpunktY);
    g.drawLine(mittelpunktX, mittelpunktY, (int)(60*Math.sin(m*Math.PI/30) )+mittelpunktX, (int)(60*(-Math.cos(m*Math.PI/30)) )+mittelpunktY);
    System.out.println(h+" "+m+" "+s);
    g.setFont(new Font("Helvetica",Font.PLAIN,12));
    int i;
    for (i=1; i<=12; i++) {

      g.drawString(Integer.toString(i),(int)(70*Math.sin(i*Math.PI/6) )+mittelpunktX-5, (int)(70*(-Math.cos(i*Math.PI/6)) )+mittelpunktY+6);
    }
  }

}