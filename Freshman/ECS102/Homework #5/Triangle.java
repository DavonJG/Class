/*Triangle.java
Davon Grant
dgran101
Section 4
*/
import java.util.Random;

public class Triangle{
  public static void main(String[]args){
    Random gen = new Random(); //create a Random object
    String symbols = "#*&@";
    
    //generate a number and use it to obtain a random symbol.
    int symTemp = gen.nextInt(4); 
    char symbol = symbols.charAt(symTemp);
    int numTemp = gen.nextInt(9)+3; //generate
    //first half of the triangle
    for(int counter=1;counter<numTemp;counter++){
      for(int counter2=1; counter2<=counter; counter2++){
        System.out.print(symbol);
      }
      System.out.println();
    }
    
    //second half of the triangle (after the longest part
    for(int counter=numTemp;counter>0;counter--){
      for(int counter2=1; counter2<=counter; counter2++){
        System.out.print(symbol);
      }
      System.out.println();
    }
  }
}

/*Sample Outputs

& 
&& 
&&& 
&& 
& 

@ 
@@ 
@@@ 
@@@@ 
@@@@@ 
@@@@@@ 
@@@@@@@ 
@@@@@@@@ 
@@@@@@@ 
@@@@@@ 
@@@@@ 
@@@@ 
@@@ 
@@ 
@ 

# 
## 
### 
#### 
##### 
###### 
####### 
######## 
######### 
########## 
########### 
########## 
######### 
######## 
####### 
###### 
##### 
#### 
### 
## 
# 

*/
