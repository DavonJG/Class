import java.util.*;

public class GraphTricks {
  // An internal class for collecting info about vertices in d.f.searches
  public static class VertInfo {
    int pre, post, parent;
    VertInfo() { pre = post = parent = -1; }
    public String toString() { return "("+pre+", "+post+", "+parent+")"; }
  }
  // GLOBAL VARIABLES
  /** Keeps track of time during a dfs */
  protected static int clock;  
  
  // Other global variables that you can make use of (or add your own) 
  static boolean flag;
  static int vert1, vert2;
  
  
  /** Perform a bread-first search of g starting at vertex i
    * @param g the graph to search
    * @param i the vertex to search from
    * @return the array of bfs-parents
    */
  public static int[] bfs(Graph g, int r) {
    boolean[] seen   = new boolean[g.nVertices()];
    Queue<Integer> q = new LinkedList<Integer>();
    int parent[]     = new int[g.nVertices()];
    
    for (int i=0; i<parent.length; i++) { 
       seen[i] = false; parent[i] = -1; 
    }
    q.add(r);
    seen[r] = true;
    
    while (!q.isEmpty()) {
      int i = q.remove();
      for (Integer j : g.outEdges(i)) {
        if (!seen[j]) {
          q.add(j);
          parent[j] = i;
          seen[j]   = true;
        }
      }
    }
    return parent;
  }
  
  // NOTE: In Morin's version of the following he keeps 
  // track of the dfsColors of vertices: 
  //    white <=> currently unexplored 
  //    gray  <=> in the current path of exploration
  //    black <=> done exploring
  // These dfsColors of vertices change as the dfs progresses.
  // Instead of dfsColors, we keep track of pre- and post-dfs 
  // numbers for each node.  These numbers tell you at least  
  // as much as the dfsColors, e.g.,
  //    i is white <=> pre[i]  = post[i] = -1.
  //    i is gray  <=> pre[i]>0, post[i] = -1.  
  //    i is black <=> pre[i]>0, post[i]>0.  
  
  /** 
   * DFS of the entire graph
   * @param g graph to be searched
   * @return an array of information on each of the vertices
   */  
  public static VertInfo[] systematicDfs(Graph g) {
    int n           = g.nVertices();
    VertInfo[] info = new VertInfo[n];
    
    for (int i=0; i<n; i++) info[i] = new VertInfo();
    clock = 1; 
    vert1 = vert2 = -1;
    
    for (int vert = 0; vert < n; vert++) 
      // if vert has not yet been visited, do a dfs starting at vert
      if (info[vert].pre == -1) dfs(g, vert, info);
    
    return info;
  }  
  
//  Morin's code includes a version of the following.
//  But, you don't want to use it for this homework 
//  /** 
//   * DFS from a specified starting vertex
//   * @param g graph to be searched
//   * @param s vertex to be searched from
//   * @return an array of information on each of the vertices
//   */
//  public static VertInfo[] dfs(Graph g, int s) {
//    int n           = g.nVertices();
//    VertInfo[] info = new VertInfo[n];
//    for (int i=0; i<n; i++) info[i] = new VertInfo();
//    clock = 1; 
//    // Do a DFS from starting vertex s
//    dfs(g, s, info);
//    return info;
//  }
  
  public static void dfs(Graph g, int i, VertInfo[] info) {
    // pre-visit for i
    info[i].pre = clock;     clock++; 
    for (Integer j : g.outEdges(i)) {
      if (info[j].pre < 0) {      // j has dfsColor "white"
        info[j].parent = i;
        dfs(g, j, info);
      } 
      else if (info[j].post < 0) { // j has dfsColor "gray"
        vert1 = i; vert2 = j;
      }
      else { // j has dfsColor "black"
        // something, maybe
      }
    }
    // post-visit for i
    info[i].post = clock;    clock++;
  }
  

  //////////////////////////////////////////////////////////////////////
  public static void checkPaths(Graph g, 
                                int s,
                                LinkedList<Integer>[] paths, 
                                int... len) {
    int n = g.nVertices();
    
    // Print the paths
    System.out.println("  Claimed shortest paths from start "+s);
    for (int i = 0; i<n; i++) 
      System.out.println("  to "+i+":\t"+paths[i]);
      // Test the paths
    for (int i = 0; i<n; i++) {
      if (len[i]!=paths[i].size()) 
        System.out.println("the path to "+i+" is the wrong length");
      if (paths[i].size()>0) {
        int prior = s;
        ListIterator<Integer> it = paths[i].listIterator(1);
        while (it.hasNext()) {
          int u = it.next();
          if (!g.hasEdge(prior,u)) 
            System.out.println("the path to "+i+" has a non-edge: ("+prior+","+u+")");
          prior = u;
        }
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  public static void checkCycle(Graph g, LinkedList<Integer> cycle) {
    int n = g.nVertices();
    boolean ok = true;
    
    // print the claimed cycle
    if (cycle.size()==0) {
      System.out.println("  No cycle found.");
      return;
    }
    System.out.println("  The claimed cycle is: "+cycle);
    
    if (cycle.peekFirst()!=cycle.peekLast()) {
      System.out.println("!!! The start and end of the cycle do not match.");
      ok = false;
    }
    
    int prior = cycle.peekFirst();
    ListIterator<Integer> it = cycle.listIterator(1);
    while (it.hasNext()) {
      int u = it.next();
      if (!g.hasEdge(prior,u)) {
        System.out.println("the cycle has a non-edge: ("+prior+","+u+")");
        ok = false;
      }
      prior = u;
    }
    if (ok) System.out.println("  The cycle checks out.");
  }
  
  //////////////////////////////////////////////////////////////////////
  public static void checkTopSort(Graph g, LinkedList<Integer> sort) {
    int n = g.nVertices();
    boolean ok = true;
   
    System.out.println("  The claimed topological sort is: "+sort);
    
    if (sort.size()!=n) {
      System.out.println("!!! The topological sort is missing vertices.");
      ok = false;
    }
    for (Integer j : sort) 
      if (j<0 || j >= n) { 
        System.out.println("!!! The topological sort includes strange vertices, e.g.: "+j);
        return;
      }
    
    ListIterator<Integer> it = sort.listIterator(0);
    int[] ord = new int[n];
    int m = 0;
    while (it.hasNext()) {
      int v = it.next();
      ord[v] = m; // vertex v is the m-th element of the top. sort
      m++;
    }
    
    for (int i=0; i<n; i++) {
      for (Integer j : g.outEdges(i)) 
        if (ord[i]>=ord[j]) {
          System.out.println("!!! ("+i+","+j+") is an edge, but "
                               +j+" comes before "+i+" in the topological sort");
          ok = false;
        }
    }
    if (ok) System.out.println("  The topological sort checks out.");
  }
  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  //  Homework problems
  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  
  //////////////////////////////////////////////////////////////////////
  /** Tests if there is a path from vertex s to vertex t in the graph g
    * @param g the graph
    * @param s the start vertex
    * @param t the target vertex
    * @return true iff there is a path from s to t in g.
    */
  public static boolean isReachable(Graph g,int s,int t) {
    // setup for a DFS
    int n = g.nVertices();
    VertInfo[] info = new VertInfo[n];
    for (int i=0; i<n; i++) info[i] = new VertInfo();
    
    // Do a DFS from s in g.
    dfs(g, s, info);  
    // After the DFS info[t].pre != -1 iff the DFS from s reached t
    return (info[t].pre != -1);
  }
  
  //////////////////////////////////////////////////////////////////////
  /** Tests if the vertex s is a source of the graph g.
    * @param g the graph
    * @param s the vertex
    * @return true if it is a source of the graph.
    */
  public static boolean isSource(Graph g,int s) {
    if (g.inDegree(s)!=0){
      return false;
    }
    int x = g.nVertices();
    VertInfo[] info = new VertInfo[x];
    for(int i = 0; i<x; i++){
      info[i] = new VertInfo();
    }
    dfs(g,s,info);
    for(int i = 0; i<x; i++){
      if(!isReachable(g,s,i)){
        return false;
      }
    }
    return true; // fixed
  }
  
  
  //////////////////////////////////////////////////////////////////////
  /** Return an array of a shortest paths from s in graph g.
    * @param g the graph
    * @param s the integer
    * @return ans, which is the array.
    */
  @SuppressWarnings("unchecked")
  public static LinkedList<Integer>[] paths(Graph g, int s) {
    LinkedList<Integer>[] ans 
      = (LinkedList<Integer>[])new LinkedList[g.nVertices()];
    for(int i=0; i<ans.length; i++) 
      ans[i] = new LinkedList<Integer>();   
    int x;
    int y = g.nVertices();
    int[] bfsList;
    bfsList = bfs(g,s);
    for(int i = 0; i<y; ++i){
      x = bfsList[i];
      ans[i].addFirst(i);
      if(i != s && x == -1){
        ans[i] = new LinkedList<Integer>();
      }
      while(x != -1){
        ans[i].addFirst(x);
        x = bfsList[x];
      }
    }
    return ans; //fixed
  }
  
  //////////////////////////////////////////////////////////////////////
  /** Return a cycle in graph g, if there is an cycle to be found. 
    * If the graph is acyclic, an empty list returned.
    * @param g the graph
    * @return ans, which is the list.
    */
  public static LinkedList<Integer> findCycle(Graph g) {
    LinkedList<Integer> ans = new LinkedList<Integer>();
    VertInfo[] info = systematicDfs(g);
    if((vert1!= -1) && (vert2!= -1)){
      ans.addFirst(vert2);
      while(vert2 != vert1){
        ans.addFirst(vert1);
        vert1 = info[vert1].parent;
      }
      ans.addFirst(vert2);
    }
    return ans; //fixed
  }
  
  //////////////////////////////////////////////////////////////////////
  /** Returns a list consisting of a topological sort of the graph. 
    * If the graph is acyclic, and returns an empty list if the graph is cyclic.
    * @param g the graph
    * @return ans, which is the list.
    */
  public static LinkedList<Integer> topSort(Graph g) {
    int x = g.nVertices();
    LinkedList<Integer> ans = new LinkedList<Integer>();
    
    LinkedList<Integer> cycle = findCycle(g);
    if(cycle.size() != 0){
      return ans;
    }
    ArrayList<Integer> a = new ArrayList<Integer>();
    for(int i = 0; i<x; i++){
      a.add(i); //put the graph into the list
    }
    while(a.size()!= 0){
      for(int i=0; i<a.size(); i++){
        if(g.inDegree(a.get(i)) == 0){
          ans.add(a.get(i));
          for(int n = 0; n<x; n++){
            g.removeEdge(a.get(i),n);
          }
          a.remove(i);
        }
      }
    }
    return ans;
  }
  //////////////////////////////////////////////////////////////////////  
  public static void main(String[] argv) {
    VertInfo[] info;
    int[] par;
    
    // Construct some graphs
    
    // g0 is the graph of page 16 in the slides, except
    // that node 9 in the slides is node 0 here.
    AdjacencyLists g0 = new AdjacencyLists(9);
    g0.addEdge(1,2);    g0.addEdge(1,6);     
    g0.addEdge(2,3);    g0.addEdge(2,4);    g0.addEdge(2,8);
    g0.addEdge(3,4);    g0.addEdge(3,8);    
    g0.addEdge(4,5);    g0.addEdge(4,6);
    g0.addEdge(5,3);    g0.addEdge(5,6);  
    g0.addEdge(7,6);  
    g0.addEdge(8,7);    g0.addEdge(8,0);  
    g0.addEdge(0,1); 
    g0.gvPrint("g0.gv");
    
    info = systematicDfs(g0);
    System.out.println("Vert\tPre\tPost\tParent");
    for (int i=0; i<g0.nVertices(); i++) 
      System.out.println(i+"\t"+info[i].pre+"\t"+info[i].post+"\t"+info[i].parent);
    
    // g1 is g0 with the edges (0,1) and (5,3) removed so that it has no cycles
    AdjacencyLists g1 = (AdjacencyLists) g0.clone();
    g1.removeEdge(0,1); g1.removeEdge(5,3);  
    // g1.gvPrint("g1.gv");
    
    // g2 is graph pictured in the homework 12 writeup
    AdjacencyLists g2 = new AdjacencyLists(14);
    g2.addEdge(0,4);    g2.addEdge(0,5);    g2.addEdge(0,11);
    g2.addEdge(1,2);    g2.addEdge(1,4);    g2.addEdge(1,8);
    g2.addEdge(2,5);    g2.addEdge(2,6);    g2.addEdge(2,9);
    g2.addEdge(3,2);    g2.addEdge(3,6);    g2.addEdge(3,13);
    g2.addEdge(4,7);
    g2.addEdge(5,8);    g2.addEdge(5,12);  
    g2.addEdge(6,5);  
    g2.addEdge(8,7);  
    g2.addEdge(9,10);   g2.addEdge(9,11);  
    g2.addEdge(10,13);  
    g2.addEdge(12,9);  
    g2.addEdge(13,1);
    // g2.gvPrint("g2.gv");
    
    // g3 is g2 with edge (13,1) removed so that it has no cycles  
    AdjacencyLists g3 = (AdjacencyLists) g2.clone();
    g3.removeEdge(13,1);
    // g3.gvPrint("g3.gv");
    
    AdjacencyLists g4 = new AdjacencyLists(4);
    g4.addEdge(0,2); g4.addEdge(0,3); 
    g4.addEdge(1,2); g4.addEdge(1,3);
    
    
    ////////////////////////////////////////////////////////////////////
    System.out.println("*** isSource tests ***");   

    // in g1, 1 is the only source
    for (int v=0; v<g1.nVertices(); v++) {
      boolean result = isSource(g1,v);
      System.out.print("  isSource(g1,"+v+") = " + result+"\t");
      if (result==(v!=1)) 
        System.out.println("WRONG");
      else 
        System.out.println("Check");      
    }
    
    // Beginning of November 29 addition ///////////////////////////////
    AdjacencyLists g5 = new AdjacencyLists(4);     
    g5.addEdge(0,2); g5.addEdge(0,3);      
    g5.addEdge(1,2); g5.addEdge(1,3);
    
    for (int v=0; v<g5.nVertices(); v++) {
      boolean result = isSource(g5,v);
      System.out.print("  isSource(g5,"+v+") = " + result+"\t"
                         + (result?"WRONG":"Check"));
    }
    // End of November 29 addition /////////////////////////////////////
      
      
    
    
    ////////////////////////////////////////////////////////////////////
    System.out.println("\n\n*** Shortest paths tests ***");
    LinkedList<Integer>[] paths;
    
    System.out.println("  For graph g0");
    paths = paths(g0,1);   
    checkPaths(g0,1,paths,4,1,2,3,3,4,2,4,3);                         
        
    System.out.println("\n  For graph g1");
    paths = paths(g1,2);  
    checkPaths(g1,2,paths,3,0,1,2,2,3,3,3,2);                         
    
    System.out.println("\n  For graph g2");
    paths = paths(g2,0);   
    checkPaths(g2,0,paths,1,7,8,0,2,2,9,3,3,4,5,2,3,6);  
    
    System.out.println("\n  For graph g3");
    paths = paths(g3,1);   
    checkPaths(g3,1,paths,0,1,2,0,2,3,3,3,2,3,4,4,4,5);  
    
    
    ////////////////////////////////////////////////////////////////////
    System.out.println("\n\n*** Cycle finding tests ***");   
    LinkedList<Integer> cycle;
    
    System.out.println("  For graph g0");
    cycle = findCycle(g0);  
    checkCycle(g0,cycle);                         
        
    System.out.println("\n  For graph g1");
    cycle = findCycle(g1);  
    if (cycle.size()==0)
      System.out.println("  No cycle found, which is correct for this graph");
    else 
      checkCycle(g1,cycle);                        
        
    System.out.println("\n  For graph g2");
    cycle = findCycle(g2);  
    checkCycle(g2,cycle);
    
    System.out.println("\n  For graph g3");
    cycle = findCycle(g3);  
        if (cycle.size()==0)
      System.out.println("  No cycle found, which is correct for this graph");
    else 
      checkCycle(g3,cycle);  
    

    ////////////////////////////////////////////////////////////////////
    System.out.println("\n\n*** Topological sort tests ***");    
    LinkedList<Integer> sort;
    
    System.out.println("\n  For graph g1");
    sort = topSort(g1);  
    checkTopSort(g1,sort);      
    
    
    System.out.println("\n  For graph g3");
    sort = topSort(g3);  
    checkTopSort(g3,sort);  
    
  }
}