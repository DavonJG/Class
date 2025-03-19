import java.util.ListIterator;

/** A subclass of DLList that keeps a sorted (from smallest to biggest) list of items.
  * A dummy node is used to simplify the code.
  * @author Davon Grant
  * @param <T> the type of elements stored in the list which is assumed to implement
  *   the Comparable interface.
  */
public class Ordered<T extends Comparable<T>> extends DLList<T> {
  //////////////////////////////////////////////////////////////////////// 
  /** Constructs an empty Ordered list (Just call's DLList's constructor.)
    */
  public Ordered() { super(); }
  
  ////////////////////////////////////////////////////////////////////////
  // OVERRIDDEN METHODS
  /** Adds a new value to the Ordered list so that the elements are
    * in <code>compareTo</code> order.  <i>Important:</i>
    * If at the start there is already an list element equal to 
    * <code>val</code>, then nothing is added to the list.
    * <p><b>Examples:</b>
    * <ul>
    * <li> If <code>lst = [1,5,23,97]</code>, then after lst.add(12), 
    * <code>lst = [1,5,12,23,97]</code>.
    * <li> If <code>lst = [1,5,23,97]</code>, then after lst.add(23), 
    * <code>lst = [1,5,23,97]</code>.
    * </ul>
    * <p> <b>HOMEWORK PROBLEM.</b> 
    * @param val the value to be added
    * @return true iff a new item was added to the list.
    */
  public boolean add(T val) {
    Node node;
    int x;
    
    /****************************************
      * Deal with an empty list
      * *************************************/
    if (this.AHEAD.next == BEHIND) { //if empty
      this.addBefore(BEHIND, val); //add
      return true;
    }
    
    /****************************************
      * If its not empty, then do the following:
      * *************************************/
    for (node = AHEAD.next, x = 0; x < n; x++, node = node.next) {
      if (val.compareTo(this.get(x)) < 0) { //compares val to the item in the list
        this.addBefore(node, val); //add the val to the correct position by using compareTo()
        return true;
      }
      else if (x == n-1) {
        this.addBefore(BEHIND, val); //if val is the largest item, put it at the very end.
        return true;
      }
    }
    return false; //if nothing was added, return false.
  }
  
  
  class Iterator implements ListIterator<T> {
    /** p is the node whose value is returned by next() */
    Node p;
    /** last is the last node whose value was returned by next() or previous() */
    Node last;
    /** i is the index of p */
    int i;
    // CONSTRUCTOR
    Iterator(Ordered<T> l, int iInit) { i = iInit; p = l.getNode(i); last = null; }
    public boolean hasNext()     { return p != BEHIND;     }
    public boolean hasPrevious() { return p.prev != AHEAD; }
    public int nextIndex()       { return i;               }
    public int previousIndex()   { return i-1;             }
    
    public void add(T x)            { throw new UnsupportedOperationException(); }
    public void set(T x)            { throw new UnsupportedOperationException(); }  
    
    public T next()      { last = p;  p = p.next;  i++;  return last.val;        }
    public T previous()  { last = p = p.prev;      i--;  return last.val;        }    
    public void remove() { 
      if (p == last) p = p.next; 
      Ordered.this.remove(last); 
    }   
  }  
  /** <b>Unsupported</b> 
    * @throws UnsupportedOperationException always */
  public void add(int i, T x)       { throw new UnsupportedOperationException(); }
  /** <b>Unsupported</b> 
    * @throws UnsupportedOperationException always */  
  public T set(int i, T x)          { throw new UnsupportedOperationException(); }
  
  ////////////////////////////////////////////////////////////////////////
  // new methods  
  ////////////////////////////////////////////////////////////////////////
  /** Construct a list of neighbors of x in the list.
    *  <p> <b>HOMEWORK PROBLEM.</b> 
    * @param x the value for the neighborhood
    * @return a list consisting of up to three elements:
    * <ul>
    * <li> the element of the list which has the largest value less than <code>x</code>
    * (if such an element exists)
    * <li> <code>x</code> if <code>x</code> is in the list
    * <li> the element of the list which has the smallest value greater than <code>x</code>
    * (if such an element exists)
    * </ul>
    * <b>Examples:</b> If <code>lst</code> consists of [1,3,5,7], then
    * <ul>
    * <li>  lst.neighbors(0) would return [1]
    * <li>  lst.neighbors(1) would return [1,3]
    * <li>  lst.neighbors(8) would return [7]
    * <li>  lst.neighbors(7) would return [5,7]
    * <li>  lst.neighbors(2) would return [1,3]
    * <li>  lst.neighbors(3) would return [1,3,5]
    * </ul>
    */
  
  public Ordered<T> neighbors(T x){
    Ordered<T> ans = new Ordered<T>();
    
    //if x is in the list, then do the following
    if (this.contains(x)) { 
      System.out.println("in it");
      int i = 0;
      while (!this.get(i).equals(x)) { 
        i++;
      }
      //deal with any out of bounds possibilities
      if (i != 0){
        ans.add(this.get(i-1));
      }
      ans.add(x);
      if (i != n-1){
        ans.add(this.get(i+1));
      }
    }
    
    //if it isnt
    else {
      int z;
      for (z = 0; z < n; z++) {
        if (x.compareTo(this.get(z)) < 0) {
          //if x is smaller than the first item:
          if (z == 0) {
            ans.add(this.get(z)); //add 
            return ans;
          }
          else {
            ans.add(this.get(z-1)); //add
            ans.add(this.get(z)); 
            return ans;
          }
        }
        //if x is the biggest item on the list, then do the following
        else if (z == n-1) { 
          ans.add(this.get(z));
          return ans;
        }
      }
    }
    
    return ans;
    
  }
  
  
  /** Checks if this list is sorted <i>(for debugging proposes)</i>
    * @return true iff the list is sorted
    */
  public boolean checkSorted() {
    if (size() <= 1) return true;
    
    T prior            = get(0);    
    ListIterator<T> it = listIterator(1);
    
    while (it.hasNext()) {
      T current = it.next();
      if (prior.compareTo(current) > 0) return false;
      prior = current;
    } 
    return true;
  }
  ////////////////////////////////////////////////////////////////////////
  public static void main(String... argv) {
    Ordered<Integer> lst = new Ordered<Integer>();
    lst.add(11);
  }
}