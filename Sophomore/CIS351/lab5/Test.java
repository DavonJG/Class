import java.io.*;
import java.util.*;
import java.lang.*;

public class Test {

  //////////////////////////////////////////////////////////////////////
  // The main method 
  public static void main(String argv[]) {
    for (int i = 100; i < 1000; i=i+100) // You'll want to play with these numbers
      experiment(i);
      scales(100,100);
  }

  //////////////////////////////////////////////////////////////////////
  // experiment(int arraySize)
  //   Carry out the run-time tests on the sorts on a random array
  //   of size arraySize

  public static void experiment(int arraySize) {
    int a[], b[];
    long steps;
 
    // A example use of the Math.log method.
    // System.out.println("The natural log of 10 is " + Math.log(10));
  
    // create two int arrays of arraySize many elements
    a = new int[arraySize];
    b = new int[arraySize];
    FillRandom(a);
    
 
    System.out.println("The array size is " + arraySize);
 
    System.arraycopy(a,0,b,0,arraySize);  // copy a to b
    steps= Sorts.sort1(b);
    scales(steps,arraySize); //added use of scales method
    System.out.printf("Number of steps for Sort 1: %12d %n",steps); 
 
    System.arraycopy(a,0,b,0,arraySize);  // recopy a to b
    steps = Sorts.sort2(b);
    scales(steps,arraySize); //added use of scales method
    System.out.printf("Number of steps for Sort 2: %12d %n",steps); 
    
    System.arraycopy(a,0,b,0,arraySize);  // recopy a to b
    steps = Sorts.sort3(b);
    scales(steps,arraySize); //added use of scales method
    System.out.printf("Number of steps for Sort 3: %12d %n",steps); 
 
    System.arraycopy(a,0,b,0,arraySize);  // recopy a to b
    steps = Sorts.sort4(b);
    scales(steps,arraySize); //added use of scales method
    System.out.printf("Number of steps for Sort 4: %12d %n",steps); 
  }

  //////////////////////////////////////////////////////////////////////
  // FillRandom(int a[])
  //   Fill an int array with random ints

  public static void FillRandom(int a[]) {
    Random r = new Random();
    for (int i = 0; i<a.length; i++) a[i] = r.nextInt();
  }
  
  //////////////////////////////////////////////////////////////////////
  // scales(int t,int n)
  //   Print some ratios of interest
  public static void scales(long t,int n) {
    double a = t/(n*Math.log(n));
    double b = t/((double) n*n);
    double c = t/((double) n*n*n);
    System.out.printf("(i) %8f   (ii) %8f   (iii) %8f %n",a,b,c);
  }
}
// Θ(n^2) = sort1
// Θ(nlogn) = sort2
// Θ(n^3) = sort3
// Θ(nlogn) = sort4

/*Explanation:
 * After adding the scales method with steps and arraysize as parameters, I was able to see that
 * n^2 converged at approximately 0.25, while nlogn went toward infinity and n^3 got closer to 0, meaning that
 * sort1 was n^2. I used a similar process for sort2 (nlogn converged around 1.7, while n^3 approached 0 and n^2
 * kept decreasing to -Infinity), sort3 (n^3 converged at 0.5, while n^2 and nlogn approached infinity), and sort4
 * (nlogn converged at 1.5 while n^3 and n^2 approached 0.). For all of these tests, I had to increase i to larger values
 * to ensure consistent and accurate testing.
*/