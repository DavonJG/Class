/*  Advising Suite
Student.java
Davon Grant
dgran101
Section 4*/

public class Student{ //(CL)
  double gpa;
  String major, firstName, lastName, name, classes, requiredClasses;
  //----------------------------------------------------
  //student()
  //Default constructor
  //----------------------------------------------------
  public Student(){
    major = "";
    firstName="";
    lastName="";
    name = firstName+" "+lastName;
    classes = "";
    gpa = 0.0;
  }
  //----------------------------------------------------
  //student()
  //Overloaded constructor which accepts values and stores them
  //into Student's instance variables.
  //----------------------------------------------------
  public Student(String m, String firstN, String lastN, String c, double g){
    major = m;
    firstName = firstN;
    lastName= lastN;
    name=firstN+" "+lastN;
    classes = c;
    gpa = g;
  }
  /***************************************************************************************
    *                              GET & SET METHODS
    * ***********************************************************************************/
  public void setMajor(String m){
    major = m;
  }
  public String getMajor(){
    return major;
  }
  public void setName(String firstN, String lastN){
    firstName = firstN;
    lastName = lastN;
    name = firstN+" "+lastN;
  }
  public String getName(){
    return name;
  }
  public String getFirstName(){
    return firstName;
  }
  public String getLastName(){
    return lastName;
  }
  public void setClasses(String c){
    classes = c;
  }
  public String getClasses(){
    return classes;
  }
  public double getGPA(){
    return gpa;
  }
  public void setGPA(double g){
    gpa = g;
  }
  

    /***************************************************************************************
    *                              END OF GET & SET METHODS
    * ***********************************************************************************/
  //----------------------------------------------------
  //addClasses(String c)
  //add the argument given to the end of the classes string.
  //----------------------------------------------------
  public void addClasses(String c){
    classes+= ", "+c;
  }
  //----------------------------------------------------
  //removeClasses(String c)
  //remove the argument given from classes string.
  //----------------------------------------------------
  public void removeClass(String c){
    classes = classes.replaceAll(c, "");
  }
  
  //----------------------------------------------------
  //toString
  //Neatly displays student data.
  //----------------------------------------------------
  public String toString(){
    String classes = this.getClasses();
    String[] classList = classes.split(","); //Split the classes so they can be printed neatly
    String x = ("--------------------------------------------------\n" //format the student data
              + "Name:"+this.getName()+"\n"
              + "Major:"+this.getMajor()+"\n"
              + "GPA:"+this.getGPA()+"\n"
              + "\n"
              + "Classes:\n ");
    for(int count=0;count<classList.length;count++){
      x+=classList[count].toString();
      x+="\n";
    }
    x+=("--------------------------------------------------");
    return x;
  }
  
  
}