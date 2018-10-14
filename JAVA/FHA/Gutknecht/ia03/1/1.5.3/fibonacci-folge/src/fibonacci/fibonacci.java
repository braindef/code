package fibonacci;  //meta-knall: historisches hierarchisches system

/**
 * <p>Title: Fibonacci Folge 1 1 2 3 5 8</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */

public class fibonacci {
  public static void main(String[] args) {
    int a = 1;  //int bis 32Bit -->kommt von c, überlauf, --> integer-klasse , ab welchen wert gibt es einen overflow bei int, bei integer
    int b = 1;
    for(int i=0; i < 11; i++) {  //für fibonacci bis 100 eignet sich while besser
      System.out.println(a);
      int c=a+b;
      a=b;
      b=c;
    }
  }
}