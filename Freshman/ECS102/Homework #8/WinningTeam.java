/*WinningTeam.java
 Davon Grant
 dgran101
 Section 4
 */

public class WinningTeam{
  private String name;
  private int yearWon;
  //constructor
  public WinningTeam(String n, int year){
    yearWon=year;
    name=n;
  }
  
  //get methods used in WinningFinder
  public String getName(){
    return name;
  }
  public int getYear(){
    return yearWon;
  }
}