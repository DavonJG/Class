/*  NobelGases.java
Davon Grant
dgran101
Section 4 */

import java.util.Scanner; //import Scanner classes

public class NobelGases{
  public static void main(String[]args){
    Scanner scan = new Scanner(System.in); //declare Scanner
    
    //ask for user input
    System.out.println("Enter the atomic symbol: ");
    String userInput = scan.nextLine();
    
    //Print messages based on what the user enters.
    if(userInput.compareToIgnoreCase("he") == 0){
      System.out.println("The atomic number of He is 7.");
    }
    else if(userInput.compareToIgnoreCase("ne") == 0){
      System.out.println("The atomic number of Ne is 10.");
    }
    else if(userInput.compareToIgnoreCase("ar") == 0){
      System.out.println("The atomic number of Ar is 18.");
    }
    else if(userInput.compareToIgnoreCase("kr") == 0){
      System.out.println("The atomic number of Kr is 36.");
    }
    else if(userInput.compareToIgnoreCase("xe") == 0){
      System.out.println("The atomic number of Xe is 54.");
    }
    else if(userInput.compareToIgnoreCase("rn") == 0){
      System.out.println("The atomic number of Rn is 86.");
    }
    else{
      System.out.println(userInput + " is not a noble gas.");
    }
}
}

/************************
  * Sample Output 1:
  * 
  * Enter the atomic symbol:  
  * kr
  * The atomic number of Kr is 36. 
  * 
  * Sample Output 2:
  * Enter the atomic symbol:  
  * ar
  * The atomic number of Ar is 18. 
  * 
  * Sample Output 3:
  * Enter the atomic symbol:  
  * NE
  * The atomic number of Ne is 10. 
  * ********************/