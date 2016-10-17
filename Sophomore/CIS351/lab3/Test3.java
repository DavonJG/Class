// A sample use of the Box2 class.
public class Test3 {
  public static void main(String argv[]) {
    Box3 x = new Box3();
    Box3 y = new Box3();
    Box3 z = new Box3();
    x.set(34);  y.set(8); z.set(75);
    System.out.println("x: " + x.get());
    System.out.println("y: " + y.get());
    System.out.println("z: " + z.get());
    System.out.println("A displayed above, the timestamp is only displayed once even though there are 3 Box3's created.");
  }
}
