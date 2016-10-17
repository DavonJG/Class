/* DrawShapes.java
Davon Grant
dgran101
Section 4
*/

import java.util.Scanner;

public class DrawShapes{
  public static void main(String[]args){
    Scanner scan = new Scanner(System.in);
    System.out.println("Welcome to the shape machine!\n");
    String input;
    do{
    System.out.println("Pick a shape:\nA)square\nB)triangle\nC)quit");
    input = scan.nextLine();
    }
    while(!(input.equalsIgnoreCase("a"))&&!(input.equalsIgnoreCase("b"))&&(!(input.equalsIgnoreCase("c"))));
    
    //based on the user input, determine which method to run
    if(input.equalsIgnoreCase("a")){
      drawSquare();
    }
    else if(input.equalsIgnoreCase("b")){
      drawTriangle();
    }
    else if(input.equalsIgnoreCase("c")){
      System.exit(0);
    }
  }
  
  //draw a square using x's
  public static void drawSquare(){
    Scanner scan = new Scanner(System.in);
    System.out.println("What size is a side?");
    int sideLength = scan.nextInt();
    drawLine('x', sideLength);
    System.out.println();
    for(int counter=0;counter<sideLength-2;counter++){
      System.out.print('x');
      for(int counter2=0;counter2<sideLength-2;counter2++){
        System.out.print(" ");
      }
      System.out.print('x');
      System.out.println();
    }
    drawLine('x', sideLength);
  }
  
  //draw a triangle using the symbol that is given
  public static void drawTriangle(){
    Scanner scan = new Scanner(System.in);
    System.out.println("What is the altitude of the triangle?");
    int altitude = scan.nextInt();
    System.out.println("What is the base of the triangle?");
    int base = scan.nextInt();
    System.out.println("What symbol should fill the triangle?");
    scan.nextLine();
    String symString = scan.nextLine();
    char sym = symString.charAt(0);
    int numSym;
    for(int counter =0; counter<altitude;counter++){
      numSym = altitude-counter;
      drawLine(sym, numSym);
      System.out.println();
    }
  }
  
  public static void drawLine(char sym, int num){ //drawLine method
    for(int counter = 0; counter<num; counter++){
      System.out.print(sym);
    }
  }
}
/*Outputs:
Welcome to the shape machine!
 
Pick a shape:
A)square
B)triangle
C)quit 
b
What is the altitude of the triangle? 
5
What is the base of the triangle? 
3
What symbol should fill the triangle? 
@
@@@@@ 
@@@@ 
@@@ 
@@ 
@ 
____________________________________________________________________

Welcome to the shape machine!
 
Pick a shape:
A)square
B)triangle
C)quit 
a
What size is a side? 
7
xxxxxxx 
x     x 
x     x 
x     x 
x     x 
x     x 
xxxxxxx
*/