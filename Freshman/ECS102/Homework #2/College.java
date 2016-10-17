/* College.java
 Davon Grant
 Section 4
 netID: dgran101 */

//import Scanner class
import java.util.Scanner;

public class College{
  public static void main(String[]args){
    
    //Instantiate the needed scanner
    Scanner input = new Scanner(System.in);
    
    //Ask for the needed information and store them in strings.
    System.out.println("Enter your hometown.");
    String userHometown = input.nextLine();
    System.out.println("Enter your the name of a family member back home");
    String userFamilyMember = input.nextLine();
    
    //Output all of the information using the user's input
    System.out.println("\nWelcome to S.U. You will be working hard.\nNow you will miss " + userFamilyMember + "\nIn a few months you will go back to " + userHometown + "\nand tell " + userFamilyMember + " all about SU.");
    }
}

/**********************************
Output:

Enter your hometown. 
New York
Enter your the name of a family member back home 
Aunt Lisa

Welcome to S.U. You will be working hard.
Now you will miss Aunt Lisa
In a few months you will go back to New York
and tell Aunt Lisa all about SU.  

Output 2:
Enter your hometown. 
Bronx
Enter your the name of a family member back home 
Mom

Welcome to S.U. You will be working hard.
Now you will miss Mom
In a few months you will go back to Bronx
and tell Mom all about SU. 

Output 3:
Enter your hometown. 
Alaska
Enter your the name of a family member back home 
Yeti

Welcome to S.U. You will be working hard.
Now you will miss Yeti
In a few months you will go back to Alaska
and tell Yeti all about SU. 

************************************/