import java.util.*;

/******************************************************************************
  * This is binary search tree class over items of type T.  It is roughly 
  * along the lines of the class described in section 6.2 of Open Data Structures.  
  * The one big change is that this class uses a sentinel node ANCHOR, where
  * <ul>
  *   <li> ANCHOR.left = the actual root of the tree
  *   <li> ANCHOR.parent = ANCHOR.right = ANCHOR.data = null
  * </ul>
  * We compare data fields via the method <code>compare</code> below where
  * we arrange that null acts like +&infin;, so that the ANCHOR node is the 
  * rightmost/largest node in the (extended) tree. 
  * 
  * @author Davon Grant
  *
  * @version
  *   Nov 02, 1887
  ****************************************************************************/


public class BSTree<T extends Comparable<T>> {
  //////////////////////////////////////////////////////////////////////
  // instance variables
  /** The sentinel node for of the tree ANCHOR.left is the actual root */
  protected BSNode<T> ANCHOR;
  /** The number of nodes (elements) currently in the tree */
  protected int n;
  
  //////////////////////////////////////////////////////////////////////
  // Constructor
  public BSTree() { ANCHOR = new BSNode<T>(null);  n = 0; }
  
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
  /** Search for a value in the tree
    * @param u the BSNode to start the BST-search from
    * @param x the value to search for
    * @return the last node on the search path for x
    */
  protected BSNode<T> findLast(BSNode<T> u,T x) {
    if (u==null) return null;
    for(;;) {
      int cmp = compare(x,u.data);
      if (cmp==0 || (cmp<0 && u.left==null) || (cmp>0 && u.right==null)) 
        return u;
      if (cmp<0)  u = u.left; else u = u.right;
    }
  }  
  //////////////////////////////////////////////////////////////////////
  /** Add a Node with value x to the BST (if it is not already there).
    * @param x the value to add
    * @return true iff a node was added.
    */
  protected boolean add(T x) {
    BSNode<T> u = findLast(ANCHOR,x);
    int cmp = compare(x,u.data);
    if (cmp==0)    return false;
    if (cmp<0)     u.left  = new BSNode<T>(x,null,null,u);
    else /*cmp>0*/ u.right = new BSNode<T>(x,null,null,u);
    n++;
    return true;   
  }
  
  //////////////////////////////////////////////////////////////////////  
  /** Finds the leftmost node below node <code>u</code>
    * @param u the node to start the search
    * @return the leftmost node below node <code>u</code>
    */ 
  protected BSNode<T> leftmostBelow(BSNode<T> u) {
    if (u==null) return null;
    while (u.left != null) u = u.left;
    return u;
  }
  //////////////////////////////////////////////////////////////////////  
  /** Returns the smallest value in the tree
    * @return the smallest value in the tree
    */ 
  public T smallest() { return (leftmostBelow(ANCHOR.left)).data; }
  //////////////////////////////////////////////////////////////////////  
  /** Finds the rightmost node below node <code>u</code>
    * @param u the node at which to start the search
    * @return the rightmost node below node <code>u</code>
    */ 
  protected BSNode<T> rightmostBelow(BSNode<T> u) {
    if (u==null) return null;
    while (u.right != null) u = u.right;
    return u;
  }
  //////////////////////////////////////////////////////////////////////  
  /** Returns the largest value in the tree
    * @return the largest value in the tree
    */   
  public T largest() { return (rightmostBelow(ANCHOR.left)).data; }  
  ////////////////////////////////////////////////////////////////////// 
  /** Delete the node with key value <code>x</code>, if it has such a node.
    * @param x the value to be deleted
    * @return true iff a node was actually deleted.
    */
  public boolean delete(T x) {
    if (x==null) return false;
    BSNode<T> u = findLast(ANCHOR,x);
    if (compare(x,u.data)!=0) return false;
    remove(u);
    return true;
  }
  /** Remove the node u --- ASSUMING u has at most one child
    * @param u the node to be removed
    */
  protected void splice(BSNode<T> u) {
    if (u.left==null && u.right==null) { // u is a leaf
      if (u.parent.left==u) u.parent.left  = null;
      else                 u.parent.right = null;
    }
    else if (u.left!=null) { // so u.right == null
      u.left.parent = u.parent;
      if (u.parent.left==u) u.parent.left  = u.left;
      else                 u.parent.right = u.left;
    }
    else { // u.right!=null  // so u.left == null
      u.right.parent = u.parent;
      if (u.parent.left==u) u.parent.left  = u.right;
      else                 u.parent.right = u.right; 
    }
    n--;
  }
  /** Remove the node u from the binary search tree
    * @param u the node to be removed
    */
  protected void remove(BSNode<T> u) {
    if (u.left == null || u.right == null) 
      splice(u);
    else {
      BSNode<T> w = leftmostBelow(u.right);
      u.data = w.data;
      splice(w);
    }
  }    
  
  //////////////////////////////////////////////////////////////////////
  /** Return a copy of this BSTree
    * @return a copy of this BSTree
    */ 
  public BSTree<T> copy() {
    BSTree<T> cp  = new BSTree<T>();
    cp.ANCHOR.left = copy(ANCHOR.left,cp.ANCHOR);
    cp.n          = n;
    return cp;
  }
  private BSNode<T> copy(BSNode<T> u,BSNode<T> p) {
    if (u==null) return null;
    BSNode<T> newu = new BSNode<T>(u.data,null,null,p);
    newu.left      = copy(u.left,newu);
    newu.right     = copy(u.right,newu);
    return newu;
  }
  
  //////////////////////////////////////////////////////////////////////  
  /** Return the in-order successor of u in the tree, if any
    * @param u the node to find the successor of
    * @return the in-order successor of u in the tree which
    * is null if u is the rightmost node in the tree.
    */ 
  protected BSNode<T> successor(BSNode<T> u) {
    if (u==null || u==ANCHOR) return null;
    if (u.right!=null) return leftmostBelow(u.right);
    BSNode<T> child = u;
    BSNode<T> p = child.parent;
    while (p!=null && child == p.right) {
      child = p;
      p     = child.parent;
    }
    return p; 
  }
  ////////////////////////////////////////////////////////////////////// 
  /** returns the in-order predeccessor of a BSNode u in the BSTree, 
    * if that BSNode has a predecessor.
    *
    * @param u - the node we want the predecesor of
    * @return - the predecesor, or null if u is already the leftmost.
    * */ 
  
  protected BSNode<T> predecessor(BSNode<T> u) {
    if (u==null || u ==ANCHOR){ //mirror successor
      return null;
    }
    if (u.left != null){
      return rightmostBelow(u.left);
    }
    BSNode<T> n = u;
    BSNode<T> p = n.parent;
    while(p != null && n == p.left){
      n = p;
      p = n.parent;
    }
    return p;
  }
  
  //////////////////////////////////////////////////////////////////////  
  /** <h2><strong>HOMEWORK PROBLEM</strong></h2>
    */ 
  public boolean equals(Object obj) {
    if (obj == this) return true;
    if (obj == null || obj.getClass() != this.getClass())  return false;
    
    @SuppressWarnings({"unchecked"}) 
    BSTree<T> other = (BSTree<T>) obj;
    return eq(this.ANCHOR,other.ANCHOR);
  }
  
  /** Tests whether the subtrees rooted at u and v are equal.
    * @param u the first BSNode
    * @param v the second BSNode
    * @return true iff the subtrees rooted at u and v are equal.
    */ 
  private boolean eq(BSNode<T> u,BSNode<T> v) {
    if (u == null && v == null){
      return true;
    } 
    else if (u == null || v == null){
      return false;
    } 
    else {
      return u.data == v.data && eq(u.left, v.left) && eq(u.right, v.right);
    }
  }
  
  ////////////////////////////////////////////////////////////////////// 
  /** Constructs an in-order list of the value in this tree that are 
    * between small and large - inclusive.
    * <h2><strong>HOMEWORK PROBLEM</strong></h2>
    * @param small the left-end of the interval of values
    * @param large the right-end of the interval of values
    * @return an in-order list of all the values in the tree that are between
    * small and large - inclusive.
    */ 
  protected ArrayList<T> between(T small, T large) {
    return between(ANCHOR.left,small,large);
  }
  
  private ArrayList<T> between(BSNode<T> u,T small, T large) {
    ArrayList<T> aList = new ArrayList<T>();
    if (u == null){
      return aList;
    }
    aList.addAll(between(u.left, small, large));
    if (small.compareTo(u.data) < 0 && large.compareTo(u.data) > 0){
      aList.add(u.data);
    }
    aList.addAll(between(u.right, small, large));
    return aList;
  }
  
  /////////////////////////////////////////////////////////// 
  /** Constructs a listIterator starting at the left or right end of the BSTree.
    * <h2><strong>HOMEWORK PROBLEM</strong></h2>
    * @param leftToRight if <code>true</code>, start the iterator at the leftmost
    * node of the tree, if <code>false</code>, start the iterator at the
    * rightmost node of the tree (i.e., <code>ANCHOR</code>).
    * @return a new a listIterator with indicated starting position
    */
  public ListIterator<T> iterator(boolean leftToRight) {
    return new Iterator(leftToRight);
  }
  /////////////////////////////////////////////////////////// 
  class Iterator implements ListIterator<T> {
    /** p is the node whose value is returned by next() */
    BSNode<T> p;
    /** last is the last node whose value was returned by next() or previous() */
    BSNode<T> last;
    /** leftmost is the left-most element of the tree */
    BSNode<T> leftmost;
    /** rightmost is the right-most element of the tree */
    BSNode<T> rightmost;
    
    // CONSTRUCTORS
    Iterator(boolean leftToRight) {
      last = null;
      leftmost = leftmostBelow(ANCHOR);
      rightmost = rightmostBelow(ANCHOR.left); //added
      p = (leftToRight)?leftmost:rightmost;
    }
    public boolean hasNext() {
      return !eq(p, ANCHOR);
    }
    
    public boolean hasPrevious() {
      return !eq(p, leftmost.left);
    }
    
    public T next() {
      System.out.println(p.data);
      last = p;
      p = successor(p);
      return last.data;
    }
    
    public T previous() {
      last = p;
      p = predecessor(p);
      return last.data;
    }
    
    //given
    public int nextIndex()        { throw new UnsupportedOperationException(); }
    public int previousIndex()    { throw new UnsupportedOperationException(); }
    public void add(T x)          { throw new UnsupportedOperationException(); }   
    public void set(T x)          { throw new UnsupportedOperationException(); }    
    public void remove()          { throw new UnsupportedOperationException(); }  
  }
  
  //////////////////////////////////////////////////////////////////////  
  //////////////////////////////////////////////////////////////////////  
  // Testing utilities
  //////////////////////////////////////////////////////////////////////  
  //////////////////////////////////////////////////////////////////////  
  /** Print the tree */
  private void show() { 
    if (ANCHOR.left==null) System.out.println("--");
    else ANCHOR.left.show(0);
  }
  
  //////////////////////////////////////////////////////////////////////
  /** Construct an ArrayList from a string
    * @param str the string to build the list from
    * @return the constructed list
    */
  private static ArrayList<Character> make(String str) {
    ArrayList<Character> ans = new ArrayList<Character>();   
    for(int i=0; i<str.length();i++) ans.add(str.charAt(i));
    return ans;      
  }
  //////////////////////////////////////////////////////////////////////
  // Test for the between method
  private static void betweenTest(BSTree<Character> t,
                                  Character small, 
                                  Character large,
                                  String target) {
    ArrayList<Character> result = t.between(small,large);
    ArrayList<Character> targ = make(target);
    System.out.print("bst1.between('"+small+"','"+large+"') = " + result);
    if (result.equals(targ))
      System.out.println("\tCheck");
    else 
      System.out.println("\tWRONG, should be = " + targ);
    
  }
  
  //////////////////////////////////////////////////////////////////////
  // Test for the equals method 
  private static void eqTest(BSTree<Character> t1,
                             BSTree<Character> t2, 
                             boolean           target) {
    boolean result = t1.equals(t2);
    System.out.print("t1.equals(t2) = " + result);
    if (result==target) 
      System.out.println("\tCheck");
    else
      System.out.println("\tWrong");      
  }
  
  //////////////////////////////////////////////////////////////////////  
  // Test program for the class 
  public static void main(String[] argv) {
    char[] cs = {'f','l','u','f','f','y',
      'k','i','t','t','e','n',
      't','e','a',
      'p','a','r','t','y'}; 
    
    BSNode<Character> u; 
    ArrayList<Character> lst  = make("");
    ArrayList<Character> lst1 = make("aefiklnprtuy");    
    ArrayList<Character> lst2 = make("yutrpnlkifea");   
    
    BSTree<Character> bst1 = new BSTree<Character>();
    for (char c : cs) bst1.add(c);
    bst1.show();
    
    //
    // Testing for between
    //
    
    System.out.println("-----------------------------------------");
    betweenTest(bst1,'b','d',"");
    betweenTest(bst1,'z','a',"");
    betweenTest(bst1,'c','q',"efiklnp");
    betweenTest(bst1,'m','z',"nprtuy");
    System.out.println("-----------------------------------------");
    
    //
    // Testing for equals
    //
    
    BSTree<Character> bst2 = new BSTree<Character>();
    BSTree<Character> bst3 = new BSTree<Character>();
    // bst2.show();    bst3.show();
    System.out.print("equals test 1:\t"); eqTest(bst2,bst3,true);
    bst2.add('m');
    System.out.print("equals test 2:\t"); eqTest(bst2,bst3,false);    
    System.out.print("equals test 3:\t"); eqTest(bst3,bst2,false);     
    bst3.add('x');
    System.out.print("equals test 4:\t"); eqTest(bst2,bst3,false);   
    bst3.delete('x'); bst3.add('m');
    System.out.print("equals test 5:\t"); eqTest(bst3,bst2,true);  
    bst2.add('f'); bst2.add('c'); bst2.add('k'); bst2.add('p'); 
    bst3.add('f'); bst3.add('c'); bst3.add('k'); bst3.add('p'); 
    System.out.print("equals test 6:\t"); eqTest(bst3,bst2,true);    
    bst2.delete('k'); 
    System.out.print("equals test 7:\t"); eqTest(bst3,bst2,false);   
    bst2.add('j');
    System.out.print("equals test 8:\t"); eqTest(bst3,bst2,false);   
    
    
    System.out.println("-----------------------------------------");
    
    //
    // Testing for predecessor
    //
    
    System.out.println("Inorder traversals using successor and predecessor");
    
    System.out.print("\tIn order (left to right): ");
    u = bst1.leftmostBelow(bst1.ANCHOR);
    
    while (u!=bst1.ANCHOR) {
      lst.add(u.data);
      u = bst1.successor(u);
    }
    System.out.println(lst); 
    if (lst.equals(lst1)) System.out.println("\t\tCheck");
    else System.out.println("\t\tWrong, it should be "+lst1);
    
    lst.clear();
    System.out.print("\tIn order (right to left): ");
    u = bst1.rightmostBelow(bst1.ANCHOR.left);
    while (u!=null) {
      lst.add(u.data);
      u = bst1.predecessor(u);
    }
    System.out.println(lst);
    if (lst.equals(lst2)) System.out.println("\tCheck");
    else System.out.println("\t\tWrong, it should be "+lst2);
    
    System.out.println("-----------------------------------------");
    
    //
    // Testing for iterator
    //
    
    System.out.println("Inorder traversals using the ListIterator");
    
    ListIterator<Character> it;
    
    lst.clear();
    System.out.print("\tIn order (left to right): ");
    it = bst1.iterator(true);
    while (it.hasNext()) lst.add(it.next());
    System.out.println(lst);
    if (lst.equals(lst1)) System.out.println("\t\tCheck");
    else System.out.println("\t\tWrong, it should be "+lst1);
    
    lst.clear();   
    System.out.print("\tIn order (right to left): ");
    it = bst1.iterator(false);
    while (it.hasPrevious()) lst.add(it.previous());
    System.out.println(lst);   
    if (lst.equals(lst2)) System.out.println("\tCheck");
    else System.out.println("\t\tWrong, it should be "+lst2);
    
  }    
  //////////////////////////////////////////////////////////////////////
}
