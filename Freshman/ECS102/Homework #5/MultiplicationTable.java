/*  MultiplicationTable.java
Davon Grant
dgran101
Section 4*/

import java.util.Scanner;
import java.io.*;

public class MultiplicationTable{
  public static void main(String[]args)throws IOException{
    
    //declare needed variables
    Scanner scan = new Scanner(System.in);
    System.out.println("Enter the upper limit:");
    int input = scan.nextInt();
    int temp;
    PrintWriter tableFile = new PrintWriter("Multiplication"+input+".txt");
    
    //LINE 1
    tableFile.print("\t");
    for(int counter = 1;counter<=input;counter++){
      tableFile.printf("%3d  |\t",counter);
    }
    tableFile.println();//create new line
    
    //LINE 2
    tableFile.print("-----");//beginning column of dashes
    //for loop which creates the second line (which is the remaining columns of dashes)
    for(int counter = 1;counter<=input;counter++){
      tableFile.print("|-------");
    }
    tableFile.print("|"); //the final | at the end of the second line
    tableFile.println();
    
    
    //ALL OF THE MIDDLE LINES + CALCULATIONS
    for(int counter =1;counter<=input;counter++){
      tableFile.printf("%3d  |\t",counter); //setup the formatting
      for(int counter2=1;counter2<=input;counter2++){
        temp = counter*counter2; //store the correct product into a temp variable
        tableFile.printf("%3d  |\t",temp); //print the correct products
      }
      tableFile.println();//create a new line each time the loop is run
    }
    
    //FINAL LINE
    tableFile.print("-----");//beginning indent
    for(int counter = 1;counter<=input;counter++){
      tableFile.print("|-------");
    }
    tableFile.print("|");
    tableFile.close();
  }
}
  