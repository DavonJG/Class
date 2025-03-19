public class BSNode<T extends Comparable> {
  // instance variables
  T         data;
  BSNode<T> left, right;
  // Constructors
  protected BSNode(BSNode<T> lft, T dat, BSNode<T> rght) {
    data = dat;  left = lft;  right = rght;   
  }
  protected BSNode(T dat) { this(null,dat,null); }

  // DISPLAY UTILITIES
  private static void spaces(int s) {
    for (int i=0; i<s; i++) System.out.print("   ");
  }
  public void show(int d) {    
    if (right==null) { spaces(d+1); System.out.println("--"); } else  right.show(d+1);
    spaces(d); System.out.println(data);
    if (left==null)  { spaces(d+1); System.out.println("--"); } else  left.show(d+1);
  }
}