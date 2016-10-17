import java.io.*;

public class Bugs2 {
  public static void main(String argv []) {
    int cash = 20;
    
    if (cash==0) //added missing = sign
      System.out.println("You are broke."); //added missing ;
    else
      System.out.println("You are solvent.");
  }
}

//fixed indentation
