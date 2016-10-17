import java.util.Date;

public class Box3 {
    private static int counter = 1;
    public int value;
  
    public Box3(){
      if(counter == 1){ // only display the timestamp if it the first time a Box3 is declared.
        timestamp();
        counter--;
      }
      value = 0;    
    }
    public void set(int v) { value = v;    }
    public int get()       { return value; }
    private static void timestamp() { 
      System.out.println( (new Date()) );
    }
}

