import java.io.*;

public class Bugs3 {
public static void main(String argv []) {
  int i = 7;
  int j = 4;
  int k = 0; //added an initialization of k 
  k = (int) ( (i-j) * (j-i) * Math.exp(j/i)) ; //added missing )
  countDown(k);
  System.out.println(k);
}

public static void countDown(int n) {
  // Run a countdown until n reaches 0 ***or below*** (Hint!).
  if (n <= 0) //changed to less than or equal to 0
    System.out.println("Lift off!");
  else
    countDown(n-1);
}
}
