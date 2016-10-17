import java.io.*;
import java.util.Scanner;

public class CCount {
  /** Counts the number of characters making up the file in.   
    * Note: FileReader is class for reading character files.   
    * If in is a FileReader, in.next() returns the next char   
    * (as an int).  When the end-of-file is reached, in.next() 
    * returns -1.                                              
    */
  public static int countChars(FileReader in) 
    throws IOException 
  {
    int count = 0;  
    while (in.read() != -1) count++;
    in.close();
    return count;
  }

  /** Prompt the use for the name of a text file and then report 
    * the number of characters in that file. 
    */
  public static void main(String argv[]) 
    throws IOException 
  {
    boolean done = false;    // may be useful
    int attempt = 0;         // may be useful
    final int tryLimit = 2;  // may be useful
    
    String fileName;
    Scanner stdin = new Scanner(System.in);
    FileReader infile;
    
    System.out.print("Name of the input file: ");  // user prompt
   
    /** Beginning of the part to play with   **/
    int x = 0;
    while(x<2){ // keep the try catch statements in a loop to repeat until the user tries twice.
      try{
        fileName = stdin.next();                       // get name from user
        infile = new FileReader(new File(fileName));   // open that file as a FileReader
        System.out.println("That file has " + countChars(infile) + " characters.");
        x += 5; //add enough to get the program out of all cases.
      }
      catch(FileNotFoundException e){
        if(x==1){ //if the user is on their second try:
          System.out.println("Sorry, too many bad inputs.");
          return; //terminate the program
        }
        else{
          System.out.println("That file doesn't exist! Try again.");
          x++;
        }
      }
    }
    /**  Ending of the part to play with     **/ 
      

    stdin.close();
  }
}