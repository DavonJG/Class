import java.io.*;
import java.util.*;

public class Test8 {
  public static final int MINSIZE = 6;
  //////////////////////////////////////////////////////////////////////
  /** Strip off "s'" and "s'" from the end of input strings.
    * <p><b>Example:</b> <code>tidy("Sam's")</code> returns "Sam".
    * @param str the String to tidy up
    * @return the result of the tidying
    */
  public static String tidy(String str) {
    String ans = str.toLowerCase();
    if (ans.endsWith("'s") || ans.endsWith("s'"))
      return ans.substring(0,ans.length()-2);
    else 
      return ans;
  }
  //////////////////////////////////////////////////////////////////////
  /** Convert an Ordered list to an array
    * @param lst the list to convert
    * @return the array version of the list
    */
  public static String[] toArray(Ordered<String> lst) {
    String[] ans = new String[lst.size()];
    ListIterator<String> it = lst.listIterator(0);
    int i=0;
    while (it.hasNext()) { ans[i] = it.next(); i++; }
    return ans;
  }
  
  //////////////////////////////////////////////////////////////////////
  /** Test an application of the add method the Ordered class 
    * @param lst the list to be added to
    * @param str the String to add
    * @param target what the result should be (as an array of strings)
    */
  
  public static void checkAdd(Ordered<String> lst, String str, String... target) {
    System.out.print(" Testing: lst.add("+str+") = ");
    lst.add(str);
    if (Arrays.equals(toArray(lst),target))
      System.out.println(lst + "\n\tCHECK!");
    else 
      System.out.println(lst + "\n\tWRONG! It should be: "+Arrays.toString(target));
    lst.linkCheck();
  }
  
  //////////////////////////////////////////////////////////////////////    
  /** Test an application of the neighbors method the Ordered class 
    * @param lst the list to be searched
    * @param str the String to find the neighbors of
    * @param target what the result should be (as an array of strings)
    */
  public static void checkNeighbors(Ordered<String> lst, String str, String... target) {
    System.out.print(" Testing: lst.neighbors("+str+") = ");
    Ordered<String> result = lst.neighbors(str);
    if (Arrays.equals(toArray(result),target))
      System.out.println(result + "\n\tCHECK!");
    else 
      System.out.println(result + "\n\tWRONG! It should be: "+Arrays.toString(target));
    result.linkCheck();
  }
  
  //////////////////////////////////////////////////////////////////////
  public static void main(String[] argv) throws IOException  {
    // PART I
    Ordered<String> emp  = new Ordered<String>();
    Ordered<String> wrds = new Ordered<String>();
        
    System.out.println("\n**TESTING add**\n");
    checkAdd(wrds,"owl",  "owl");
    checkAdd(wrds,"gnu",  "gnu","owl");
    checkAdd(wrds,"yak",  "gnu","owl","yak");
    checkAdd(wrds,"bee",  "bee","gnu","owl","yak");   
    checkAdd(wrds,"cat",  "bee","cat","gnu","owl","yak");  
    checkAdd(wrds,"eel",  "bee","cat","eel","gnu","owl","yak");  
    checkAdd(wrds,"dog",  "bee","cat","dog","eel","gnu","owl","yak");     
    checkAdd(wrds,"cow",  "bee","cat","cow","dog","eel","gnu","owl","yak");      
    checkAdd(wrds,"rat",  "bee","cat","cow","dog","eel","gnu","owl","rat","yak");     
    checkAdd(wrds,"ram",  "bee","cat","cow","dog","eel","gnu","owl","ram","rat","yak");  
    
    System.out.println("\n**TESTING neighbors**\n");
    checkNeighbors(emp, "gnu");
    checkNeighbors(wrds,"ant",   "bee");
    checkNeighbors(wrds,"bee",   "bee","cat");  
    checkNeighbors(wrds,"zebra", "yak");    
    checkNeighbors(wrds,"yak",   "rat","yak");
    checkNeighbors(wrds,"eel",   "dog","eel","gnu");
    checkNeighbors(wrds,"ewe",   "eel","gnu");
    
    
    Iterator<String> it = wrds.iterator();
    System.out.print("The list wrds: " );
    while (it.hasNext()) {
      String wrd = it.next();
      System.out.print(wrd+" ");
    }
    System.out.println("\n");
    
    
    // PART II
    System.out.println("\n**Building concordence**\n");
    
    /** a list of words from the text. */
    Ordered<String> lex         = new Ordered<String>();
    
    /** a table of Entry's to build the concordence */
    ChainedHashTable<Entry> tab = new ChainedHashTable<Entry>();
    
    final String inFile = "fox.txt";
    Scanner inp = new Scanner(new File(inFile));
    int lineNumber = 0; // current line number of the input text

    // scan the text, build the word list, lex, and concordence table, tab
    while(inp.hasNextLine()){ //while there are more lines
      Scanner scan = new Scanner(inp.nextLine());
      scan.useDelimiter("[\\s,.!?-]"); 
      while(scan.hasNext()){
        String s = tidy(scan.next()); //use tidy to instantiate new String
        if(s.length() >= MINSIZE){
          if(!lex.contains(s)){
            lex.add(s);
            tab.add(new Entry(s, lineNumber));
          }
          else{
            if(!tab.find(s).getOccurrences().contains(lineNumber)){
              tab.find(s).update(lineNumber);
            }
          }
        }
      }
      lineNumber++;
    }
    
    // Now print the concordence in alphabetical order
    int temp = 0;
    while(temp < lex.size()){
      System.out.println(tab.find(lex.get(temp)));
      temp++;
    }
  } 

  //////////////////////////////////////////////////////////////////////
}