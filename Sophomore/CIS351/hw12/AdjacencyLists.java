//package ods;
/** A version of Morin's AdjancenyLists */
import java.util.*;
import java.io.*;

public class AdjacencyLists implements Graph {
  // Instance variables ///////////////////////////////////////
  /** the number of vertices in the graph */
  int n;
  /** the array adjacency lists  */  
  List<Integer>[] adj;
  
  // Constructor  /////////////////////////////////////////////
  @SuppressWarnings("unchecked")
  public AdjacencyLists(int n0) {
    n = n0;
    adj = (List<Integer>[])new List[n];
    for (int i = 0; i < n; i++) 
      adj[i] = new LinkedList<Integer>();
  }
  
  ////////////////////////////////////////////////////////////  
  // Instance methods  ///////////////////////////////////////
  ////////////////////////////////////////////////////////////
  
  /** Returns a copy of this AdjacencyLists instance.
    * @return a clone of this AdjacencyLists instance
    */
  @SuppressWarnings("unchecked")
  public Object clone() {
    AdjacencyLists other = new AdjacencyLists(n);  
    for (int i = 0; i < n; i++) 
      other.adj[i] = (LinkedList<Integer>)(((LinkedList<Integer>)adj[i]).clone());
    return (Object) other;
  }   
  ////////////////////////////////////////////////////////////   
  /** Add an edge to the graph. 
    * @param i the source vertex of the edge
    * @param j the target vertex of the edge
    */
  public void addEdge(int i, int j) { adj[i].add(j); }
  ////////////////////////////////////////////////////////////   
  /** Tests if the graph has a particular edge. 
    * @param i the source vertex of the edge
    * @param j the target vertex of the edge  
    */ 
  public boolean hasEdge(int i, int j) { return adj[i].contains(j); }
  //////////////////////////////////////////////////////////// 
  /** Count the number of edges with target i.
    * @param i the vertex
    * @return the number of edges with target i
    */ 
  public int inDegree(int i) {
    int deg = 0;
    for (List<Integer> lst : adj)
      if (lst.contains(i)) deg++;
    return deg;
  }
  //////////////////////////////////////////////////////////// 
  /** Construct the list of edges with target i.
    * @param i the vertex
    * @return a list of edges with target i 
    */ 
  public List<Integer> inEdges(int i) {
    List<Integer> edges = new LinkedList<Integer>();
    for (int j = 0; j < n; j++)
      if (adj[j].contains(i)) edges.add(j);
    return edges;
  }
  //////////////////////////////////////////////////////////// 
  /** Return the number of vertices in the graph.
    * @return the number of vertices in the graph
    */ 
  public int nVertices() { return n; }
  /** count the number of edges with source i
    * @param i the vertex
    * @return the number of edges with source i
    */ 
  public int outDegree(int i) { return adj[i].size(); }
  //////////////////////////////////////////////////////////// 
  /** Return the list of edges with source i.
    * @param i the vertex
    * @return a list of edges with source i 
    */ 
  public List<Integer> outEdges(int i) { return adj[i]; }
  //////////////////////////////////////////////////////////// 
  /** Remove an edge to the graph.
    * @param i the source vertex of the edge
    * @param j the target vertex of the edge
    */
  public void removeEdge(int i, int j) { adj[i].remove((Integer)j); } 
  //////////////////////////////////////////////////////////// 
  /** Print the adjacency lists. */
  public void print() {
    for (int i = 0; i<n; i++) 
      System.out.printf("%3d: %s\n",i,adj[i]);
    System.out.println();
  }
    //////////////////////////////////////////////////////////// 
  /** Print the graph as a GraphViz file (see http://www.graphviz.org). 
    * @param fileName the name of the file to write
    */
  public void gvPrint(String fileName) {
    try{
      PrintWriter writer = new PrintWriter(fileName);
      writer.println("digraph g {\n   rankdir=LR \n");
      for (int i = 0; i<n; i++) {
        writer.print("   ");
        for (Integer j : adj[i]) writer.print(i+"->"+j+";  ");
        writer.println();
      }
      writer.println("}");
      writer.close();
      System.out.println("Graph written to "+fileName);
    } catch (Exception e) { System.out.println("Whoops: "+ e); }
  }
}
