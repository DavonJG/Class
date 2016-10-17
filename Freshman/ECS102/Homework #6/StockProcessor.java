import java.util.Scanner;
import java.io.*;

public class StockProcessor{
  public static void main(String[]args) throws IOException{
    String fileName;
    Scanner scan = new Scanner(System.in);
    System.out.println("Hello! What is the name of the file that we will be working with?");
    fileName=  scan.nextLine();
    File inputFile = new File(fileName+".txt");
    Scanner fileScan = new Scanner(inputFile);
    PrintWriter printer = new PrintWriter(fileName+"Profit.txt");
    
    //instance variables
    String name="h";
    double pp, pc, sc, sp;
    int ns;
    double finalProfit=0.0;
    int counter = 0;
    
    while(fileScan.hasNext()){ //loop until the end of the file collecting and outputting data. How do you do this without catching an exception...
      //inside of loop works fine and records all data, but couldn't figure out how to properly loop
      //to the end of the file.
      counter++;
      name = fileScan.nextLine();
      ns = fileScan.nextInt();
      pp = fileScan.nextDouble();
      pc = fileScan.nextDouble();
      sp = fileScan.nextDouble();
      sc = fileScan.nextDouble();
      finalProfit += computeProfit(pp,pc,ns,sc,sp);
      printer.println("The "+name+" stock has "+ns+" shares and a total profit of "+computeProfit(pp,pc,ns,sc,sp));
      fileScan.nextLine();
    };
    
    //final results of all the stocks
    System.out.println("There are "+counter+" stocks. The total profit is "+finalProfit);
    printer.print("There are "+counter+" stocks. The total profit is "+finalProfit);
    printer.close();
  }
  
  //uses the computeProfit method found in the textbook.
  public static double computeProfit(double pp, double pc, int ns, double sc, double sp){
    double finalProfit = (((ns*sp)-sc)-((ns*pp)+pc));
    return finalProfit;
  }
}