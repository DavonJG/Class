import java.io.*;

public class Poke {
  public static void main(String argv[]) {
    Puzzle0 p0 = new Puzzle0();
    Puzzle1 p1 = new Puzzle1();
    Puzzle2 p2 = new Puzzle2();
    Puzzle3 p3 = new Puzzle3();
    
    // Do your tests on p1.a, p1.b, p2.a, p2.b, p3.a, and p3.b below.
       
    // Example: Figuring out Puzzle0.
    System.out.println("\n**PUZZLE 0 Experments**");
    System.out.println("p0.a is " + p0.a); // prints: -T-O-
    System.out.println("p0.b is " + p0.b); // prints: -Y-O-
    // The O might be in a shared Node
    p0.a.changeAll('O','X');
    System.out.println("p0.a is " + p0.a); // prints: -T-X-
    System.out.println("p0.b is " + p0.b); // prints: -Y-X- 
    // Since p0.b's last Node's letter changed from an O to an X,
    // that Node must be shared between p0.a and p0.b.
    // So we have the digram given in Part I of the Lab writeup
   
  
    System.out.println("\n**PUZZLE 1 Experments**");
    System.out.println("p1.a is "+ p1.a);
    System.out.println("p1.b is "+ p1.b);

    System.out.println("\nChange all the e's in p1.b to w's");
    p1.b.changeAll('e','w');
    System.out.println("p1.a is "+ p1.a);
    System.out.println("p1.b is "+p1.b);
    
    System.out.println("\nChange all the a's in p1.b to o's");
    p1.b.changeAll('a','o');
    System.out.println("p1.a is "+ p1.a);
    System.out.println("p1.b is "+p1.b);
    
    System.out.println("\nChange all the s's in p1.b to r's");
    p1.b.changeAll('s','r');
    System.out.println("p1.a is "+ p1.a);
    System.out.println("p1.b is "+p1.b);
    
    System.out.println("\nChange all the y's in p1.b to s's");
    p1.b.changeAll('y','s');
    System.out.println("p1.a is "+ p1.a);
    System.out.println("p1.b is "+p1.b);
    
    System.out.println("As displayed above, all of the nodes are shared. There are 4 total nodes.");
    // Now write down a box and arrow diagram for p1.a and p1.b.
    // Explain why your diagram *must* be correct.

    System.out.println("\n**PUZZLE 2 Experments**");
    System.out.println("p2.a is "+ p2.a);
    System.out.println("p2.b is "+ p2.b);
    
    if (p2.a.front==null)
      System.out.println("Hey, p2.a is empty");
    else
      System.out.println("The first letter in p2.a is: "
    + p2.a.front.letter);
    
    p2.a.changeAll('o','p'); //this changes the second o node in p2.b as well, showing that that is the shared node.
    System.out.println("p2.a is "+ p2.a);
    System.out.println("p2.b is "+p2.b);
    System.out.println("p2.a.changeAll('o','p') changes the second o node in p2.b as well, showing that that is the shared node. changeAll works seperately using all other letters. There are 7 nodes.");
    // Etc.
    System.out.println("\n**PUZZLE 3 Experments**");
    System.out.println("p3.a is "+ p3.a);
    LetList p3c = new LetList();
    p3c = p3.b.rest();
    System.out.println("p3c is "+ p3c);
    //System.out.println("p3.b is "+ p3.b); //This causes bad things to happen.

  }
}
