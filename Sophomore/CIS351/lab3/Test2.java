// A sample use of the Box2 class.
public class Test2 {
  public static void main(String argv[]) {
    Box2 x = new Box2(5,10);
    Box2 y = new Box2(1, 2);
    System.out.println("x: " + x.pair[0] + "  " + x.pair[1]); //should print 5,10
    System.out.println("y: " + y.pair[0] + "  " + y.pair[1]); //should print 1,2
    y = Box2.copy1(x);
    System.out.println("x: " + x.pair[0] + "  " + x.pair[1]); //should still print 5,10
    System.out.println("y: " + x.pair[0] + "  " + x.pair[1]); //should still print 5,10
    Box2 z = Box2.copy2(x);
    System.out.println("x: " + x.pair[0] + "  " + x.pair[1]); //5,10
    System.out.println("y: " + y.pair[0] + "  " + y.pair[1]); //5,10
    System.out.println("z: " + z.pair[0] + "  " + z.pair[1]); //5,10
    
    System.out.println("One of the copys  is copying the original array while the other copy changes the aspects to that of the new objects.");
  }
}
