import java.util.Scanner;
import java.util.Random;

public class TwentyOne{
  //Instance data
  Random gen = new Random();
  Die firstDie = new Die(6);
  Die secondDie = new Die(6);
  Scanner scan = new Scanner(System.in);
  int humanScore = 0;
  int computerScore = 0;
  int computerFlip = 0;
  
  
  //play method which plays rounds until the computer or user reaches 5 coins.
  //tested using an external class.
  //External class:
  /*
 
 public class Test{
  public static void main(String[]args){
    TwentyOne twentyone = new TwentyOne();
    twentyone.play();
  }
}

*/
  public void play(){
    int humanCoins = 0;
    int computerCoins = 0;
    int humanRoundTotal, computerRoundTotal;
    while(humanCoins<5&&computerCoins<5){
      computerRoundTotal= computerTurn();
      humanRoundTotal = humanTurn();
      if(humanRoundTotal<21&&computerRoundTotal<21){
        if(humanRoundTotal%21<computerRoundTotal%21){
          humanCoins++;
        }
        else if(humanRoundTotal%21>computerRoundTotal%21){
          computerCoins++;
        }
      }
      else if(humanRoundTotal>21&&computerRoundTotal<21){
        computerCoins++;
      }
      else if(humanRoundTotal<21&&computerRoundTotal>21){
        humanCoins++;
      }
    }
    if(humanCoins==5){
      System.out.println("Human wins!");
    }
    else if(computerCoins==5){
      System.out.print("Computer wins!");
    }
  }
  
  //humanTurn() method that repeats until the user declines.
  public int humanTurn(){
    boolean redo = true;
    do{
      firstDie.roll();
      int temp1 = firstDie.getValue();
      secondDie.roll();
      int temp2 = secondDie.getValue();
      humanScore+=(temp1+temp2);
      System.out.println("You have rolled a "+temp1+" and a "+temp2+"! Your current total is "+humanScore);
      System.out.println("Would you like to roll again? (Y/N)");
      String selection = scan.nextLine();
      if(selection.equalsIgnoreCase("y")){
        redo=true;
      }
      else if(selection.equalsIgnoreCase("n")){
        redo=false;
        System.out.println("Human turn has ended.");
      }
    }while(redo==true);
    return humanScore;
  }
  
  //computerTurn method, repeats using a random integer. If the integer is 1, it continues. If it is 0, it stops.
  public int computerTurn(){
    do{
      firstDie.roll();
      int temp1 = firstDie.getValue();
      secondDie.roll();
      int temp2 = secondDie.getValue();
      computerScore+=(temp1+temp2);
      computerFlip = gen.nextInt(1);
      if(computerFlip==0){
        return computerScore;
      }
      else{
        computerFlip=1;
        System.out.println("CPU is rolling again.");
      }
    }while(computerFlip==1);
    System.out.println("CPU's turn is complete.");
    return computerScore;
  }
}