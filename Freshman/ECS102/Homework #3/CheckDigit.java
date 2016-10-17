/*  CheckDigit.java
Davon Grant
dgran101
Section 4 */

import java.util.Scanner; //import Scanner class

public class CheckDigit{
  public static void main(String[]args){
    Scanner scan = new Scanner(System.in); 
    
    //Ask for the user's input and store it
    System.out.println("What is your bank account number?");
    int bankNumber = scan.nextInt();
    
    // If the number that the user entered has less than 4 digits
    // then tell the user that their number is invalid.
    if(bankNumber < 1000){
      System.out.println(bankNumber + " is a fake account number!");
    }
    
    
    //If the sum of the first 3 numbers is even, make sure there is a 0 before
    //confirming it is a valid account number.
    int result = ((bankNumber/1000)+(bankNumber/100)+(bankNumber/10));
    if(result%2==0){
      if(bankNumber%10==0){ //If the check digit is a 0, it is valid.
        System.out.println(bankNumber + " is a valid account number.");
      }
      else if(bankNumber%10==1){
        System.out.println(bankNumber + " is a fake account number!");
      }
    }
    
    //If the sum of the first 3 numbers is odd, make sure there is a 1 before
    //confirming it is a valid account number.
    else if(result%2==1){
      if(bankNumber%10==0){ //If the check digit is a 0, it is a fake account number.
        System.out.println(bankNumber + " is a fake account number!");
      }
      else if(bankNumber%10==1){
        System.out.println(bankNumber + " is a valid account number.");
      }
    }
  }
}

/***********************************************
  * Sample Output 1:
  * What is your bank account number? 
  * 482
  * 482 is a fake account number! 
  * 
  * Sample Output 2:
  * What is your bank account number? 
  * 5821
  * 5821 is a valid account number. 
  * 
  * Sample Output 3:
  * What is your bank account number? 
  * 8200
  * 8200 is a valid account number. 
  * ********************************************/