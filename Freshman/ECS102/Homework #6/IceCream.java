/* IceCream.java
Davon Grant
dgran101
Section 4
*/

import java.util.Scanner;

public class IceCream{
  public static void main(String[]args){
    Scanner scan = new Scanner(System.in);
    boolean x;
    System.out.println("Welcome to the ice cream shop.");
    int selection;
    
    //ask for the flavor until the user gives a valid answer.
    do{
    flavorChoices();
    selection = askUser();
    }while((selection<1)||(selection>4));
    
    //ask for the size until the user gives a valid answer.
    do{
    sizeChoices();
    selection = askUser();
    }while((selection<1)||(selection>3));
    x=moreCones();
    
    //If the user says that they want more cones, repeat the process.
    while(x==true){
      do{
        flavorChoices();
        selection = askUser();
      }while((selection<1)||(selection>4));
      do{
        sizeChoices();
        selection = askUser();
      }while((selection<1)||(selection>3));
      x=moreCones();
    }
    thankYou(); //Thank the user
  }
  
  //flavorChoices()
  //Displays the list of ice cream flavors for the user to choose.
  public static void flavorChoices(){
    System.out.println("Choose a flavor.\n1)Vanilla\n2)Chocolate\n3)Strawberry\n4)Fudge Ripple");
  }
  
  //sizeChoices()
  //Displays the list of sizes for the user to choose
  public static void sizeChoices(){
    System.out.println("Choose a size.\n1)Small\n2)Medium\n3)Large");
  }
  
  //askUser()
  //Method used for asking the user for an input and returns
  public static int askUser(){
    Scanner scan = new Scanner(System.in);
    System.out.println("What is your selection?");
    int selection = scan.nextInt();
    return selection;
  }
  
  //moreCones()
  //Ask if the user wants anything else and returns true and false.
  public static boolean moreCones(){
    String input;
    Scanner scan = new Scanner(System.in);
    System.out.println("Here is your cone, would you like anything else?");
    input = scan.nextLine();
    if(input.equalsIgnoreCase("yes")){
      return true;
    }
    else{
       return false;
    }
  }
  
  //thankYou()
  //Thanks the user for coming.
  public static void thankYou(){
    System.out.println("Thank you for coming!");
  }
}
/*Outputs:
Welcome to the ice cream shop. 
Choose a flavor.
1)Vanilla
2)Chocolate
3)Strawberry
4)Fudge Ripple 
What is your selection? 
1
Choose a size.
1)Small
2)Medium
3)Large 
What is your selection? 
4
Choose a size.
1)Small
2)Medium
3)Large 
What is your selection? 
2
Here is your cone, would you like anything else? 
No
Thank you for coming! 
________________________________________________________________________________________________

Welcome to the ice cream shop. 
Choose a flavor.
1)Vanilla
2)Chocolate
3)Strawberry
4)Fudge Ripple 
What is your selection? 
7
Choose a flavor.
1)Vanilla
2)Chocolate
3)Strawberry
4)Fudge Ripple 
What is your selection? 
3
Choose a size.
1)Small
2)Medium
3)Large 
What is your selection? 
4
Choose a size.
1)Small
2)Medium
3)Large 
What is your selection? 
3
Here is your cone, would you like anything else? 
Yes
Choose a flavor.
1)Vanilla
2)Chocolate
3)Strawberry
4)Fudge Ripple 
What is your selection? 
6
Choose a flavor.
1)Vanilla
2)Chocolate
3)Strawberry
4)Fudge Ripple 
What is your selection? 
2
Choose a size.
1)Small
2)Medium
3)Large 
What is your selection? 
1
Here is your cone, would you like anything else? 
No
Thank you for coming! 
*/