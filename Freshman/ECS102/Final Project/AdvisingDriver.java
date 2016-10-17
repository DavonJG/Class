import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Random;

/*  Advising Suite
AdvisingDriver.java
Davon Grant
dgran101
Section 4*/
public class AdvisingDriver{
  static ArrayList<Student> allStudents = new ArrayList<Student>(); //used for sotring students throughout the program. (AR)
  //main method
  public static void main(String[]args)throws IOException{
    int selection;
    Scanner scan = new Scanner(System.in);
    printMenu();
    selection = scan.nextInt();
    //display a menu and continue displaying it during the program while selection isn't 0 or 7, which closes the program.
    while(selection!=0){
      checkSelection(selection);
      printMenu();
      selection = scan.nextInt();
    }
  }
  
  //----------------------------------------------------
  //printMenu() (MYMETH)
  //menu method which is repeated throughout the program.
  //----------------------------------------------------
  public static void printMenu(){
    System.out.println("Hello! Welcome to Advising Suite.\nPlease select an option:\n1. Create a new student\n2. Edit an existing student\n3. Display a student\n4. Display student rankings\n5. Student giveaway\n6. Display class list\n7. Quit\n\n8. Import student file\n9. Export student file.");
  }
  //----------------------------------------------------
  //checkSelection(int selection)  (MYMETH) - invokes rest of methods in AdvisingDriver
  //Used to check what the user chose in the main method. Based on 
  //the choice number, the checkSelection method calls other methods
  //in the program using a switch function.
  //----------------------------------------------------
  public static void checkSelection(int selection)throws IOException{
    switch(selection){
      case 1:
        createStudent();
        break;
      case 2:
        editStudent();
        break;
      case 3:
        displayStudent();
        break;
      case 4:
        displayRankings();
        break;
      case 5:
        studentGiveaway();
        break;
      case 6:
        displayClassList();
        break;
      case 7:
        System.exit(1);
        break;
      case 8:
        studentImport();
        break;
      case 9:
        studentExport();
        break;
      default:
        System.out.println("Please select a valid option!");
        break;
    }
    return;
  }
  
  //----------------------------------------------------
  //displayClassList()
  //Grabs the classes from all of the students and displays them in a list.
  //----------------------------------------------------
  public static void displayClassList(){
    if(allStudents.size()<=0){
      System.out.println("There are no students to grab classes from! Please import or add students.");
    }
    else{
      //Create a long string of all classes, split them, and print the splitted array of strings.
      String unformattedClassList = ""; 
      for(int count=0;count<allStudents.size()-1;count++){
        unformattedClassList+=((allStudents.get(count)).getClasses());
      }
      String[] classList = unformattedClassList.split(",");
      System.out.println("Classes displayed below.");
      for(int count=0;count<classList.length;count++){
        System.out.println(classList[count]);
      }
    }
  }
  //----------------------------------------------------
  //studentExport() (I/O) (MYMETH) - invokes get methods
  //method that allows the user to export all of the students currently in
  //the allStudents arrayList.
  //----------------------------------------------------
  public static void studentExport()throws IOException{
    Scanner scan = new Scanner(System.in);
    String fileName;
    if(allStudents.size()<=0){ //dont export a file if there are no students
      System.out.println("There are no students to export yet! Please import or create students.");
      System.out.println("Returning to main menu...");
    }
    else{
      System.out.println("What would you like the file name to be?");
      fileName = scan.nextLine();
      PrintWriter outputFile = new PrintWriter(fileName+".txt");
      for(int i=0;i<allStudents.size();i++){ //loop through the array and export each student
        outputFile.println((allStudents.get(i)).getFirstName());
        outputFile.println((allStudents.get(i)).getLastName());
        outputFile.println((allStudents.get(i)).getMajor());
        outputFile.println((allStudents.get(i)).getGPA());
        outputFile.println((allStudents.get(i)).getClasses());
      }
      outputFile.close();
      System.out.println("File exported! Returning to main menu...");
    }
  }
  //----------------------------------------------------
  //displayStudent() (MYMETH) - invokes studentSearch
  //method that allows the user to view a student's data. Uses the
  //studentSearch method to check if the student exists beforehand.
  //----------------------------------------------------
  public static void displayStudent(){
    Scanner scan = new Scanner(System.in);
    String tryAgain ="";
    String displayAgain="";
    String studentName;
    int x;
    if(allStudents.size()<=0){
      System.out.println("There are no students to display. Please create a student or import students.");
      System.out.println("Returning to main menu...");
    }
    else{
      do{
        do{
          tryAgain="N";
          System.out.println("What student would you like to display? (First Last)");
          studentName = scan.nextLine();
          x = studentSearch(allStudents, studentName); //call studentSearch to find the student
          if(x<0){
            System.out.println("Student does not exist! Would you like to try again? (Y/N)");
            tryAgain = scan.nextLine();
          }
        }while(tryAgain.compareToIgnoreCase("Y")==0);
        if(x>=0){
          System.out.println(allStudents.get(x));
          System.out.println("Would you like to print another student? (Y/N)");
          displayAgain = scan.nextLine();
        }
      }while(displayAgain.compareToIgnoreCase("Y")==0);
    }
  }

        
  //----------------------------------------------------
  //studentSearch(ArrayList<Student> allStudents, String targetName)  (SEARCH)
  //search method which is called throughout the rest of the program. Uses the array of
  //students and the target name as parameters to perform a linear search.
  //----------------------------------------------------
  public static int studentSearch(ArrayList<Student> allStudents, String targetName){
    int i=0;
    boolean foundStudent = false; // (BOOL)
    while(!foundStudent&&i<allStudents.size()){
      if(((allStudents.get(i)).getName()).compareToIgnoreCase(targetName)==0){
        foundStudent=true;
      }
      else{
        i++;
      }
    }
    if(foundStudent){
      return i;
    }
    else{
      return -1;
    }
  }
    
  //----------------------------------------------------
  //editStudent() (MYMETH) - invokes studentSearch() + more
  //method used to edit student data. Also calls studentSearch() to find
  //the student that the user wants to edit.
  //----------------------------------------------------  
  public static void editStudent(){
    //declare instance data and get user inputs
    if(allStudents.size()<=0){
      System.out.println("There are no students to edit! Returning to main menu...");
    }
    if(allStudents.size()>0){
      Scanner scan = new Scanner(System.in);
      String selection = "N";
      String repeatEdit = "Y";
      String classesRemoved, classesAdded, newMajor, firstN,lastN, name;
      double newGPA =0.0;
      int index;
      do{
        selection="N";
        System.out.println("Editing student data. Please enter the student's first name.");
        firstN = scan.nextLine();
        System.out.println("What is "+firstN+"'s last name?");
        lastN=scan.nextLine();
        name = firstN+" "+lastN;
        index = studentSearch(allStudents, name); //call the search method to find the student the user wants to edit.
        if(index<0){
          System.out.println("Student not found! Would you like to try again? (Y/N)");
          selection=scan.nextLine();
        }
      }while(selection.compareToIgnoreCase("Y")==0);
      if(index>=0){
        System.out.println("Student found! Data is displayed below.");
        System.out.println(allStudents.get(index));
        do{
          System.out.println("What would you like to edit? (Classes/GPA/Major)");
          selection = scan.nextLine();
          //-----------
          //If the user selects classes, let them edit the classes.
          //------------
          if(selection.compareToIgnoreCase("Classes")==0){
            System.out.println("What classes would you like to remove? Leave blank if you do not want to remove any classes. (Separate by commas)");
            classesRemoved = scan.nextLine();
            (allStudents.get(index)).removeClass(classesRemoved);
            System.out.println(classesRemoved+ " has/have been removed. What classes would you like to add? Leave blank if you do not want to add any classes.");
            classesAdded = scan.nextLine();
            (allStudents.get(index)).addClasses(classesAdded);
            System.out.println("Updated student is displayed below:");
            System.out.println(allStudents.get(index));
            System.out.println("Would you like to make more changes? (Y/N)");
            repeatEdit = scan.nextLine();
          }
          //-----------
          //If the user selects GPA, let them edit the GPA.
          //------------
          else if(selection.compareToIgnoreCase("GPA")==0){
            System.out.println("What is "+firstN+"'s new GPA?");
            newGPA=scan.nextDouble();
            (allStudents.get(index)).setGPA(newGPA);
            System.out.println("Updated student is displayed below:");
            System.out.println(allStudents.get(index));
            System.out.println("Would you like to make more changes? (Y/N)");
            scan.nextLine();
            repeatEdit = scan.nextLine();
          }
          //-----------
          //If the user selects major, let them edit the major.
          //------------
          else if(selection.compareToIgnoreCase("Major")==0){
            System.out.println("What is "+firstN+"'s new major?");
            newMajor = scan.nextLine();
            (allStudents.get(index)).setMajor(newMajor);
            System.out.println("Updated student is displayed below:");
            System.out.println(allStudents.get(index));
            System.out.println("Would you like to make more changes? (Y/N)");
            repeatEdit = scan.nextLine();
          }
          //-----------
          //Input validation.
          //------------
          else{
            System.out.println("Please enter a valid choice.");
          }
        }while(repeatEdit.compareToIgnoreCase("Y")==0);
      }
    }
  }
    
  //----------------------------------------------------
  //studentImport() (I/O)
  //method used to import files that have student data. Stores them into the
  //allStudents array so the data can be used in the rest of the program.
  //----------------------------------------------------
  public static void studentImport()throws IOException{
    Scanner scan = new Scanner(System.in);
    File studentFile = null; //initialize
    String userFilename = "";//initialize
    String selection="";
    do{
      selection="N";
      System.out.println("What is the name of the file you would like to import? (Do not include .txt)");
      userFilename = scan.nextLine();
      studentFile = new File(userFilename+".txt");    
      if(!(studentFile.exists())){
        System.out.println("File not found. Make sure the file is in the same directory as the program. Would you like to try again? (Y/N)");
        selection = scan.nextLine();
      } 
    }while(selection.compareToIgnoreCase("Y")==0);
    if(studentFile.exists()){
      Scanner studentFileScan = new Scanner(new File(userFilename+".txt"));
      for(int i=0;studentFileScan.hasNextLine();i++){ //loop through the file and store all of the data
        String studentFirstName = studentFileScan.nextLine();
        String studentLastName = studentFileScan.nextLine();
        String studentMajor = studentFileScan.nextLine();
        double studentGPA = studentFileScan.nextDouble();
        studentFileScan.nextLine();
        String studentClasses = studentFileScan.nextLine();
        Student student = new Student(studentMajor, studentFirstName, studentLastName, studentClasses, studentGPA);
        allStudents.add(i,student);
      }
      System.out.println("Student(s) successfully imported!");
    }
  }
  //----------------------------------------------------
  //displayRankings() (MYMETH) - invokes studentSort()
  //method used to display the rankings of all of the students
  //that are in the allStudents array. It allows the user to choose what they
  //want to sort by, and also alerts the user if there are no students to rank.
  //Calls studentSort() method.
  //----------------------------------------------------
  public static void displayRankings(){ 
    Scanner scan = new Scanner(System.in);
    if(allStudents.size()<=0){
      System.out.println("There are no students to rank! Please try again after importing or creating students."); //alerts the user if there are no students to rank.
    }
    else{
      System.out.println("Would you like to display the rankings by last name, first name or GPA?");
      String selection = scan.nextLine();
      System.out.println("--------------------------------------------------------------"); //print out first line
      //-----------
      //sort array by first name
      //------------
      if(selection.equalsIgnoreCase("First name")){
        studentSort(allStudents, "First name");
        System.out.println("First Name\t\t\tLast Name\t\tGPA");
        for(int i=0; i<allStudents.size(); i++){
          String studentFirstName = (allStudents.get(i)).getFirstName();
          String studentLastName = (allStudents.get(i)).getLastName();
          double studentGPA = (allStudents.get(i)).getGPA();
          System.out.printf("%.10s\t\t\t%.10s\t\t%.3f", studentFirstName,studentLastName,studentGPA);
          System.out.println();
        }
      }
      //-----------
      //sort array by last name
      //------------
      else if(selection.equalsIgnoreCase("Last Name")){
        studentSort(allStudents, "Last Name");//sort array by last name
        System.out.println("Last Name:\t\t\tFirst Name:\t\tGPA:");
        for(int i=0; i<allStudents.size(); i++){
          String studentFirstName = (allStudents.get(i)).getFirstName();
          String studentLastName = (allStudents.get(i)).getLastName();
          double studentGPA = (allStudents.get(i)).getGPA();
          System.out.printf("%.10s\t\t\t%.10s\t\t\t%.3f", studentLastName,studentFirstName,studentGPA);
          System.out.println();
        }
      }
      //-----------
      //sort array by GPA
      //------------
      else if(selection.equalsIgnoreCase("GPA")){
        studentSort(allStudents, "GPA");
        System.out.println("GPA\t\t\tFirst Name\t\tLast Name");
        for(int i=allStudents.size()-1; i>=0; i--){
          String studentFirstName = (allStudents.get(i)).getFirstName();
          String studentLastName = (allStudents.get(i)).getLastName();
          double studentGPA = (allStudents.get(i)).getGPA();
          System.out.printf("%.3f\t\t\t%.10s\t\t%.10s", studentGPA,studentFirstName,studentLastName);
          System.out.println();
        }
      }
      System.out.println("--------------------------------------------------------------");
    }
  }
  
  //----------------------------------------------------
  //createStudent() (MYMETH) - invokes get methods + more
  //method used to create students using information which the program
  //asks from the user. It then displays that student using Student's toString()
  //method, and stores the student into the allStudents array if the user confirm he wants
  //to create the student.
  //----------------------------------------------------
  public static void createStudent(){ 
    Scanner scan = new Scanner(System.in);
    //get all the needed information
    System.out.println("What is the student's first name?");
    String studentFirstName = scan.nextLine();
    System.out.println("What is the student's last name?");
    String studentLastName = scan.nextLine();
    System.out.println("What is the student's major?");
    String studentMajor = scan.nextLine();
    System.out.println("What is the student's GPA?");
    double studentGPA = scan.nextDouble();
    scan.nextLine();
    System.out.println("Please enter the classes the student will take, seperated by commas.");
    String studentClasses = scan.nextLine();
    Student student = new Student(studentMajor, studentFirstName, studentLastName, studentClasses, studentGPA);
    System.out.println("The current student’s information is printed below. Please review all alerts before confirming the student creation!");
    System.out.println(student);
    System.out.println("Create student? 1= yes, 2= no, see above for more options");
    int userInput;
    //--------------------
    //user confirmation.
    //--------------------
    do{
      userInput = scan.nextInt();
      if(userInput ==1){
        allStudents.add(student);
        System.out.println("Student created!");
        System.out.println("Returning to main menu...");
      }
      else if(userInput==2){ //Do not store the student into the array if the user doesn't want to create the student.
        System.out.println("Student creation cancelled!\nReturning to main menu...");
      }
      else{
        System.out.println("Please enter a valid option.");
      }
    }while((userInput>3)||(userInput<1));
  }
  
  //----------------------------------------------------
  //studentGiveaway()
  //method used to create randomly generate the winner of a giveaway.
  //----------------------------------------------------
  public static void studentGiveaway(){ //(MYMETH) (RANDOM)
    if(allStudents.size()>0){ //check if there are students first before doing the giveaway.
      Random gen = new Random();
      int arrayLength = allStudents.size();
      int randomIndex = gen.nextInt(arrayLength); 
      Student winner = allStudents.get(randomIndex);
      String winnerName = winner.getName();
      System.out.println("The winner of the giveaway is...\n"+winnerName+"\n Congratulations!");
    }
    else{ //Do not allow a giveaay if there aren't any students yet.
      System.out.println("There are no students yet! Please try again after creating or importing students.");
      System.out.println("Returning to main menu...");
    }
  }
  
  //----------------------------------------------------
  //studentSort() (SORT)(MYMETH) - invokes get methods + more
  //accepts the arraylist generated at the beginning of the beginning, as this is what will be sorted.
  //also accepts the selection string which is provided through user input.
  //
  //studentSort uses the selection parameter to sor
  //----------------------------------------------------
  public static void studentSort(ArrayList<Student> studentList, String selection){ 
    Integer first;
    Student temp;
    if(selection.equalsIgnoreCase("Last Name")){
      for (int i=0; i<studentList.size()-1; i++){
        first = i;
        for (int x=i+1; x<studentList.size(); x++)
          if (((studentList.get(x)).getLastName()).compareTo((studentList.get(first)).getLastName())<0)
             first = x; 
        //swap
        temp = studentList.get(first);
        studentList.set(first, studentList.get(i));
        studentList.set(i, temp);
      }
    }
    else if(selection.equalsIgnoreCase("First Name")){
      for (int i=0; i<studentList.size()-1; i++){
        first = i;
        for (int x=i+1; x<studentList.size(); x++)
          if (((studentList.get(x)).getFirstName()).compareTo((studentList.get(first)).getFirstName())<0)
             first = x; 
        //swap
        temp = studentList.get(first);
        studentList.set(first, studentList.get(i));
        studentList.set(i, temp);
      }
    }
    else if(selection.equalsIgnoreCase("GPA")){
      for (int i=0; i<studentList.size()-1; i++){
        first = i;
        for (int x=i+1; x<studentList.size(); x++)
          if (((studentList.get(x)).getGPA())<((studentList.get(first)).getGPA()))
             first = x; 
        //swap
        temp = studentList.get(first);
        studentList.set(first, studentList.get(i));
        studentList.set(i, temp);
      }
    }
    else{
      System.out.println("Please select a valid option!");
    }
  }
}