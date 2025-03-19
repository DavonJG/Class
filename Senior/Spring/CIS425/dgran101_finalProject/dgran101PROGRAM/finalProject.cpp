/******************************************
*
* Official Name:  Davon Grant
*
* Nickname:  N/A
*
* E-mail:  dgran101@syr.edu
*
* Assignment:  Final Project
*
* Environment/Compiler:  Visual Studio 2017
*
* Date:  April 27, 2019
*
* References:  Computer Graphics Through OpenGL by Sumanta Guha and lecture notes
   RotatingHelix3.cpp was the starting point of this program, so there are many
   similar methods. Other references include ballAndTorus.cpp, and glutObjects.cpp,
   as well as past homeworks. This includes every homework besides the last one, and when a
   specific homework is referenced, it is said in the method header comment.
*
* Interactions:
Press 'Space' to begin
Press 'esc' to quit
Press 'r' to reset the scene
Press 's' to switch between day and night
Press 'c' to get rid of dialogue on screen
Press 'i' to make the bobber red & blue
Press 'o' to make the bobber orange & blue
Press 'p' to make the bobber black & yellow
Press 'b' to make the friend compliment the fisherman
Press 'n' to make the friend insult the fisherman
Press 'm' to make the friend say a joke
Press 'k' to make the fish start swimming back and forth
Press 'v' to make the fish swim in a position to be caught on the next passaround.

Right click the window to display submenu's:
	Left click Time of Day > Morning to change to daytime
	Left click Time of Day > Night to change to daytime
	Left click Friend Speech > Compliment to make friend say a compliment
	Left click Friend Speech > Antagonize to make friend be rude
	Left click Bobber Color > Red and White to make the bobber appear red and white
	Left click Bobber Color > Blue and Orange to make the bobber appear blue and orange
	Left click Bobber Color > Black and Yellow to make the bobber appear black and yellow
	Left click "Catch a Fish!" to make the fish swim in a position to be caught on the next passaround.
	Left click Quit to exit program
*
*******************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

// Globals.

static int sunOut = 1; //default view is with the sun out.
static int titleScreen = 1; //used to display titleScreen
static int friendLine = 0; //used for the friend speaking
static int bobberColorChoice = 7;
static int fishermanSmile = 0; //used for the fisherman smiling 
static int rightSide = 1; //what side of the screen the fish is on 

//used to draw the bobber on the rod
static float bobberPT1x = -12;
static float bobberPT1y = -28;
static float bobberPT1z = -5;
static float bobberPT2x = -12;
static float bobberPT2y = -28.5;
static float bobberPT2z = -5;

//used to draw the hook on the rod
static float rodHookPT1x = -12;
static float rodHookPT1y = -29.5;
static float rodHookPT1z = -5;

static float rodHookPT2x = -12; 
static float rodHookPT2y = -32.5; 
static float rodHookPT2z = -7;

static float rodHookPT3x = -12;
static float rodHookPT3y = -31.5;
static float rodHookPT3z = -7.2;

//used to draw the string on the rod
static float stringAngle = 120;
static float stringLength = 35;

static float fishX = 9;
static float fishY = -6;
static float fishZ = -7;
static int fishSent = 0;
static float fishAngle = 0;
static int prepGetCaught = 0; // if enabled, make the fish hit the hook on the next go around
static int fishCaught = 0; //fish is in the proper position
GLUquadricObj *p = gluNewQuadric();




//taken from lecture (class 5)
void displayText(void *font, const char *string)  //mjb I made this const
{
	const char *c;  //mjb I made this const

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

//used in menu system 
void quit(int id)
{
	if (id == 1) {
		exit(0);
	}
}

//used in menu system 
void timeOfDay(int id) {
	if (id == 2) {
		sunOut = 1;
	}

	if (id == 3) {
		sunOut = 0;
	}


	glutPostRedisplay();
}

//used in menu system 
void friendSpeak(int id) {
	if (id == 4) {
		friendLine = 4;
	}

	if (id == 5) {
		friendLine = 5;
	}

	if (id == 6) {
		friendLine = 6;
	}
}

//used in menu system
void bobberColor(int id) {
	if (id == 7) {
		bobberColorChoice = 7;
	}

	if (id == 8) {
		bobberColorChoice = 8;
	}

	if (id == 9) {
		bobberColorChoice = 9;
	}
}

//used in menu system
void setCatchAFish(int id) {
	if (id == 10) {
		prepGetCaught = 1;
	}
}


//draw a text box that comes out of the friend's mouth
void drawFriendTextBox(){
	glLineWidth(1.0);

	//draw rectangle
	glColor3f(1, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-11, 0.5, -25); //Vertex values were obtained
	glVertex3f(-18, 0.5, -25); //through extensive testing.
	glVertex3f(-18, 4.5, -25);
	glVertex3f(-11, 4.5, -25);
	glEnd();

	//draw triangle pointing from friend
	glColor3f(1, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-14, 0.5, -25); //Vertex values were obtained
	glVertex3f(-12, 0.5, -25); //through extensive testing.
	glVertex3f(-12.5, -0.5, -25);
	glEnd();

	//draw outline
	glColor3f(0, 0, 0); //rgb for white
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex3f(-11, 4.5, -25);
	glVertex3f(-18, 4.5, -25);
	glVertex3f(-18, 4.5, -25);
	glVertex3f(-18, 0.5, -25);
	glVertex3f(-18, 0.5, -25);
	glVertex3f(-14, 0.5, -25);
	glVertex3f(-14, 0.5, -25);
	glVertex3f(-12.5, -0.5, -25);
	glVertex3f(-12.5, -0.5, -25);
	glVertex3f(-12, 0.5, -25);
	glVertex3f(-12, 0.5, -25);
	glVertex3f(-11, 0.5, -25);
	glVertex3f(-11, 0.5, -25);
	glVertex3f(-11, 4.5, -25);
	glEnd();

}

//Draw a text box and a statement based on what friendLine is set to
void drawFriendSpeech(){
	if (friendLine == 4) { // compliment
		drawFriendTextBox();
		glColor3f(0, 0, 0);
		glRasterPos3f(-15.5, 2, -24);
		displayText(GLUT_BITMAP_HELVETICA_12, "Nice job!");
	}
	if (friendLine == 5) { //antagonize
		drawFriendTextBox();
		glColor3f(0, 0, 0);
		glRasterPos3f(-15.5, 2, -24);
		displayText(GLUT_BITMAP_HELVETICA_12, "You stink!");
	}
	if (friendLine == 6) { //joke
		drawFriendTextBox();
		glColor3f(0, 0, 0);
		glRasterPos3f(-16, 3, -24);
		displayText(GLUT_BITMAP_HELVETICA_12, "Smells FISHY");
		glRasterPos3f(-16, 2, -24);
		displayText(GLUT_BITMAP_HELVETICA_12, "out here!");
	}
	glutPostRedisplay();
}


//create the right click menu, based on my menu from hw2
void makeMenu(void) {
	int sub_menu;
	sub_menu = glutCreateMenu(timeOfDay);
	glutAddMenuEntry("Morning", 2);
	glutAddMenuEntry("Night", 3);

	int sub_menu2;
	sub_menu2 = glutCreateMenu(friendSpeak);
	glutAddMenuEntry("Compliment", 4);
	glutAddMenuEntry("Antagonize", 5);
	glutAddMenuEntry("Joke", 6);

	int sub_menu3;
	sub_menu3 = glutCreateMenu(bobberColor);
	glutAddMenuEntry("Red and White", 7);
	glutAddMenuEntry("Blue and Orange", 8);
	glutAddMenuEntry("Black and Yellow", 9);

	glutCreateMenu(quit);
	glutCreateMenu(setCatchAFish);
	glutAddSubMenu("Time of Day", sub_menu);
	glutAddSubMenu("Friend Speech", sub_menu2);
	glutAddSubMenu("Bobber Color", sub_menu3);
	glutAddMenuEntry("Catch a Fish!", 10);
	glutAddMenuEntry("Quit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//draws a fish using glut spheres.
void drawFish() {
	
	//draw the body
	glColor3f(0.972549, 0.2, 0.0);
	glPushMatrix();
	glTranslatef(-1, -3, -3.5);
	glScalef(3, 1, 0.3);
	glutSolidSphere(4, 100, 100);
	glPopMatrix();

	//draw the tail
	glColor3f(0.972549, 0.2, 0.0);
	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	glTranslatef(6, -8, -3.5);
	glScalef(1, 0.3, 0.3);
	glutSolidSphere(4, 100, 100);
	glPopMatrix();

	glColor3f(0.972549, 0.2, 0.0);
	glPushMatrix();
	glRotatef(-45, 0, 0, 1);
	glTranslatef(10, 5, -3.5);
	glScalef(1, 0.3, 0.3);
	glutSolidSphere(4, 100, 100);
	glPopMatrix();

	//draw the eyes
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(-5, -1, -2);
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(-5, -1, -5);
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();
}


//draw the fisherman's friend.
void drawHuman() {
	//draw his head
	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(0, 2, -5);
	glutSolidSphere(4, 100, 100);
	glPopMatrix();

	//draw his ears
	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(4, 3, -5);
	glScalef(0.5, 1.0, 1.0);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(-4, 3, -5);
	glScalef(0.5, 1.0, 1.0);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	//draw the eyes
	//outer circle
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-1.4, 2.7, -2);
	glutSolidSphere(1.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 2.7, -2);
	glutSolidSphere(1.2, 100, 100);
	glPopMatrix();

	//inner circle
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(-1.4, 2.7, -1);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 2.7, -1);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

	//draw his nose
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0, 1.8, -2);
	glutSolidSphere(1.1, 100, 100);
	glPopMatrix();

	//mouth 
	if (friendLine == 0) { //if hes not speaking, draw with mouth closed
		glColor3f(0, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0.3, -1.8);
		glScalef(1.5, 0.3, 0.5);
		glutSolidSphere(1.1, 100, 100);
		glPopMatrix();
	}
	else { //otherwise, draw with mouth open
		glColor3f(0, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0.3, -1.8);
		glScalef(2.0, 1.1, 0.5);
		glutSolidSphere(1.1, 100, 100);
		glPopMatrix();
	}
	//draw his body
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0, -8, -5);
	glScalef(0.7, 1, 1);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();



	//draw his arms
	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(6, -5, -5);
	glRotatef(45, 0, 0, 1);
	glScalef(0.3, 0.7, 0.5);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -5, -5);
	glRotatef(315, 0, 0, 1);
	glScalef(0.3, 0.7, 0.5);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();

	//draw his legs
	glColor3f(0, 0, 1);

	glPushMatrix();
	glTranslatef(-3, -16, -5);
	glScalef(0.2, 0.7, 0.4);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, -16, -5);
	glScalef(0.2, 0.7, 0.4);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();
}

//draw the fisherman. this is heavily based on the drawHuman() method,
//with the only difference being the shirt color.
void drawFisherman() {
	//draw his head
	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(0, 2, -5);
	glutSolidSphere(4, 100, 100);
	glPopMatrix();

	//draw his ears
	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(4, 3, -5);
	glScalef(0.5, 1.0, 1.0);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(-4, 3, -5);
	glScalef(0.5, 1.0, 1.0);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	//draw the eyes
	//outer circle
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-1.4, 2.7, -2);
	glutSolidSphere(1.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 2.7, -2);
	glutSolidSphere(1.2, 100, 100);
	glPopMatrix();

	//inner circle
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(-1.4, 2.7, -1);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, 2.7, -1);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

	//draw his nose
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0, 1.8, -2);
	glutSolidSphere(1.1, 100, 100);
	glPopMatrix();

	//draw his mouth
	if (fishermanSmile == 0) { //if hes not smiling, draw with mouth closed
		glColor3f(0, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0.3, -1.8);
		glScalef(1.5, 0.3, 0.5);
		glutSolidSphere(1.1, 100, 100);
		glPopMatrix();
	}
	else { //otherwise, draw with mouth open
		glColor3f(0, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0.3, -1.8);
		glScalef(2.0, 1.1, 0.5);
		glutSolidSphere(1.1, 100, 100);
		glPopMatrix();
	}

	//draw his body
	glColor3f(0.49411764, 0.580392, 0.4588235);
	glPushMatrix();
	glTranslatef(0, -8, -5);
	glScalef(0.7, 1, 1);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();



	//Arms
	glColor3f(1.000, 0.627, 0.478);
	glPushMatrix();
	glTranslatef(4, -5, -2);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.3, 0.7, 0.5);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, -5, -2);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.3, 0.7, 0.5);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();

	//Legs
	glColor3f(0, 0, 1);

	glPushMatrix();
	glTranslatef(-3, -16, -5);
	glScalef(0.2, 0.7, 0.4);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, -16, -5);
	glScalef(0.2, 0.7, 0.4);
	glutSolidSphere(6, 100, 100);
	glPopMatrix();
}

//for drawRod, I knew that I wanted to use a gluQuadricObject because
//at the very least, a cylinder had to be included.
void drawRod() {

	//draw the rod portion
	glColor3f(0.607843, 0.831372, 0.396078);
	glPushMatrix();
	glTranslatef(0, -9, 14.5);
	glRotatef(-120, 1.0, 0.0, 0.0);
	gluCylinder(p, 1, 1, 20, 100, 100);
	glPopMatrix();

	//draw handle
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0, -13, 16.4);
	glRotatef(-120, 1.0, 0.0, 0.0);
	gluCylinder(p, 1.5, 1.5, 5, 100, 100);
	glPopMatrix();

	//draw the string
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0, 8, 5);
	//glRotatef(120, 1.0, 0.0, 0.0); original string
	glRotatef(stringAngle, 1.0, 0.0, 0.0);
	//gluCylinder(p, 0.1, 0.1, 35, 100, 100); original string 
	gluCylinder(p, 0.1, 0.1, stringLength, 100, 100);
	glPopMatrix();

	//draw the bobber
	if (bobberColorChoice == 7) {
		glColor3f(1, 1, 1);
	}
	if (bobberColorChoice == 8) {
		glColor3f(0.988235, 0.4392156, 0.058823);
	}
	if (bobberColorChoice == 9) {
		glColor3f(0, 0, 0);
	}
	glPushMatrix(); 
	//glTranslatef(-12, -28, -5); part 1 of bobber
	glTranslatef(bobberPT1x, bobberPT1y, bobberPT1z);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

	if (bobberColorChoice == 7) {
		glColor3f(1, 0, 0);
	}
	if (bobberColorChoice == 8) {
		glColor3f(0, 0, 1);
	}
	if (bobberColorChoice == 9) {
		glColor3f(0.9960784, 0.776470, 0.223529);
	}
	glPushMatrix();
	//glTranslatef(-12, -28.5, -5); part 2 of bobber
	glTranslatef(bobberPT2x, bobberPT2y, bobberPT2z);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

	//draw the hook
	glColor3f(0.412, 0.412, 0.412);
	glPushMatrix();
	//glTranslatef(-12, -29.5, -5); original pt 1 
	glTranslatef(rodHookPT1x, rodHookPT1y, rodHookPT1z);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(p, 0.2, 0.2, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(-12, -32.5, -7); original pt 2
	glTranslatef(rodHookPT2x, rodHookPT2y, rodHookPT2z); 
	gluCylinder(p, 0.2, 0.2, 2, 100, 100);
	glPopMatrix();
	
	glPushMatrix();
	//glTranslatef(-12, -31.5, -7.2);
	glTranslatef(rodHookPT3x, rodHookPT3y, rodHookPT3z); 
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(p, 0.2, 0.2, 1, 100, 100);
	glPopMatrix();

}
//draw the title screen
void drawTitleScreen(void) {

	//draw the blue background
	glBegin(GL_QUADS);
	glColor3f(0.031372, 0.1843137, 0.9686274);
	glVertex3f(-100.0, -100.0, -11);
	glVertex3f(100.0, -100.0, -11);
	glColor3f(0, 0, 0); //mixed in black to make it darker
	glVertex3f(100.0, 100.0, -11);
	glVertex3f(-100.0, 100.0, -11);
	glEnd();

	//display text
	glColor3f(1, 1, 1);
	glRasterPos3f(-3.5, 3, -10);
	displayText(GLUT_BITMAP_HELVETICA_18, "FISHING WITH THE FELLAS!");

	glColor3f(1, 1, 1);
	glRasterPos3f(-3.0, -3, -10);
	displayText(GLUT_BITMAP_HELVETICA_12, "Press Spacebar to begin");

	glColor3f(1, 1, 1);
	glRasterPos3f(-3.0, -4.5, -10);
	displayText(GLUT_BITMAP_HELVETICA_12, "Press Esc to quit");
}

//draw the cube used to represent sea
void drawSea(float x, float y, float z) {
	glColor3f(0.117647, 0.35686, 0.431372);
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(5.0, 2.0, 1.0);
	glutSolidCube(40);
	glPopMatrix();
}

//draw the sun or the moon, based on the sunOut variable
void drawSunOrMoon(float x, float y, float z) {
	if (sunOut == 1) { //if it is morning, display the sun
		glColor3f(0.972549, 0.741176, 0.29803);
		glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidCone(15.0, 3.0, 100, 100);
		glPopMatrix();
	}
	else { //otherwise, display the moon
		glColor3f(0.843137, 0.854901, 0.862745098);
		glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidCone(15.0, 3.0, 100, 100);
		glPopMatrix();
	}
}

//draw a cube that represents the sky. the cube was needed
//because using glClearColor did not reflect the changes in light.
void drawSky() {
	glColor3f(0.686, 0.933, 0.933);
	glPushMatrix();
	glScalef(0, 0, 0.3);
	glTranslatef(0, 0, 300);
	glutSolidCube(300);
	glPopMatrix();
}

//draw a boat (supposed to represent a canoe)
void drawBoat(float x, float y, float z) {
	//draw outer boat
	glColor3f(0.41960784, 0.0196078, 0.0509803);
	glPushMatrix();
	glScalef(2.0, 0.2, 1.0);
	glTranslatef(x, y, z);
	glutSolidSphere(3.0, 100, 100);
	glPopMatrix();
	//draw inner seats
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(2.0, 0.0, 1.0, 0.0);
	glScalef(1.0, 0.1, 1.0);
	glTranslatef(x - 1.5, y - 19, z + 1);
	glutSolidSphere(3.0, 100, 100);
	glPopMatrix();
}

//draw a geyser that is supposed to shoot bubbles. INCOMPLETE + NOT USED
void drawGeyser() {
	glColor3f(0.611764, 0.545, 0.341);
	glPushMatrix();
	glTranslatef(5, -6, -7);
	glRotatef(225.0, 1.0, 0.0, 0.0);
	glutSolidCone(3.5, 2.5, 1000, 1000);
	glPopMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(20.9, -23.5, -28.0);
	glScalef(2, 1, 1);
	glutSolidSphere(0.5, 2.5, 1000);
	glPopMatrix();
}

//Lazy attempt at seaweed
void drawSeaweed(float x, float y, float z) {

	//draw rectangle
	glColor3f(0.17254, 0.584313, 0.211764);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);

	glVertex3f(x, y, z); //Vertex values were obtained
	glVertex3f(x-2, y, z); //through extensive testing.
	glVertex3f(x-2, y+27, z);
	glVertex3f(x, y + 27, z);
	glEnd();
}

//function used to adjust the fish as well as the fishing rod
//as the fish is being caught.
void raiseFish() {
	if (rightSide == 1) { //If it is coming from the right, change the angle.
		if (fishAngle > -48) {
			fishAngle -= 5;
			glutPostRedisplay();
		}
	}
	if ((fishAngle <= -48) && fishY < -2) {
		fishY += 0.2;
		bobberPT1x += 0.6;
		bobberPT1y += 1.35;
		bobberPT2x += 0.6;
		bobberPT2y += 1.35;
		stringAngle += 0.5;
		stringLength -= 1.05;
		rodHookPT1x += 0.6;
		rodHookPT1y += 1.35;
		rodHookPT2x += 0.6;
		rodHookPT2y += 1.35;
		rodHookPT3x += 0.6;
		rodHookPT3y += 1.35;
		glutPostRedisplay();
	}

	if (rightSide == 0) {
		if (fishAngle < 55) {
			fishAngle += 5;
			glutPostRedisplay();
		}
	}

	if ((fishAngle >= 55)  && fishY < -2) {
		fishY += 0.2;
		bobberPT1x += 0.6;
		bobberPT1y += 1.35;
		bobberPT2x += 0.6;
		bobberPT2y += 1.35;
		stringAngle += 0.5;
		stringLength -= 1.05;
		rodHookPT1x += 0.6;
		rodHookPT1y += 1.35;
		rodHookPT2x += 0.6;
		rodHookPT2y += 1.35;
		rodHookPT3x += 0.6;
		rodHookPT3y += 1.35;
		glutPostRedisplay();
	}

	fishermanSmile = 1;
	glutPostRedisplay();
}

//function used to make the fish swim back and forth. Also uses its
//coordinates to determine when it gets caught.
void fishPath() {
	if (rightSide == 1) { //if coming from the right
		if (fishX > -14) {
			if ((fishX == 2.5) && (fishY < -3.8) && (fishY > -4.5) && (fishZ == -7)) {
				fishCaught = 1;
				fishSent = 0;
				return;
			}
			fishX -= 0.5;
		}
		else {
			
			if (prepGetCaught == 1) {
				fishY = -5;
				fishZ = -8;
			}
			rightSide = 0;
		}
	}

	else if (rightSide == 0) { //if coming from the left
		if (fishX <= 14) {
			if (fishX == 1.5 && fishY == -5 && fishZ == -8) {
				fishCaught = 1;
				fishSent = 0;
				return;
			}
			fishX += 0.5;
		}
		else {
			if (prepGetCaught == 1) {
				fishY = -4.4;
				fishZ = -7;
			}
			rightSide = 1;
		}
	}
	

	glutPostRedisplay();
}


//Timer function used to make the fish move after
//it is sent on its path
void sendFish(int x) {
	if (fishSent)
		fishPath();
	glutTimerFunc(110, sendFish, 1);
}

//Timer function used to make the fish raise after
//it is on the hook.
void catchFish(int x) {
	if (fishCaught)
		raiseFish();
	glutTimerFunc(110, catchFish, 1);
}




//drawImage is used in order to draw everything that needs to be drawn,
//rather than doing it all in drawScene.
void drawImage(void) {

	float lightAmb[] = { 0.4, 0.4, 0.4, 0.4 };
	float lightAmb2[] = { 0.0, 0.1, 0.1, 0.1 };

	if (sunOut == 0) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb2);
	}
	else {
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	}

	//draw the grassiuo
	if (titleScreen == 1) {
		drawTitleScreen();
	}
	else {
		drawSky();
		drawSunOrMoon(75, 75, -99.0);
		drawSea(0.0, -47.0, -35.0);
		drawBoat(-2.3, -23.0, -15.0);

		//draw the bystander
		glPushMatrix();
		glRotatef(25.0, 0.0, 1.0, 0.0);
		glTranslatef(0.7, -1.3, -15);
		glScalef(0.15, 0.15, 0.15);
		drawHuman();
		glPopMatrix();

		//draw the fishermen
		glPushMatrix();
		glRotatef(45.0, 0.0, 1.0, 0.0);
		glTranslatef(7.0, -0.7, -9);
		glScalef(0.15, 0.15, 0.15);
		drawFisherman();
		glPopMatrix();

		//draw the fishing rod
		glPushMatrix();
	
		glTranslatef(1, 0, -8);
		glRotatef(220.0, 0.0, 1.0, 0.0);
		glScalef(0.15, 0.15, 0.15);
		glRotatef(10.0, 0.0, 0.0, 1.0);
		drawRod();
		glPopMatrix();

		//draw the fish - z value has to be between -11 and -7
		
		glPushMatrix();
		glTranslatef(fishX, fishY, fishZ);
		glScalef(0.1, 0.1, 0.1);
		if (rightSide == 0) {
			glRotatef(180.0, 0.0, 1.0, 0.0);
		}
		glRotatef(fishAngle, 0.0, 1.0, 0.0);
		drawFish();
		glPopMatrix();
		
		//draw the seaweed
		glPushMatrix();
		glTranslatef(5, -6, -7);
		glScalef(0.1, 0.1, 0.1);
		drawSeaweed(-11, -37.5, -25);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5, -6, -7);
		glScalef(0.1, 0.1, 0.1);
		drawSeaweed(20, -17.5, -5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5, -6, -7);
		glScalef(0.1, 0.1, 0.1);
		drawSeaweed(-50, -17.5, -5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5, -6, -7);
		glScalef(0.1, 0.1, 0.1);
		drawSeaweed(-111, -37.5, -25);
		glPopMatrix();

		drawFriendSpeech(); //draw the friend's text if necessary
	}
}


// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawImage();
	glutSwapBuffers();
}



// Initialization routines. Light taken from sphereInBox1.cpp
void setup(void)
{
	
	//light properties and materials are borrowed from lecture notes.
	
	// Material property vectors.
	float matSpec[] = { 0.0, 5.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };
	float matAmbAndDif[] = { 0.0, 0.1, 1.0, 1.0 };


	// Light property vectors.
	float lightDifAndSpec[] = { 0.0, 0.1, 1.0, 1.0 };
	float lightPos[] = { 0.0, 10.0, -20.0, .50 };
	float globAmb[] = { 0.8, 0.8, 0.8, 1.0 };


	// Material properties of the objects.
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmbAndDif);

	// Light0 properties.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	// Poperties of the ambient light.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);


	glEnable(GL_LIGHTING); // Enable lighting calculations.
	glEnable(GL_LIGHT0); // Enable particular light source.
	glEnable(GL_DEPTH_TEST); // Enable depth testing.

	glEnable(GL_NORMALIZE); // Enable automatic normalization of normals.
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.686, 0.933, 0.933, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 5, 100);
	glMatrixMode(GL_MODELVIEW);
}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 's':
		if (sunOut == 0)
			sunOut = 1;
		else
			sunOut = 0;
		glutPostRedisplay();
		break;

	//get rid of dialogue
	case 'c':
		friendLine = 0;
		glutPostRedisplay();
		break;

	//move past title screen
	case ' ':
		if (titleScreen == 1) {
			titleScreen = 0;
		}
		glutPostRedisplay();
		break;

	//make the fish start swimming
	case 'k':
		fishSent = 1;
		glutPostRedisplay();
		break;

	//bobber colors
	case 'i':
		bobberColorChoice = 7;
		glutPostRedisplay();
		break;
	case 'o':
		bobberColorChoice = 8;
		glutPostRedisplay();
		break;
	case 'p':
		bobberColorChoice = 9;
		glutPostRedisplay();
		break;

	//friend comments
	case 'b':
		friendLine = 4;
		glutPostRedisplay();
		break;
	case 'n':
		friendLine = 5;
		glutPostRedisplay();
		break;
	case 'm':
		friendLine = 6;
		glutPostRedisplay();
		break;
	case 'v':
		prepGetCaught = 1;
		glutPostRedisplay();
		break;

	case 'r': //reset scene 
		sunOut = 1;
		bobberColorChoice = 7;
		fishSent = 0;
		fishX = 9;
		fishY = -6;
		fishZ = -7;
		titleScreen = 1;
		friendLine = 0;
		fishAngle = 0;
		fishCaught = 0;
		fishSent = 0;
		fishermanSmile = 0; 
		rightSide = 1; 
		prepGetCaught = 0;
		
		bobberPT1x = -12;
		bobberPT1y = -28;
		bobberPT1z = -5;
		bobberPT2x = -12;
		bobberPT2y = -28.5;
		bobberPT2z = -5;

		
		rodHookPT1x = -12;
		rodHookPT1y = -29.5;
		rodHookPT1z = -5;

		rodHookPT2x = -12;
		rodHookPT2y = -32.5;
		rodHookPT2z = -7;

		rodHookPT3x = -12;
		rodHookPT3y = -31.5;
		rodHookPT3z = -7.2;

		
		stringAngle = 120;
		stringLength = 35;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// referenced from rotatingHelix3.cpp
// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Press 'space' to begin" << endl;
	cout << "Press 'esc' to quit" << endl;
	cout << "Press 'r' to reset the scene" << endl;
	cout << "Press 's' to switch between day and night" << endl;
	cout << "Press 'c' to get rid of dialogue on screen" << endl;
	cout << "Press 'i' to make the bobber red & blue" << endl;
	cout <<	"Press 'o' to make the bobber orange & blue" << endl;
	cout <<	"Press 'p' to make the bobber black & yellow" << endl;
	cout <<	"Press 'b' to make the friend compliment the fisherman" << endl;
	cout <<	"Press 'n' to make the friend insult the fisherman" << endl;
	cout <<	"Press 'm' to make the friend say a joke" << endl;
	cout <<	"Press 'k' to make the fish start swimming back and forth" << endl;
	cout <<	"Press 'v' to make the fish swim in a position to be caught on the next passaround." << endl;
	cout << "" << endl;
	cout <<	"Right click the window to display submenu's:" << endl;
	cout <<	"Left click Time of Day > Morning to change to daytime" << endl;
	cout <<	"Left click Time of Day > Night to change to daytime" << endl;
	cout <<	"Left click Friend Speech > Compliment to make friend say a compliment" << endl;
	cout <<	"Left click Friend Speech > Antagonize to make friend be rude" << endl;
	cout <<	"Left click Bobber Color > Red and White to make the bobber appear red and white" << endl;
	cout <<	"Left click Bobber Color > Blue and Orange to make the bobber appear blue and orange" << endl;
	cout <<	"Left click Bobber Color > Black and Yellow to make the bobber appear black and yellow" << endl;
	cout <<	"Left click Catch a Fish! to make the fish swim in a position to be caught on the next passaround." << endl;
	cout <<	"Left click Quit to exit program" << endl;

}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(850, 850);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Final Project");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	makeMenu();
	glutTimerFunc(5, sendFish, 1);
	glutTimerFunc(5, catchFish, 1);
	glutMainLoop();

	return 0;
}