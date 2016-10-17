/* Bill.java
 Davon Grant
 Section 4
 netID: dgran101 */

import java.util.Scanner;

public class Bill{
  public static void main(String[]args){
    
    //Declare variables used in the program
    String buyerName;
    int numBagOfChips;
    double numPoundsOfSpinach, numDozenEggs;
    final double CHIPS_PRICE = 3.49;
    final double SPINACH_PRICE = 2.99;
    final double EGGS_PRICE = 1.89;
    
    //Ask the user for all of the information and store it in the variables declared earlier.
    Scanner input = new Scanner(System.in);
    System.out.println("Hello! How many bags of chips are you buying?");
    numBagOfChips = input.nextInt();
    System.out.println("Ok, you are buying " + numBagOfChips + " bags of chips. How many pounds of spinach are you buying?");
    numPoundsOfSpinach = input.nextDouble();
    System.out.println("Ok, so " + numBagOfChips + " bags of chips and " + numPoundsOfSpinach + " pounds of spinach. How many dozens of eggs are you buying?");
    numDozenEggs = input.nextDouble();
    input.nextLine();
    System.out.println(numBagOfChips + " bags of chips, "+ numPoundsOfSpinach + " pounds of spinach, and " +numDozenEggs + " dozen eggs. What is your name?");    
    buyerName = input.nextLine();
    
    //Display the needed information using the user's inputs
    double totalPrice = ((numBagOfChips*CHIPS_PRICE)+(numPoundsOfSpinach*SPINACH_PRICE)+(numDozenEggs*EGGS_PRICE));
    System.out.println("\nYour final bill is below:\n" + numBagOfChips + " bags of chips @ $3.49 each: $" + (numBagOfChips*CHIPS_PRICE) + "\n" + numPoundsOfSpinach + " pounds of spinach @ $2.99 each: $" + (numPoundsOfSpinach*SPINACH_PRICE) + "\n" + numDozenEggs + " dozen eggs @ $1.89 each: $" + (numDozenEggs*EGGS_PRICE));
    System.out.println("\nYour total is $" + totalPrice + ". Have a great day, " + buyerName + "!");
     }
}

/*****************************************************************
Output 1:

Hello! How many bags of chips are you buying? 
3
Ok, you are buying 3 bags of chips. How many pounds of spinach are you buying? 
2
Ok, so 3 bags of chips and 2.0 pounds of spinach. How many dozens of eggs are you buying? 
1
3 bags of chips, 2.0 pounds of spinach, and 1.0 dozen eggs. What is your name? 
Davon

Your final bill is below:
3 bags of chips @ $3.49 each: $10.47
2.0 pounds of spinach @ $2.99 each: $5.98
1.0 dozen eggs @ $1.89 each: $1.89 

Your total is $18.340000000000003. Have a great day, Davon! 

Output 2:
Hello! How many bags of chips are you buying? 
6
Ok, you are buying 6 bags of chips. How many pounds of spinach are you buying? 
8
Ok, so 6 bags of chips and 8.0 pounds of spinach. How many dozens of eggs are you buying? 
12
6 bags of chips, 8.0 pounds of spinach, and 12.0 dozen eggs. What is your name? 
Bob

Your final bill is below:
6 bags of chips @ $3.49 each: $20.94
8.0 pounds of spinach @ $2.99 each: $23.92
12.0 dozen eggs @ $1.89 each: $22.68 

Your total is $67.53999999999999. Have a great day, Bob! 

Output 3:
Hello! How many bags of chips are you buying? 
9
Ok, you are buying 9 bags of chips. How many pounds of spinach are you buying? 
8
Ok, so 9 bags of chips and 8.0 pounds of spinach. How many dozens of eggs are you buying? 
6
9 bags of chips, 8.0 pounds of spinach, and 6.0 dozen eggs. What is your name? 
Tony

Your final bill is below:
9 bags of chips @ $3.49 each: $31.410000000000004
8.0 pounds of spinach @ $2.99 each: $23.92
6.0 dozen eggs @ $1.89 each: $11.34 

Your total is $66.67. Have a great day, Tony! 

********************************************************************/