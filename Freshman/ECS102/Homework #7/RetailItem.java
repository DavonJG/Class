/*RetailItem.java
 * Davon Grant
 * dgran101
 * Section 4
 * 
 * To be used with Store.java.
 * */

public class RetailItem{
  private String description;
  private double price;
  private int unitsOnHand;
  public RetailItem(String s, double pr, int units){ //overloaded constructor
    description = s;
    price = pr;
    unitsOnHand = units;
  }
  
  //get and set methods for the instance data
  public void setDescription(String desc){
    description = desc;
  }
  public String getDescription(){
    return description;
  }
  public void setPrice(double p){
    price = p;
  }
  public double getPrice(){
    return price;
  }
  public void setUnitsOnHand(int units){
    unitsOnHand = units;
  }
  public int getUnitsOnHand(){
    return unitsOnHand;
  }
}