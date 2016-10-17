public class Boxcar extends RailroadCar{
  private double height, width, length; //instance variables
  public static void main(String[]args){
    Boxcar b1 = new Boxcar();
    Boxcar b2 = new Boxcar(60,9,11);
    
    System.out.println("**********************\n Volume & get + set test: \n**********************");
    System.out.println("b1.volume() = " + b1.volume()); //test volume 
    System.out.println("b1.getLength() * b1.getHeight() * b1.getWidth() = " + b1.getLength() * b1.getHeight() * b1.getWidth()); //test get methods to calculate volume
    System.out.println("b2.volume() = " + b2.volume()); //test volume
    System.out.println("Changing b1 length to 60, height to 9, and width to 11...");
    b1.setLength(60); b1.setHeight(9); b1.setWidth(11);
    System.out.println("b1.getLength() = " + b1.getLength() + "\nb1.getHeight() = " + b1.getHeight() + "\nb1.getWidth() = " + b1.getWidth()); //test to see if set methods worked
    System.out.println("**************************************************************"); //formatting
      System.out.println("Testing extenion of RailroadCar by setting weight to 999 and yearMade to 1950...");
    System.out.println("**************************************************************"); //formatting
      b1.setWeight(999); b1.set_yearMade(1950);
    System.out.println("weight = " + b1.getWeight() + "\nyearMade = " + b1.get_yearMade()); //test to see if set methods worked
  }
  public Boxcar(){ //default contructor
    height = 10;
    width = 9.4;
    length = 55;
  }
  
  public Boxcar(double h, double l, double w){ //three parameter constructor
    height = h;
    length = l;
    width = w;
  }
  public double volume(){ //volume method
    double v = this.height * this.width * this.length;
    return v;
  }
  
  //get & set methods
  protected double getWeight(){
    return weight;
  }
  
  protected int get_yearMade(){
    return yearMade;
  }
  
  protected double getHeight(){
    return height;
  }
  
  protected double getLength(){
    return length;
  }
  
  protected double getWidth(){
    return width;
  }
  
  protected void setWeight(double w){
    weight = w;
  }
  
  protected void set_yearMade(int y){
    yearMade = y;
  }
  
  protected void setHeight(double h){
    height = h;
  }
  
  protected void setLength(double l){
    length = l;
  }
  
  protected void setWidth(double w){
    width = w;
  }
}