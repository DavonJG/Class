import java.io.*;
import java.util.Scanner;


/*WinningFinder.java
 Davon Grant
 dgran101
 Section 4
 */

public class WinningFinder{
  public static void main(String[]args) throws IOException{
    Scanner scan = new Scanner(System.in);
    WinningTeam[] teams = new WinningTeam[104];
    File dataFile = new File("WorldSeriesWinners.txt");
    Scanner dataScan = new Scanner(dataFile);
    int i=0;
    for(int x=1903; x<2009; x++){ //Store the WinningTeam objects into the array.
      if((x==1904)||(x==1994)){
        x++;
      }
      teams[i]= new WinningTeam(dataScan.nextLine(), x);
      i++;
    }
    //Display what the user asks.
    System.out.println("What winning team would you like to display?");
    String selection = scan.nextLine();
    int winCount=0;
    String yearsWon="";
    for(int z=0;z<teams.length;z++){
      if(selection.equalsIgnoreCase(teams[z].getName())){
        winCount++;
        yearsWon+=(teams[z].getYear()+" ");
      }
    }
    System.out.println("The "+selection+" won "+winCount+" times! The years when they've won is below!");
    System.out.println(yearsWon);
    }
  }