/* Seconds.java
 Davon Grant
 Section 4
 netID: dgran101 */

//import Scanner class
import java.util.Scanner;

public class Seconds{
  public static void main(String[]args){
    //Declare needed variables
    Scanner input = new Scanner(System.in);
    int hours, minutes, seconds, temp, temp2;
    final int SECONDS_IN_HOUR = 3600;
    final int SECONDS_IN_MINUTE = 60;
    
    //Ask the user for an input and record it
    System.out.println("How many seconds would you like to convert?");
    seconds = input.nextInt();
    
    //Do the math needed to convert from seconds to hours, seconds, and minutes
    hours = seconds/SECONDS_IN_HOUR;
    temp = seconds%SECONDS_IN_HOUR; 
    temp2 = temp%60; 
    minutes = temp/60;
    seconds = temp2;
    
    //Display the result of the conversion
    System.out.println(hours + " hours, " + minutes + " minutes, " + seconds + " seconds.");
  }
}

/************************************************************************************
Sample Output 1:
How many seconds would you like to convert? 
100000
27 hours, 46 minutes, 40 seconds. 


Sample Output 2:
How many seconds would you like to convert? 
194722
54 hours, 5 minutes, 22 seconds. 

Sample Output 3:
How many seconds would you like to convert? 
92847274
25790 hours, 54 minutes, 34 seconds. 
**************************************************************************************/