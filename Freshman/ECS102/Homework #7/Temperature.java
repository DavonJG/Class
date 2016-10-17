/*Temperature.java
 * Davon Grant
 * dgran101
 * Section 4
 * 
 * To be used with TempTable.java.
 * */


public class Temperature{
  private double ftemp;
  private double ctemp;
  private double ktemp;
  public Temperature(double f){ //first constructor that sets the temperature to the given value
    ftemp = f;
  }
  public Temperature(double temp, char type){ //additional constructor that allows the user to choose what type of temperature to enter.
    if(type=='C'){
      ftemp = ((9.0*temp)/5.0) + 32.0;
    }
    else if(type=='K'){
      ftemp = ((9.0*(temp-273.0))/5.0)+32.0;
    }
    else if(type=='F'){
      ftemp = temp;
    }
  }
  //get and set method for fahrenheit temperature
  public void setFahrenheit(double f){
    ftemp = f;
  }
  public double getFahrenheit(){
    return ftemp;
  }
  //get method for celsius temperature
  public double getCelsius(){
    ctemp = (5.0/9.0)*(ftemp-32.0);
    return ctemp;
  }
  
  //get method for kelvin temperature.
  public double getKelvin(){
    ktemp = ((5.0/9.0)*(ftemp-32.0)) + 273.0;
    return ktemp;
  }
}