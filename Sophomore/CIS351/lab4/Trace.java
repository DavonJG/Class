 import java.io.*;

public class Trace {
  ////////////////////////////////////////////////////////////////////////
  // Class variables

  ////////////////////////////////////////////////////////////////////////
  // Instance variables
  String name;
  static int d = 0; //used in Spaces
  
  //The indenting trick works because d is a class variable since it is static, meaning that it all of the classes
  //share the same variable. This allows the indenting to always be correct when used in Spaces()
  
  ////////////////////////////////////////////////////////////////////////
  // This constructor stores the name String and prints out an
  // ``Entering'' message
  
  public Trace(String n) {
    name = n;
    Spaces(2*d); //print spaces before the rest
    System.out.println(">> Entering: " + name);
  }
  
  ////////////////////////////////////////////////////////////////////////
  // This constructor stores the name String and prints out an
  // `Entering'' message using the name and the extra information
  // supplied in the String with.
  
  public Trace(String n, String with) {
    name = n;
    d++;
    Spaces(2*d);
    System.out.println(">> Entering: " + name + " with: " + with);
  }
  
  ////////////////////////////////////////////////////////////////////////
  // This method prints a farewell message when invoked.
  public void bye(String s) {
    d--;
    Spaces(2*d);
    System.out.println("<< Leaving:  " + name + " " + s);
  }
  
  ////////////////////////////////////////////////////////////////////////
  // Given an integer n, this method prints n blank spaces on the
  // current line of output.
  
  private void Spaces(int n) {
    for (int i=0; i<n; i++ ) System.out.print(" ");
  }
  ////////////////////////////////////////////////////////////////////////
}


