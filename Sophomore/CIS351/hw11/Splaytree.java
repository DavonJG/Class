// STARTING CODE: Version 1.3 (Thu Nov 10 10:10:32 EST 2016)
import java.util.*;

/**
 * Description of the class (fill in)
 */

public class Splaytree<T extends Comparable<T>> {
  //////////////////////////////////////////////////////////////////////
  // instance variables
  /** The sentinel node for of the tree ANCHOR.left is the actual root */
  protected BSNode<T> ANCHOR;
  
  //////////////////////////////////////////////////////////////////////
  // Constructor
  public Splaytree() { ANCHOR = new BSNode<T>(null); }
  
  //////////////////////////////////////////////////////////////////////
  /** compares two T values where null is treated as +infinity
    * @param x first thing to compare
    * @param y second thing to compare
    * @return (i) a negative number if x &lt; y; (ii) 0, if x = y; 
    *   (iii) a positive number, if x &gt; y
    */
  public int compare(T x,T y) {
    if (x==null && y==null) return 0; // null == null
    if (y==null) return -1;           // y < null
    if (x==null) return 1;            // null > y
    return x.compareTo(y);
  }
  //////////////////////////////////////////////////////////////////////  
    /**  checks if the tree is empty
    @return true if the tree is empty
    */
  public boolean isEmpty() { return (ANCHOR.left==null); }
  
  //////////////////////////////////////////////////////////////////////  
  /** Tests if a BSNode is the last one on the search path for z
    * @param z the value sought
    * @param u the BSNode to test
    * @return true iff in doing a BST search for z on the tree rooted at u
    *   the search would not continue on beyond u
    */
  private boolean terminal(T z,BSNode<T> u) {
    if (u==null) return true;
    if (compare(z,u.data)==0) return true;
    if (compare(z,u.data)<0) return u.left==null;
    return (u.right==null);
  }
  //////////////////////////////////////////////////////////////////////   
  
  public void splay(T pivot) { ANCHOR.left = splay(pivot,ANCHOR.left); }
  
  /** helper function (where all the work takes place)
    @param T pivot
    @param BSNode<T> u
    @return the subtree rooted at u around the value pivot splayed. 
    */
  private BSNode<T> splay(T pivot, BSNode<T> u) {
    if (u==null || terminal(pivot,u)) return u;
    if (compare(pivot,u.data)<0) {
      if (terminal(pivot,u.left)) return zig(u.left,u.data,u.right);
      BSNode<T> ull = u.left.left;
      T           w = u.left.data;
      BSNode<T> ulr = u.left.right;
      if (compare(pivot,w)<=0) 
        return zigzig(splay(pivot,ull),w,ulr,u.data,u.right);
      else 
        return zigzag(ull,w,splay(pivot,ulr),u.data,u.right);
    }
    else { // pivot > x
      if (terminal(pivot,u.right)) return zag(u.left,u.data,u.right);
      BSNode<T> url = u.right.left;
      T           y = u.right.data;
      BSNode<T> urr = u.right.right;
      if (compare(pivot,y)<=0) 
        return zagzig(u.left,u.data,splay(pivot,url),y,urr);
      else 
        return zagzag(u.left, u.data, url, y, (splay(pivot, urr))); //fixed.
    }
  }
  ////////////////////////////////////////////////////////////////////// 
  private BSNode<T> zig(BSNode<T> ux,T y,BSNode<T> uc) {
    BSNode<T> ua = ux.left;
    T          x = ux.data;
    BSNode<T> ub = ux.right;
    return new BSNode<T>(ua,x,new BSNode<T>(ub,y,uc));
  }
  ////////////////////////////////////////////////////////////////////// 
  /** does the zag reconfiguring of the data (and is the mirror image of zig)
    @param BSNode<T> ua
    @param T x 
    @param BSNode<T> uy
    @return the resulting BSNode<T>
    */
  private BSNode<T> zag(BSNode<T> ua,T x,BSNode<T> uy) {
    BSNode<T> ul = uy.left;
    T          y = uy.data;
    BSNode<T> ur = uy.right;
    return new BSNode<T>(new BSNode<T>(ua, x, ul), y, ur);
  }  
  ////////////////////////////////////////////////////////////////////// 
  private BSNode<T> zigzig(BSNode<T> ux,T y, BSNode<T> uc, T z,BSNode<T> ud) {
    BSNode<T> ua = ux.left;
    T          x = ux.data;
    BSNode<T> ub = ux.right;
    return new BSNode<T>(ua,
                         x,
                         new BSNode<T>(ub,y,new BSNode<T>(uc,z,ud)));
  }
  ////////////////////////////////////////////////////////////////////// 
  /** does the zagzag reconfiguring of the data (and is the mirror image of zigzig). 
    @param BSNode<T> ua
    @param T x 
    @param BSNode<T> ub 
    @param T y 
    @param BSNode<T> uz
    @return the resulting BSNode<T>
    */
  
  private BSNode<T> zagzag(BSNode<T> ua,T x, BSNode<T> ub, T y,BSNode<T> uz) {
    BSNode<T> uc = uz.left;
    T          z = uz.data;
    BSNode<T> ud = uz.right;    
    return new BSNode<T>(new BSNode<T>(new BSNode<T>(ua, x, ub), y, uc), z, ud); //fixed
  }  
  ////////////////////////////////////////////////////////////////////// 
  /** does the zigzag reconfiguring of the data (and is the mirror image of zagzig).  
    @param BSNode<T> ua
    @param T x
    @param BSNode<T> uy
    @param T z
    @param BSNode<T> ud
    @return the resulting BSNode<T>
    */
  private BSNode<T> zigzag(BSNode<T> ua,T x, BSNode<T> uy, T z,BSNode<T> ud) {
    BSNode<T> ub = uy.left;
    T          y = uy.data;
    BSNode<T> uc = uy.right; 
    return new BSNode<T>(new BSNode<T>(ua, x, ub), y, new BSNode<T>(uc, z, ud));
  }
  ////////////////////////////////////////////////////////////////////// 
  private BSNode<T> zagzig(BSNode<T> ua,T x, BSNode<T> uy, T z,BSNode<T> ud) {
    return zigzag(ua,x,uy,z,ud);
  }
  
  //////////////////////////////////////////////////////////////////////
  
  /**  adds x to the tree
    @param T x
    @return true if x was added
    */
  public boolean add(T x) {
    if (isEmpty()) {
      ANCHOR.left = new BSNode<T>(x);
      return true;
    }
    BSNode<T> u = splay(x,ANCHOR.left);
    if (x==u.data) {
      ANCHOR.left = u;
      return false;
    }
    else if (compare(x,u.data) < 0)
      ANCHOR.left = new BSNode<T>(new BSNode<T>(u.left,x,null),u.data,u.right);
    else 
      ANCHOR.left = new BSNode<T>(u.left,u.data,new BSNode<T>(null,x,u.right));   
    return true;
  }
  
  //////////////////////////////////////////////////////////////////////
  /** delete x from the tree (returns true if it was really deleted)  
    @param T x
    @return true if x was deleted
    */
  public boolean delete(T x) {
    if (isEmpty()) return false;
    BSNode<T> u = splay(x,ANCHOR.left);
    if (compare(u.data, x) != 0){
      ANCHOR.left = join(u.left, u.right);
    }
    return false;
  }
  //////////////////////////////////////////////////////////////////////
  /**  joins the two trees rooted at u and v into one new BST – under the assumption that all of the values in u's tree are less than all of the values in v's tree.  
    @param BSNode<T> u
    @param BSNode<T> v
    @return the resulting joined tree.
    */
  public BSNode<T> join(BSNode<T> u, BSNode<T> v) {
    if (u==null) return v;
    if (v==null) return u;
    BSNode<T> w = u;  while (w.right != null) w = w.right;
    // now w.data is the maximum value in u
    splay(w.data);
    w.right = v;
    return w;
  }
  
  //////////////////////////////////////////////////////////////////////
  /** Print the tree */
  private void show() { 
    if (ANCHOR.left==null) System.out.println("--");
    else ANCHOR.left.show(0);
  }
  
  //////////////////////////////////////////////////////////////////////
  private static Splaytree<Character> make(String str) {
    Splaytree<Character> ans = new Splaytree<Character>();
    for(char c : str.toCharArray()) ans.add(c);
    return ans;
  }
  
  //////////////////////////////////////////////////////////////////////
  // Tests of the Splaytree class
  public static void main(String[] argv) {
    Splaytree<Character> t1 = new Splaytree<Character>();  
        
    // Zig demo 
    
       // add your tests here
    
    // Zag demo
    t1 = make("pqr");
    System.out.println("Zag demonstration, before:");
    t1.show();
    System.out.println("-------------------------------");
    System.out.println("After splaying on 'p':");
    t1.splay('r');
    t1.show();
    System.out.println("-------------------------------");
    // YOUR OUTPUT SHOULD LOOK LIKE:
    //-------------------------------
    // Zag demonstration, before:
    //       --
    //    r
    //       --
    // q
    //       --
    //    p
    //       --
    //-------------------------------
    //After splaying on 'r':
    //    --
    // r
    //       --
    //    q
    //          --
    //       p
    //          --
    //-------------------------------
    
    
    System.out.println("-------------------------------");    
    
    // Zagzag demo
    // abcdefghijklmnopqrstuvwxyz
    t1 = make("zyxw");
    System.out.println("Zagzag demonstration, before:");
    t1.show();
    System.out.println("-------------------------------");
    System.out.println("After splaying on 't':");
    t1.splay('z');
    t1.show();
    System.out.println("-------------------------------");
    System.out.println("-------------------------------");
    // YOUR OUTPUT SHOULD LOOK LIKE:
    // -------------------------------
    // Zagzag demonstration, before:
    //          --
    //       z
    //          --
    //    y
    //       --
    // x
    //       --
    //    w
    //       --
    // -------------------------------
    // After splaying on 't':
    //    --
    // z
    //       --
    //    y
    //          --
    //       x
    //             --
    //          w
    //             --
    // -------------------------------  
    

    

    // Zigzig demo 
       // add your tests here    
    
    // Zigzag demo (add your tests)
        
       // add your tests here

    // Zagzig demo (add your tests)
    
        // add your tests here

    
   // OTHER TESTS
    
       // add your tests here 
  }
}