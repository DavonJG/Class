import java.util.Scanner;

/*Store.java
 * Davon Grant
 * dgran101
 * Section 4
 * 
 * Creates a store using RetailItem objects
 * */

public class Store{
  public static void main(String[]args){
    int selection;
    boolean askMore = true; //boolean used for continuing the program.
    Scanner scan = new Scanner(System.in);
    RetailItem jacket = new RetailItem("Jacket",59.95,12);
    RetailItem designerJeans = new RetailItem("Designer Jeans",34.95,40);
    RetailItem shirt = new RetailItem("Shirt",24.95,20);
    while(askMore==true){ 
      do{
        System.out.println("Welcome to the store! We are selling the following:\n1)"+jacket.getDescription()+"\n2)"+designerJeans.getDescription()+"\n3)"+shirt.getDescription()+"\n4)Quit\nWhat would you like?");
        selection = scan.nextInt();
      }while((selection<1)||(selection>4));
      if(selection==1){
        buyItem(jacket);
        askMore = true;
      }
      else if(selection==2){
        buyItem(designerJeans);
        askMore = true;
      }
      else if(selection==3){
        buyItem(shirt);
        askMore = true;
      }
      else if(selection==4){
        System.out.println("Have a nice day! Here is our remaining inventory:\n");
        askMore = false;
      }
    }
    System.out.println("\tDescription\tUnits On Hand\tPrice");
    System.out.println("----------------------------------------------------------------");
    System.out.println("Item #1\t"+jacket.getDescription()+"\t\t"+jacket.getUnitsOnHand()+"\t\t"+jacket.getPrice());
    System.out.println("Item #2\t"+designerJeans.getDescription()+"\t"+designerJeans.getUnitsOnHand()+"\t\t"+designerJeans.getPrice());
    System.out.println("Item #3\t"+shirt.getDescription()+"\t\t"+shirt.getUnitsOnHand()+"\t\t"+shirt.getPrice());
  }
  
  //buyItem()
  //Tells the user what they have purchased as well as decreasing the units remaining.
  public static void buyItem(RetailItem ri){
    System.out.println("You have purchased: "+ri.getDescription()+" for $"+ri.getPrice()+".");
    if(ri.getUnitsOnHand()==0){
      System.out.println("Sorry, there are no more units.");
    }
    else{
      ri.setUnitsOnHand(ri.getUnitsOnHand()-1);
    }
  }
}