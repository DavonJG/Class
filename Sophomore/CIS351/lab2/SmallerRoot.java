import java.util.Scanner;
import java.lang.Math;

public class SmallerRoot {
  /** Computes the smaller root of ax^2 + bx + c **/
  public static double smaller(double a, double b, double c) 
    throws Exception
  {
    if(a==0.0){
      throw new Exception("a is zero");
    }
    double root = (-b - Math.sqrt(b*b-4*a*c))/(2*a);
    if(root<0){
      throw new Exception("Discriminate is negative.");
    }
    return root;
  }
  
  /** Prompts the user for three numbers, a, b, and c, and then 
    * prints the smaller root of the quadratic equation x^2 + bx + c 
    * (provided things go well).
    */
  public static void main(String argv[]) throws Exception
  {
    try{
      Scanner stdin = new Scanner(System.in);
      System.out.print("Enter three numbers: ");
      double a = stdin.nextDouble();
      double b = stdin.nextDouble();
      double c = stdin.nextDouble();
      
      double root = smaller(a,b,c);
      System.out.println("The smaller root of " + a + "x^2 + " + b 
                           + "x + " + c + " is " + root);
    }
    catch (Exception e){
      System.out.println("Sorry, no such root.");
    }
  }
}



