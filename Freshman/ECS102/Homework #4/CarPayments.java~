/*  CarPayments.java
Davon Grant
dgran101
Section 4 */


import java.util.Scanner;

public class CarPayments{
  public static void main(String[]args){
    Scanner scan = new Scanner(System.in); //Declare needed scanner
    
    //Obtain all user inputs and store them.
    System.out.println("How much is the loan?");
    double loanAmount = scan.nextDouble();
    System.out.println("How many payments?");
    int numPayments = scan.nextInt();
    System.out.println("What is the annual interest rate?");
    double interestRate = scan.nextDouble();
    
    //Create more variables and output the beginning of the graph.
    double monthlyInterest = interestRate/12;
    double monthlyPayment = ((monthlyInterest)*(loanAmount))/(1-Math.pow((1+monthlyInterest),-numPayments));
    monthlyPayment = (double)Math.round((monthlyPayment*100))/100.0; //get the payment rounded to the nearest cent.
    System.out.println("Monthly payment: " + monthlyPayment);
    System.out.println("Payment\tInterest\tPrincipal\tRemaining\nNumber\tPayment\tPayment\tBalance");
    double interestPayment = monthlyInterest*loanAmount;
    double remainingBalance = loanAmount; //initialize remainingBalance
    double principalPayment = 0; //initialize principalPayment
    
    //for loop which displays the payments
    for(int counter=1;counter<=numPayments;counter++){
      principalPayment = (double)Math.round((monthlyPayment-interestPayment)*100)/100;
      remainingBalance -= principalPayment;
      System.out.println(counter + "\t" + interestPayment + "\t" + principalPayment + "\t" + Math.round((remainingBalance*100))/100.0);
      interestPayment = (double)Math.round((monthlyInterest * remainingBalance)*100)/100;
      //When the final payment is reached, set remainingBalance to the monthly payment which would result in a final balance of 0 after.
      if(remainingBalance < monthlyPayment){
        remainingBalance = principalPayment + interestPayment;
      }
    }
  }
}

/*Sample Output:

How much is the loan? 
1000
How many payments? 
6
What is the annual interest rate? 
.09
Monthly payment: 171.07 
Payment Interest Principal Remaining
Number Payment Payment Balance 
1 7.5 163.57 836.43 
2 6.27 164.8 671.63 
3 5.04 166.03 505.6 
4 3.79 167.28 338.32 
5 2.54 168.53 169.79 
6 1.27 169.8 0.0 
*/

//table looks better when it actually runs...