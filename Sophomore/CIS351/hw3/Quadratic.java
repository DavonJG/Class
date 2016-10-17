/*********************************************************
* Quadradic is a simple representation of quadratic expressions.
* (Starting code taken from http://www.cis.syr.edu/courses/cis351/Hw03/Quadratic.java)
**********************************************************/
public class Quadratic {
  /** The x<sup>2</sup> coeffecient */
  double a;
  /** The x<sup>1</sup> coeffecient */
  double b;
  /** The constant coeffecient      */
  double c;
  /////////////////////////////////////////////////////////
  // Constructor
  /////////////////////////////////////////////////////////
  /**
   * Initialize a quadratic expression with all coeffecients 0.0 
   **/   
  public Quadratic() { 
    a = b = c = 0.0;
  }

  /////////////////////////////////////////////////////////
  // Setters and Getters
  /////////////////////////////////////////////////////////
  /**
   * Initialize a quadratic expression with the specified
   * values of the coeffecients.
   * @param aVal
   *   the initial value of the x<sup>2</sup> coeff.
   * @param bVal
   *   the initial value of the x<sup>1</sup> coeff.
   * @param cVal
   *   the initial value of the constant coeff.
   **/   
  public Quadratic(double aVal, double bVal, double cVal) {
    a = aVal;
    b = bVal;
    c = cVal;
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Sets the x<sup>2</sup>-coeff.
   * @param  aVal
   *   the value that the x<sup>2</sup> coeff is set to.
   **/   
  public void setA(double aVal) { 
    a = aVal;
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Gets the x<sup>2</sup>-coeff.
   * @return
   *   The value of the x<sup>2</sup> coeff
   **/   
  public double getA() { 
    return a;
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Sets the x<sup>1</sup>-coeff.
   * @param bVal
   *   the value that the x<sup>1</sup> coeff is set to.
   **/   
  public void setB(double bVal) { 
    b = bVal;
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Gets the x<sup>1</sup>-coeff.
   * @return
   *   The value of the x<sup>1</sup> coeff
   **/   
  public double getB() { 
    return b;
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Sets the constant-coeff.
   * @param cVal
   *   the value that the x<sup>2</sup> coeff is set to.
   **/   
  public void setC(double cVal) { 
    c = cVal;
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Gets the constant-coeff.
   * @return
   *   The value of the x<sup>0</sup> coeff
   **/   
  public double getC() { 
    return c;
  }
  
  /////////////////////////////////////////////////////////
  // Other methods
  /////////////////////////////////////////////////////////
  /**
   * Evaluates the quadratic expression at x.
   * @param x
   *   the value at which to evaluate the expression
   * @return
   *   The value of the expression at x
   * <br><br><b>Example:</b>  For  
   * <blockquote>
   * <code>Quadratic p = new Quadratic(1,-4,3);</code> </blockquote> 
   * <ul>
   * <li><code>p.eval(0)</code> returns 3, 
   * <li><code>p.eval(1)</code> returns 0, 
   * <li><code>p.eval(2)</code> returns <b>-1</b>,  &nbsp;&nbsp; <i>(Typo fixed: 17 Sept)</i>
   * <li><code>p.eval(3)</code> returns 0, and 
   * <li><code>p.eval(4)</code> returns 3.</ul>
   **/   
  public double eval(double x)  {
    double result = (this.a * x) + (this.b * x) + c; /* fix! */
    return result;
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Adds two quadratic expressions
   * @param q1
   *   the first quadratic expression
   * @param q2
   *   the second quadratic expression
   * @return
   *   the quadratic expression that is the sum of q1 and a2
   **/   
  public static Quadratic sum(Quadratic q1, Quadratic q2) {
    double newQuadraticA = q1.getA() + q2.getA();
    double newQuadraticB = q1.getB() + q2.getB();
    double newQuadraticC = q1.getC() + q2.getC();
    return new Quadratic(newQuadraticA, newQuadraticB, newQuadraticC);  /* fix! */
  }
  
  /////////////////////////////////////////////////////////
  /**
   * Multiply the coeffs by a scaling value
   * @param r
   *   the scaling value
   * @param q
   *   the quadratic to scale
   * @return
   *   the resulting quadratic expression
   **/   
  public static Quadratic scale(double r, Quadratic q) {
    double a = q.getA();
    double b = q.getB();
    double c = q.getC();
    a = a*r;
    b = b*r;
    c = c*r;
    return new Quadratic(a, b, c);  /* fix! */
  }
  
  /////////////////////////////////////////////////////////
  /**
   * The number of roots of a quadratic expression
   * @return
   *   The number of roots: either 0, 1, 2, or 3 (which
   *   stands for infinity)
   **/   
  public int numRoots() {
    double roots = (Math.pow(this.getB(), 2)) - (4 * this.getA() * this.getC());
    if((this.getA() == 0) && (this.getB() == 0) && (this.getC() == 0)){
      return 3;
    }
    if(this.getA() == 0 && this.getB() == 0){
      return 0;
    }
    if(roots < 0.0){
      return 0;
    }
    else if(roots == 0.0) {
      return 1;
    }
    else if(roots > 0.0){
      return 2;
    }
    else{
      return 3;
    }
  }
  
  /////////////////////////////////////////////////////////
  /**
   * The smallest root of the quadratic expression
   * @return
   *   the smallest root of the quadratic expression.
   *   If there are infinitely many roots or no roots, 0.0
   *   is returned.
   **/   
  public double smallRoot() {
    //find both the small root and big root, and return the larger root (if there is one.)
    
    double x = ((-2*c)/(b + Math.sqrt(Math.pow(b,2) - 4 * a * c)));
    double y = ((-2*c)/(b - Math.sqrt(Math.pow(b,2) - 4 * a * c)));
    if((b - Math.sqrt(Math.pow(b,2) - 4 * a * c)) == 0){
      return 0.0;
    }
    if(x>y){
      return y;
    }
    else if(y>x){
      return x;
    }
    else{
      return 0.0;
    }
  }    

  
  /////////////////////////////////////////////////////////
  /**
   * The biggest root of the quadratic expression
   * @return
   *   the biggest root of the quadratic expression.
   *   If there are infinitely many roots or no roots, 0.0
   *   is returned.
   **/   
  public double bigRoot() {
    //find both the small root and big root, and return the larger root (if there is one.)
    double x = ((-2*c)/(b + Math.sqrt(Math.pow(b,2) - 4 * a * c)));
    double y = ((-2*c)/(b - Math.sqrt(Math.pow(b,2) - 4 * a * c)));
    if(x>y){
      return x;
    }
    else if(y>x){
      return y;
    }
    else{
      return 0.0;
    }
  }
 
  /////////////////////////////////////////////////////////
  /**
   * Convert the Quadratic to a string for printing.
   * @return
   *   a Sting version of the Quadratic
   **/  
  public String toString() {
    return Double.toString(a) + "*x^2 + " +
           Double.toString(b) + "*x + " +
           Double.toString(c);
  }  
  
  /////////////////////////////////////////////////////////
  /**
   * <i>A test method:</i> Print the Quadratic and report on its roots.
   * @param q the Quadratic to report on
   **/   
  public static void report(Quadratic q) {
    System.out.println(q+" has:");
    switch (q.numRoots()) {
      case 0: 
        System.out.println("  no roots");
        break;
      case 1: 
        System.out.println("  one root: "+ q.smallRoot());
        break;
      case 2: 
        System.out.println("  two roots: "+q.smallRoot()+" and "+q.bigRoot());
        break;
      default: 
        System.out.println("  infinitely many roots");
        break;
    }       
  } 

  /////////////////////////////////////////////////////////
  /**
   * A test program for the Quadratic class
   * @param argv command line arguments (not used) 
   */
  public static void main(String argv[]) {
    Quadratic q = new Quadratic();
    Quadratic x = new Quadratic(1.0 , 2.0 , 3.0);
    Quadratic y = new Quadratic(4.0 , 6.0 , 7.0);
    
    //                            Expected Output
    report(q);                //  infinitely many roots
    
    q.setC(1);     report(q); //  no roots
    q.setB(-1);    report(q); //  one root: 1.0
    q.setA(1);     report(q); //  no roots
    q.setB(-2);    report(q); //  one root: 1.0
    q.setB(-3);    report(q); //  two roots: 0.3819660112501051 and 2.618033988749895
    // include more tests of, among other things, eval, scale, and sum.
    System.out.println("------------------ Additional Tests ------------------"); //formatting
    System.out.println("*********************\n****eval() method****\n*********************"); //formatting
    System.out.println("Quadratic x:\na = " + x.getA() + "\nb = " + x.getB() + "\nc = "+ x.getC()); //display the values that will be used with eval()
    System.out.println("x.eval(3) = " + x.eval(3));
    System.out.println("x.eval(4) = " + x.eval(4));
    System.out.println("*********************"); //formatting
    System.out.println("***scale() method:***\n*********************\nQuadratic x:\na = " + x.getA() + "\nb = " + x.getB() + "\nc = "+ x.getC()); //display values before scaling.
    Quadratic n = Quadratic.scale(3, x);
    System.out.println("Quadratic x scaled by 3:\na = " + n.getA() + "\nb = " + n.getB() + "\nc = "+ n.getC()); //display new Quadratic returned after scaling.
    System.out.println("*********************\n****sum() method****\n*********************"); //formatting
    System.out.println("Quadratic x:\na = " + x.getA() + "\nb = " + x.getB() + "\nc = "+ x.getC()); //display the values that will be used with sum()
    System.out.println("Quadratic y:\na = " + y.getA() + "\nb = " + y.getB() + "\nc = "+ y.getC()); //display the values that will be used with sum()
    Quadratic summed = Quadratic.sum(x,y);
    System.out.println("Quadratic summed:\na = " + summed.getA() + "\nb = " + summed.getB() + "\nc = "+ summed.getC()); //display the summed values
  }
}