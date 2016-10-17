/*  AirQuality.java
Davon Grant
dgran101
Section 4 */

import java.util.Scanner; //Import scanner class

public class AirQuality{
  public static void main(String[]args){
    //declare needed variables as well as obtain users 1st input
    Scanner scan = new Scanner(System.in);
    boolean reportingMethod = true; //instantialize the boolean variable (initial value does not matter)
    System.out.println("Select reporting method:\n1)Level of Health Concern\n2)Color");
    int input = scan.nextInt();
    
    //Determine the reporting method based on the users input
    if(input == 1){
      reportingMethod = true;
    }
    else if (input ==2){
      reportingMethod = false;
    }
    
    //Ask the user for the AQI
    System.out.println("Enter AQI:");
    int aqiValue = scan.nextInt();
    
    //Based on the chosen reporting method, output the level of health concern
    if(reportingMethod == true){
      if ((aqiValue>0)&&(aqiValue<=50)){
        System.out.println("Good");
      }
      else if ((aqiValue>50)&&(aqiValue<=100)){
        System.out.println("Moderate");
      }
      else if ((aqiValue>100)&&(aqiValue<=150)){
        System.out.println("Unhealthy for Sensitive Groups");
      }
      else if ((aqiValue>150)&&(aqiValue<=200)){
        System.out.println("Unhealthy");
      }
      else if ((aqiValue>200)&&(aqiValue<=300)){
        System.out.println("Very Unhealthy");
      }
      else if ((aqiValue>300)&&(aqiValue<=500)){
        System.out.println("Hazardous");
      }
    }
    //Based on the chosen reporting method, output the color
    if(reportingMethod == false){
      if ((aqiValue>0)&&(aqiValue<=50)){
        System.out.println("Green");
      }
      else if ((aqiValue>50)&&(aqiValue<=100)){
        System.out.println("Yellow");
      }
      else if ((aqiValue>100)&&(aqiValue<=150)){
        System.out.println("Orange");
      }
      else if ((aqiValue>150)&&(aqiValue<=200)){
        System.out.println("Red");
      }
      else if ((aqiValue>200)&&(aqiValue<=300)){
        System.out.println("Purple");
      }
      else if ((aqiValue>300)&&(aqiValue<=500)){
        System.out.println("Maroon");
      }
      
  }
}//end main method
}//end class

/*****************************
  * Sample Output 1:
  * 
  * Select reporting method:
  * 1)Level of Health Concern
  * 2)Color 
  * 1
  * Enter AQI: 
  * 20
  * Good 
  * 
  * Sample Output 2:
  * 
  * Select reporting method:
  * 1)Level of Health Concern
  * 2)Color 
  * 2
  * Enter AQI: 
  * 305
  * Maroon 
  * 
  * Sample Output 3:
  * Select reporting method:
  * 1)Level of Health Concern
  * 2)Color 
  * 1
  * Enter AQI: 
  * 124
  * Unhealthy for Sensitive Groups 
  * ************************/
