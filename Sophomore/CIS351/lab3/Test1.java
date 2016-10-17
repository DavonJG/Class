// A sample use of the Box1 class.
public class Test1 {
  public static void main(String argv[]) {
    Box1 x = new Box1();
    System.out.println("----------------------------------------------"); //formatting
    System.out.println("When Box1 x and Box1 y are first created, both a and b for both objects are the default value of 0, as shown below: ");
    System.out.println("x.getA():" + x.getA());
    System.out.println("x.getB(): " + x.getB());
    Box1 y = new Box1();
    System.out.println("y.getA(): " + y.getA());
    System.out.println("y.getB(): " + y.getB());
    System.out.println("------------------------------\nHowever, when both A and B are changed for Box1 x via x.setA(25) and x.setB(25), the only variable that " +
                       "changes for Box1 y is b.");
    x.setA(25);
    x.setB(25);
    System.out.println("x.getA() after x.setA(25): " + x.getA());
    System.out.println("x.getB() after x.setA(25): " + x.getB());
    System.out.println("y.getA() after x.setA(25): " + y.getA());
    System.out.println("y.getB() after x.setA(25): " + y.getB());
    System.out.println("SOLUTION: a is the instance variable, because changing a for Box1 x does not change a for Box1 y. This means that both objects have "+
                       "their own instance of variable a. b is the static variable, because when B is changed for Box1 x via x.setB(), it also changes the "+
                       "result of y.getB(), proving they point to the same variable.");
  }
}
