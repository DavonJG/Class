import java.util.Scanner;

/*TempTable.java
 * Davon Grant
 * dgran101
 * Section 4
 * 
 * Displays functionality of Temperature.java by displaying Temperature objects in rows.
 * */

public class TempTable{
  public static void main(String[]args){
    double fahrenheitTemp;
    double kelvinTemp;
    double celsiusTemp;
    Scanner scan = new Scanner(System.in);
    System.out.println("Hello. Please choose a scale. (Fahrenheit, Celsius, or Kelvin)");
    String selection = scan.nextLine();
    
    //Creates Temperature objects in a loop before displaying them in a table.
    if(selection.equalsIgnoreCase("Fahrenheit")){
      System.out.println("Fahrenheit       Celsius       Kelvin");
      for(double i=0; i<101.0; i+=5.0){
        Temperature temp = new Temperature(i, 'F'); //create a temperature object using the counter as the temperature.
        fahrenheitTemp = temp.getFahrenheit();
        kelvinTemp = temp.getKelvin();
        celsiusTemp = temp.getCelsius();
        System.out.printf("%.3f        %.3f       %.3f", fahrenheitTemp,celsiusTemp,kelvinTemp);
        System.out.println();
      }
    }
    
    //same loop, but use 'C' as the char in the constructor and switch the order of values in the table.
    else if(selection.equalsIgnoreCase("Celsius")){
      System.out.println("Celsius       Fahrenheit       Kelvin");
      for(double i=0; i<101.0; i+=5.0){
        Temperature temp = new Temperature(i, 'C'); //create a temperature object using the counter as the temperature.
        fahrenheitTemp = temp.getFahrenheit();
        kelvinTemp = temp.getKelvin();
        celsiusTemp = temp.getCelsius();
        System.out.printf("%.3f        %.3f       %.3f", celsiusTemp,fahrenheitTemp,kelvinTemp);
        System.out.println();
      }
    }
    //same loop, but use 'K' as the char in the constructor and switch the order of values in the table.
    else if(selection.equalsIgnoreCase("Kelvin")){
      System.out.println("Kelvin       Fahrenheit       Celsius");
      for(double i=0; i<101.0; i+=5.0){
        Temperature temp = new Temperature(i, 'K'); //create a temperature object using the counter as the temperature.
        fahrenheitTemp = temp.getFahrenheit();
        kelvinTemp = temp.getKelvin();
        celsiusTemp = temp.getCelsius();
        System.out.printf("%.3f        %.3f       %.3f", kelvinTemp,fahrenheitTemp,celsiusTemp);
        System.out.println();
      }
    }
  }
}
            