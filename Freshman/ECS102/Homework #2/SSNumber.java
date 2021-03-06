/* SSNumber.java
 Davon Grant
 N/A
 dgran101 */

//import needed classes
import javax.swing.JOptionPane;
import java.util.Scanner;

public class SSNumber{
  public static void main(String[]args){
    
    //declare needed variables
    Scanner input = new Scanner(System.in);
    String left, middle, right;
    int leftSSN, middleSSN, rightSSN;
    
    //Ask for information and parse them to integers
    left = JOptionPane.showInputDialog("What are the first three numbers of your social security number?");
    leftSSN = Integer.parseInt(left);
    middle = JOptionPane.showInputDialog("What are the two numbers after the first three numbers in your social security number?");
    middleSSN = Integer.parseInt(middle);
    right = JOptionPane.showInputDialog("What are the final four numbers in your social security number?");
    rightSSN = Integer.parseInt(right);
    
    //Display the information as a SSN and the warning message
    JOptionPane.showMessageDialog(null, "Your social security number is " + leftSSN + "-" + middleSSN + "-" + rightSSN + ".");
    JOptionPane.showMessageDialog(null, "Be careful! ''Don't give your S.S. number over the phone!''");
  }
}

/******************************
Output(all through JOptionPane):
What are the first three numbers of your social security number?
111
What are the two numbers after the first three numbers in your social security number?
99
What are the final four numbers in your social security number?
8467
Your social security number is 111-99-8467.
Be careful! "Don't give your S.S. number over the phone!"
******************************/