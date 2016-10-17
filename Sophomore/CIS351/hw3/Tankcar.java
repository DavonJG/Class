public class Tankcar extends RailroadCar{
  private double length, radius; //instance variables
  
  public static void main(String[]args){
    Tankcar t1 = new Tankcar();
    Tankcar t2 = new Tankcar(5, 10);
    
    System.out.println("**********************\n Volume & get + set test: \n**********************");
    System.out.println("t1.volume() = " + t1.volume()); //test volume 
    System.out.println("Math.pow(t1.radius, 2)) * t1.length * Math.PI = " + (Math.pow(t1.radius, 2)) * t1.length * Math.PI); //test get methods to calculate volume
    System.out.println("t2.volume() = " + t2.volume()); //test volume 
    System.out.println("Changing t1 length to 99, radius to 8...");
    t1.setLength(99); t1.setRadius(8);
    System.out.println("t1.getLength() = " + t1.getLength() + "\nt1.getRadius() = " + t1.getRadius() ); //test to see if set methods worked
    System.out.println("Testing extenion of RailroadCar by setting weight to 850 and yearMade to 1999...");
    t1.setWeight(850); t1.set_yearMade(1999);
    System.out.println("weight = " + t1.getWeight() + "\nyearMade = " + t1.get_yearMade()); //test to see if set methods worked
  }
  
  public Tankcar(){ //constructor
    length = 47;
    radius = 5.0;
  }
  
  public Tankcar(double l, double r){ //overloaded constructor
    length = l;
    radius = r;
  }
  
  protected double volume(){ //volume method
    double v = (Math.pow(this.radius, 2)) * this.length * Math.PI;
    return v;
  }
  
  //get and set methods
  protected double getWeight(){
    return weight;
  }
  
  protected int get_yearMade(){
    return yearMade;
  }
  
  protected double getLength(){
    return length;
  }
  
  protected double getRadius(){
    return radius;
  }
  
  protected void setLength(double l){
    length = l;
  }
  protected void setRadius(double r){
    radius = r;
  }
  
  protected void setWeight(double w){
    weight = w;
  }
  
  protected void set_yearMade(int y){
    yearMade = y;
  }
}
  