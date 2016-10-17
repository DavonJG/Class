import java.util.Scanner;
import java.io.*;

/*Sales.java
 Davon Grant
 dgran101
 Section 4
 */

//was confused between divisions vs quarters the entire time...
public class Sales{
  public static void main(String[]args)throws IOException{
    //declare instance data and ask for inputs
    Scanner scan = new Scanner(System.in);
    System.out.println("What is the name of your sales data file? (Don't include .txt)");
    String selection = scan.nextLine();
    File dataFile = new File(selection+".txt");
    boolean fileExists = dataFile.exists();
    if(fileExists==false){
      System.out.println("The file does not exist! Closing program...");
      System.exit(1);
    }
    Scanner dataScan = new Scanner(dataFile);
    double[][] quarterlySales = new double[6][4];
    //store all the data in a 2d array and close if it has negative data
    for(int r=0;r<6;r++){
      for(int c=0;c<4;c++){
        quarterlySales[r][c]=dataScan.nextDouble();
        if(quarterlySales[r][c]<0){
          System.out.println("No negative values! Program closing...");
          System.exit(1);
        }
      }
    }
    
    //print all sales figures
    for(int r=0;r<6;r++){
      System.out.print("Sales figures in division "+(r+1)+":");
      for(int c=0;c<4;c++){
        System.out.print(" $" + quarterlySales[r][c]+"\t");
      }
      System.out.println();
    }
    
    //calculate the total of all divisions
    double div1Total =0;
    double div2Total =0;
    double div3Total =0;
    double div4Total =0;
    for(int c=0;c<4;c++){
      div1Total += quarterlySales[0][c];
    }
    for(int c=0;c<4;c++){
      div2Total += quarterlySales[1][c];
    }
    for(int c=0;c<4;c++){
      div3Total += quarterlySales[2][c];
    }
    for(int c=0;c<4;c++){
      div4Total += quarterlySales[3][c];
    }
    
    //get the highest sales per quarter
    double highestdiv1Sales =0;
    int highestdiv1SalesIndex=0;
    for(int r=0;r<6;r++){
      if(quarterlySales[r][0]>highestdiv1Sales){
        highestdiv1Sales = quarterlySales[r][0];
        highestdiv1SalesIndex=r;
      }
    }
    double highestdiv2Sales =0;
    int highestdiv2SalesIndex=0;
    for(int r=0;r<6;r++){
      if(quarterlySales[r][1]>highestdiv2Sales){
        highestdiv2Sales = quarterlySales[r][1];
        highestdiv2SalesIndex=r;
      }
    }
    double highestdiv3Sales =0;
    int highestdiv3SalesIndex=0;
    for(int r=0;r<6;r++){
      if(quarterlySales[r][2]>highestdiv3Sales){
        highestdiv3Sales = quarterlySales[r][2];
        highestdiv3SalesIndex=r;
      }
    }
    double highestdiv4Sales =0;
    int highestdiv4SalesIndex=0;
    for(int r=0;r<6;r++){
      if(quarterlySales[r][3]>highestdiv4Sales){
        highestdiv4Sales = quarterlySales[r][3];
        highestdiv4SalesIndex=r;
      }
    }
    
    //print the requested data
    System.out.println();
    System.out.println("Quarter 1 Stats:\nTotal sales: $"+div1Total+"\nChange from previous quarter:N/A\nAverage sales: $"+(div1Total/4.0)+"\nDivision with highest sales: "+(highestdiv1SalesIndex+1));
    System.out.println();
    System.out.println("Quarter 2 Stats:\nTotal sales: $"+div2Total+"\nChange from previous quarter: $"+(div2Total-div1Total)+"\nAverage sales: $"+(div2Total/4.0)+"\nDivision with highest sales: "+(highestdiv2SalesIndex+1));
    System.out.println();
    System.out.println("Quarter 3 Stats:\nTotal sales: $"+div3Total+"\nChange from previous quarter: $"+(div3Total-div2Total)+"\nAverage sales: $"+(div3Total/4.0)+"\nDivision with highest sales: "+(highestdiv3SalesIndex+1));
    System.out.println();
    System.out.println("Quarter 4 Stats:\nTotal sales: $"+div4Total+"\nChange from previous quarter: $"+(div4Total-div3Total)+"\nAverage sales: $"+(div4Total/4.0)+"\nDivision with highest sales: "+(highestdiv4SalesIndex+1));
    
    
  }
}