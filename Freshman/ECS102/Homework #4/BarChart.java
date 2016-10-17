/*BarChart.java
 * Davon Grant
 * dgran101
 * Section 4 */

import java.util.Scanner;

public class BarChart{
  public static void main(String[]args){
    //declare needed variables and objects
    Scanner scan = new Scanner(System.in);
    String store1Stars, store2Stars, store3Stars, store4Stars, store5Stars;
    int counter;
    
    //Get the user's inputs
    System.out.print("Enter today's sales for store 1:");
    int store1Sales = scan.nextInt();
    System.out.print("Enter today's sales for store 2:");
    int store2Sales = scan.nextInt();
    System.out.print("Enter today's sales for store 3:");
    int store3Sales = scan.nextInt();
    System.out.print("Enter today's sales for store 4:");
    int store4Sales = scan.nextInt();
    System.out.print("Enter today's sales for store 5:");
    int store5Sales = scan.nextInt();
    
    //Set the store sales variables to the given integer divided by 100
    store1Sales=(store1Sales/100);
    store2Sales=(store2Sales/100);
    store3Sales=(store3Sales/100);
    store4Sales=(store4Sales/100);
    store5Sales=(store5Sales/100);
    
    if((store1Sales>0) && (store2Sales>0) && (store3Sales>0) && (store4Sales>0) && (store5Sales>0)){ //input validation
    //Print out the appropriate amount of stars using for loops.
      System.out.println("SALES BAR CHART");
      System.out.print("Store 1: ");
      for(counter=0; counter<store1Sales; counter++){
        System.out.print("*");
      }
      System.out.print("\nStore 2: ");
      for(counter=0; counter<store2Sales; counter++){
        System.out.print("*");
      }
      System.out.print("\nStore 3: ");
      for(counter=0; counter<store3Sales; counter++){
        System.out.print("*");
      }
      System.out.print("\nStore 4: ");
      for(counter=0; counter<store4Sales; counter++){
        System.out.print("*");
      }
      System.out.print("\nStore 5: ");
      for(counter=0; counter<store5Sales; counter++){
        System.out.print("*");
      }
    }
    else{ //if a negative number is given, output an error message.
      System.out.println("Negative numbers will not be accepted. Restart the program and try again.");
    }
  }
}

/*Sample Output 1:
Enter today's sales for store 1:100
Enter today's sales for store 2:2000
Enter today's sales for store 3:300
Enter today's sales for store 4:600
Enter today's sales for store 5:200
SALES BAR CHART 
Store 1: *
Store 2: ********************
Store 3: ***
Store 4: ******
Store 5: **

Sample Output 2:
Enter today's sales for store 1:400
Enter today's sales for store 2:-300
Enter today's sales for store 3:100
Enter today's sales for store 4:-100
Enter today's sales for store 5:2200
Negative numbers will not be accepted. Restart the program and try again. 
*/

