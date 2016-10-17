/*  QuizGame.java
Davon Grant
dgran101
Section 4*/

import javax.swing.JOptionPane;
import java.io.*;
import java.util.Scanner;
import java.util.Random;

public class QuizGame{
  public static void main(String[]args) throws IOException{
    
    //Declare the needed variables and objects
    Random generator = new Random();
    File quizQuestions = new File("QuizQuestions.txt");
    Scanner questionScan = new Scanner(quizQuestions);
    File quizAnswers = new File("QuizAnswers.txt");
    Scanner answerScan = new Scanner(quizAnswers);
    String questionString = JOptionPane.showInputDialog("Welcome,\nHow many questions do you want? (1-10)");
    int numQuestions = Integer.parseInt(questionString);
    
    //Stay in this loop if the entered number is not between 1 and 10
    do{
      JOptionPane.showMessageDialog(null, "Thank you for your input");
    }
    while((numQuestions>10)&&(numQuestions<0));
    
    //declare the answers counters
    int correctAnswers = 0;
    int incorrectAnswers = 0;
    
    //Loops for asking questions and recording if the answers are correct.
    for(int counter = 0;counter<numQuestions;counter++){
      //declare all the variables that will be used in the loop and record the users input to the current question
      String correctMessage = "";
      String incorrectMessage = "";
      String currentQuestion = questionScan.nextLine();
      String currentAnswer = answerScan.nextLine();
      String temp = JOptionPane.showInputDialog(currentQuestion);
      
      //setup the random responses to correct answers
      if(temp.equalsIgnoreCase(currentAnswer)){
        int messageTemp = generator.nextInt(3);
        if(messageTemp == 0){
          correctMessage = "Great!";
        }
        else if(messageTemp == 1){
          correctMessage = "Excellent!";
        }
        else if(messageTemp == 2){
          correctMessage = "Wow!";
        }
        JOptionPane.showMessageDialog(null, correctMessage);
        correctAnswers++; //add 1 to the correct answers coutner
      }
      
      //setup the random responses to incorrect answers
      else{
        int messageTemp = generator.nextInt(2);
        if(messageTemp == 0){
          incorrectMessage = "Sorry, incorrect.";
        }
        else if(messageTemp == 1){
          incorrectMessage = "Wrong.";
        }
        JOptionPane.showMessageDialog(null, incorrectMessage);
        incorrectAnswers++; //add 1 to the incorrect answers counter
      }
    }
    //Output the final results.
    JOptionPane.showMessageDialog(null, "You got " + correctAnswers + " questions correct and "+ incorrectAnswers + " incorrect.");
  }
}