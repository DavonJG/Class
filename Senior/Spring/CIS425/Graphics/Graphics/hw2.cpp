/******************************************
*
* Official Name:  Davon Grant
*
* Nickname:  N/A
*
* E-mail:  dgran101@syr.edu
*
* Assignment:  Homework 2
*
* Environment/Compiler:  Visual Studio 2017
*
* Date:  February 18, 2019
*
* References:  Computer Graphics Through OpenGL by Sumanta Guha and lecture notes
			   windowsWKeyboardOptions.cpp was the starting point of this program, so there are many 
			   similar methods.
*
* Interactions:   Press the escape key to quit.
				  Click the Pasta radio button to see it filled and see it displayed.
                  Press a to fill the Pasta radio button and see it displayed.
				  Click the Burger radio button to see it filled and see it displayed.
				  Press s to fill the Burger radio button and see it displayed.
				  Click the Pizza radio button to see it filled and see it displayed.
				  Press d to fill the Pizza radio button and see it displayed.
				  Click the Sushi radio button to see it filled and see it displayed.
				  Press f to fill the Sushi radio button and see it displayed.
				  Click the Apple checkbox to see it filled and see it displayed.
				  Press z to fill the Apple checkbox and see it displayed.
				  Click the Carrot checkbox to see it filled and see it displayed.
				  Press x to fill the Carrot checkbox and see it displayed.
				  Click the Wasabi checkbox to see it filled and see it displayed.
				  Press c to fill the Wasabi checkbox and see it displayed.
				  Click the Fries checkbox to see it filled and see it displayed.
				  Press v to fill the Fries checkbox and see it displayed.
				  Click the Brocolli checkbox to see it filled and see it displayed.
				  Press b to fill the Brocolli checkbox and see it displayed.
				  Right click the Display Panel to display submenu's
					Left click Change Plate Color > Silver to make the plate silver
					Left click Change Plate Color > Purple to make the plate purple
					Left click Change Plate Color > Silver to make the plate blue
					Left click Rotate Plate > 90 to rotate the plate 90 degrees.
					Left click Entree Portion > Double to make the portion size bigger
					Left click Entree Portion > Half to make the portion size smaller
					Left click Entree Portion > Original to make the portion size reset back to normal
					Left click Quit to exit the program.

*
*******************************************/

#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

// Globals.
static int id1, id2; // Window identifiers.
//default silver plate
static double plateColorR = 0.8274509;
static double plateColorG = 0.8274509;
static double plateColorB = 0.8274509;

static int entreeChoice = 0; //used to determine entree on screen

//globals for sides
static int sideApple = 0;
static int sideCarrot = 0;
static int sideWasabi = 0;
static int sideFries = 0;
static int sideBrocolli = 0;
static int rotate90 = 0;

/******************************************
plateColor()

read the id given by the submenu in order to change
the global variables used to draw the plate.
*******************************************/
void plateColor(int id) {
	if (id == 2) { //silver
		plateColorR = 0.8274509;
		plateColorG = 0.8274509;
		plateColorB = 0.8274509;
		glutSetWindow(id1);
	}

	if (id == 3) { // purple
		plateColorR = 0.57647;
		plateColorG = 0.439215;
		plateColorB = 0.858823;
		glutSetWindow(id1);
	}

	if (id == 4) { // blue
		plateColorR = 0.678431;
		plateColorG = 0.847058;
		plateColorB = 0.901960;
		glutSetWindow(id1);
	}

	glutPostRedisplay();
}

/******************************************
entreeSize() - INCOMPLETE

read the id given by the submenu in order to change
the size of the entree.
*******************************************/
void entreeSize(int id) {
	if (id == 6) {
		glScalef(2.0, 2.0, 0.0);
		glutPostRedisplay();
	}
	if (id == 7) {
		glScalef(0.5, 0.5, 0.0);
		glutPostRedisplay();
	}
	if (id == 8) {
		glScalef(1.0, 1.0, 0.0);
		glutPostRedisplay();
	}
}

/******************************************
plateRotation() - INCOMPLETE

read the id given by the submenu in order to change
the angle of the plate.
*******************************************/
void plateRotation(int id) {
	if (id == 5) {
		rotate90++;
		glRotatef((rotate90 * 90), 180, 0, 0);
		glutPostRedisplay();
	}
}

/******************************************
quit()

read the id given by the submenu in order to
exit the program
*******************************************/
void quit(int id)
{
	if (id == 1) {
		exit(0);
	}
}

/******************************************
makeMenu()

Create the submenu used in the display panel.
*******************************************/
void makeMenu(void){
	//plateColor menu
	int sub_menu;
	sub_menu = glutCreateMenu(plateColor);
		glutAddMenuEntry("Silver", 2);
		glutAddMenuEntry("Purple", 3);
		glutAddMenuEntry("Blue", 4);
	
	//rotation menu
	int sub_menu2;
	sub_menu2 = glutCreateMenu(plateRotation);
		glutAddMenuEntry("90°", 5);

	//Portion size menu
	int sub_menu3;
	sub_menu3 = glutCreateMenu(plateRotation);
	glutAddMenuEntry("Double", 6);
	glutAddMenuEntry("Half", 7);
	glutAddMenuEntry("Original", 8);

	glutCreateMenu(quit);
	glutAddSubMenu("Change Plate Color", sub_menu);
	glutAddSubMenu("Rotate Plate", sub_menu2);
	glutAddSubMenu("Entree Portion", sub_menu3);
	glutAddMenuEntry("Quit", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/******************************************
writeBitmapString()

Writes a string of text using bitmap imaging.
Taken from lecture.
*******************************************/
void writeBitmapString(void *font, const char *string)  //mjb I made this const
{
	const char *c;  //mjb I made this const

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

/******************************************
drawWasabi()

draw a scoop of wasabi.
*******************************************/
void drawWasabi() {
	glColor3f(0.349019, 0.64705, 0.137254); //wasabi green

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((3 * cos(25 * PI*i / 999.0)) + 3, (1 * sin(25 * PI*i / 999.0)) -12, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2.5 * cos(25 * PI*i / 999.0)) + 3, (1 * sin(25 * PI*i / 999.0)) - 11, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(25 * PI*i / 999.0)) + 3, (1 * sin(25 * PI*i / 999.0)) - 10, 0);
	}
	glEnd();
}

/******************************************
drawFries()

draw a carton of french fries.
*******************************************/
void drawFries() {
	glColor3f(0.992156, 0.301960, 0.301960); //red french fry box
	glBegin(GL_POLYGON);
	glVertex3f(3.3, 11, 0);
	glVertex3f(6.9, 11, 0);
	glVertex3f(6.9, 7, 0);
	glVertex3f(3.3, 7, 0);
	glEnd();
	glColor3f(0.95686, 0.77647, 0.243137); //french fry yellow
	glBegin(GL_POLYGON);
	glVertex3f(3.3, 11, 0);
	glVertex3f(3.3, 13, 0);
	glVertex3f(3.9, 13, 0);
	glVertex3f(3.9, 11, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(4.0, 11, 0);
	glVertex3f(4.0, 13.2, 0);
	glVertex3f(4.6, 13.2, 0);
	glVertex3f(4.6, 11, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(4.7, 11, 0);
	glVertex3f(4.7, 13.4, 0);
	glVertex3f(5.3, 13.4, 0);
	glVertex3f(5.3, 11, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(5.4, 11, 0);
	glVertex3f(5.4, 13.2, 0);
	glVertex3f(6.0, 13.2, 0);
	glVertex3f(6.0, 11, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(6.1, 11, 0);
	glVertex3f(6.1, 13, 0);
	glVertex3f(6.7, 13, 0);
	glVertex3f(6.7, 11, 0);
	glEnd();
}

/******************************************
drawBrocolli()

draw a piece of brocolli.
*******************************************/
void drawBrocolli() {
	glColor3f(0.53333, 0.607843, 0.36862); //brocolli stem green
	glBegin(GL_POLYGON);
	glVertex3f(12, -1, 0);
	glVertex3f(13.3, -1, 0);
	glVertex3f(13.3, 3, 0);
	glVertex3f(12, 3, 0);
	glEnd();

	glColor3f(0.3333, 0.419607, 0.18431);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1 * cos(25 * PI*i / 999.0)) + 13, (1 * sin(25 * PI*i / 999.0)) + 3, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1 * cos(25 * PI*i / 999.0)) + 12.5, (1 * sin(25 * PI*i / 999.0)) + 4, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1 * cos(25 * PI*i / 999.0)) + 12, (1 * sin(25 * PI*i / 999.0)) + 3, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1 * cos(25 * PI*i / 999.0)) + 11, (1 * sin(25 * PI*i / 999.0)) + 2, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1 * cos(25 * PI*i / 999.0)) + 12, (1 * sin(25 * PI*i / 999.0)) + 2, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1 * cos(25 * PI*i / 999.0)) + 13, (1 * sin(25 * PI*i / 999.0)) + 2, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1 * cos(25 * PI*i / 999.0)) + 14, (1 * sin(25 * PI*i / 999.0)) + 2, -1);
	}
	glEnd();
}

/******************************************
drawCarrot()

draw a carrot.
*******************************************/
void drawCarrot() {
	glColor3f(0.9294117, 0.64444, 0.1294117); //carrot orange
	glBegin(GL_TRIANGLES);
	glVertex3f(5, -3, 0);
	glVertex3f(10, -3, 0);
	glVertex3f(7.5, -10, 0);
	glEnd();

	//leaves
	glColor3f(0.50980, 0.8313725, 0.207843);
	glBegin(GL_POLYGON);
	glVertex3f(6, -3, 0);
	glVertex3f(5.5, 0, 0);
	glVertex3f(6, 0.5, 0);
	glVertex3f(6.5, 0.5, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(7.5, -3, 0);
	glVertex3f(7, 0, 0);
	glVertex3f(7.5, 0.5, 0);
	glVertex3f(8, 0.5, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(9, -3, 0);
	glVertex3f(8.5, 0, 0);
	glVertex3f(9, 0.5, 0);
	glVertex3f(9.5, 0.5, 0);
	glEnd();

	glFlush();

}

/******************************************
drawSushi()

draw a roll of sushi.
*******************************************/
void drawSushi() {

	//black circles (supposed to represent seaweed)
	glColor3f(0, 0, 0); 

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(25 * PI*i / 999.0)) - 9, (2 * sin(25 * PI*i / 999.0)) + 8, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(25 * PI*i / 999.0)) - 9, (2 * sin(25 * PI*i / 999.0)) + 3, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(25 * PI*i / 999.0)) - 9, (2 * sin(25 * PI*i / 999.0)) - 2, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(25 * PI*i / 999.0)) - 4, (2 * sin(25 * PI*i / 999.0)) + 8, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(25 * PI*i / 999.0)) - 4, (2 * sin(25 * PI*i / 999.0)) + 3, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(25 * PI*i / 999.0)) - 4, (2 * sin(25 * PI*i / 999.0)) - 2, 0);
	}
	glEnd();

	//white circles (supposed to represent rice)
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1.7 * cos(25 * PI*i / 999.0)) - 9, (1.7 * sin(25 * PI*i / 999.0)) + 8, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1.7 * cos(25 * PI*i / 999.0)) - 9, (1.7 * sin(25 * PI*i / 999.0)) + 3, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1.7 * cos(25 * PI*i / 999.0)) - 9, (1.7 * sin(25 * PI*i / 999.0)) - 2, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1.7 * cos(25 * PI*i / 999.0)) - 4, (1.7 * sin(25 * PI*i / 999.0)) + 8, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1.7 * cos(25 * PI*i / 999.0)) - 4, (1.7 * sin(25 * PI*i / 999.0)) + 3, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((1.7 * cos(25 * PI*i / 999.0)) - 4, (1.7 * sin(25 * PI*i / 999.0)) - 2, 0);
	}
	glEnd();

	//draw salmon
	glColor3f(0.9333, 0.45098, 0.30980);

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((0.8 * cos(25 * PI*i / 999.0)) - 9, (0.8 * sin(25 * PI*i / 999.0)) + 8, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((0.8 * cos(25 * PI*i / 999.0)) - 9, (0.8 * sin(25 * PI*i / 999.0)) + 3, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((0.8 * cos(25 * PI*i / 999.0)) - 9, (0.8 * sin(25 * PI*i / 999.0)) - 2, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((0.8 * cos(25 * PI*i / 999.0)) - 4, (0.8 * sin(25 * PI*i / 999.0)) + 8, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((0.8 * cos(25 * PI*i / 999.0)) - 4, (0.8 * sin(25 * PI*i / 999.0)) + 3, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((0.8 * cos(25 * PI*i / 999.0)) - 4, (0.8 * sin(25 * PI*i / 999.0)) - 2, 0);
	}
	glEnd();

}

/******************************************
drawPasta()

draw a piece of lasagna.
*******************************************/
void drawPasta() {
	glColor3f(0.98039, 0.92549, 0.64705); //pasta yellow
	glBegin(GL_POLYGON);
	glVertex3f(-12, 9, 0);
	glVertex3f(-4, 9, 0);
	glVertex3f(-4, 8.2, 0);
	glVertex3f(-12, 8.2, 0);
	glEnd();

	glColor3f(0.81568, 0.04705, 0.039215); //red sauce
	glBegin(GL_POLYGON);
	glVertex3f(-11, 8.2, 0);
	glVertex3f(-5, 8.2, 0);
	glVertex3f(-5, 7.9, 0);
	glVertex3f(-11, 7.9, 0);
	glEnd();

	glColor3f(0.55294, 0.17254, 0.09019); //ground beef
	glBegin(GL_POLYGON);
	glVertex3f(-11, 7.9, 0);
	glVertex3f(-5, 7.9, 0);
	glVertex3f(-5, 7.4, 0);
	glVertex3f(-11, 7.4, 0);
	glEnd();

	//2nd layer
	glColor3f(0.98039, 0.92549, 0.64705); //pasta yellow
	glBegin(GL_POLYGON);
	glVertex3f(-12, 7.4, 0);
	glVertex3f(-4, 7.4, 0);
	glVertex3f(-4, 6.8, 0);
	glVertex3f(-12, 6.8, 0);
	glEnd();

	glColor3f(0.81568, 0.04705, 0.039215); //red sauce
	glBegin(GL_POLYGON);
	glVertex3f(-11, 6.8, 0);
	glVertex3f(-5, 6.8, 0);
	glVertex3f(-5, 6.5, 0);
	glVertex3f(-11, 6.5, 0);
	glEnd();

	glColor3f(0.55294, 0.17254, 0.09019); //ground beef
	glBegin(GL_POLYGON);
	glVertex3f(-11, 6.5, 0);
	glVertex3f(-5, 6.5, 0);
	glVertex3f(-5, 6.0, 0);
	glVertex3f(-11, 6.0, 0);
	glEnd();

	//3rd layer
	glColor3f(0.98039, 0.92549, 0.64705); //pasta yellow
	glBegin(GL_POLYGON);
	glVertex3f(-12, 6.0, 0);
	glVertex3f(-4, 6.0, 0);
	glVertex3f(-4, 5.2, 0);
	glVertex3f(-12, 5.2, 0);
	glEnd();

	glColor3f(0.81568, 0.04705, 0.039215); //red sauce
	glBegin(GL_POLYGON);
	glVertex3f(-11, 5.2, 0);
	glVertex3f(-5, 5.2, 0);
	glVertex3f(-5, 4.9, 0);
	glVertex3f(-11, 4.9, 0);
	glEnd();

	glColor3f(0.55294, 0.17254, 0.09019); //ground beef
	glBegin(GL_POLYGON);
	glVertex3f(-11, 4.9, 0);
	glVertex3f(-5, 4.9, 0);
	glVertex3f(-5, 4.4, 0);
	glVertex3f(-11, 4.4, 0);
	glEnd();

	glColor3f(0.98039, 0.92549, 0.64705); //pasta yellow
	glBegin(GL_POLYGON);
	glVertex3f(-12, 4.4, 0);
	glVertex3f(-4, 4.4, 0);
	glVertex3f(-4, 3.8, 0);
	glVertex3f(-12, 3.8, 0);
	glEnd();
}
/******************************************
drawApple()

draw an apple.
*******************************************/
void drawApple() { //draw apple
	glColor3f(0.6431372, 0, 0); //apple red
	glPushMatrix();
	glRotatef(100, 90, 0, 0);
	glTranslatef(4, -15, 0);
	glutWireSphere(2.0, 20.0, 20.0);
	glPopMatrix();

	//draw stem
	glColor3f(0.4, 0.2, 0.0); // RGB Values for brown
	glBegin(GL_POLYGON);
	glVertex3f(3.8, 4, -1.0);
	glVertex3f(5.5, 6, -1.0);
	glVertex3f(5.5, 5.5, -1.0);
	glVertex3f(3.8, 3.5, -1.0);
	glEnd();
}

/******************************************
drawBurger()

draw a cheeseburger.
*******************************************/
void drawBurger() { 
	int i, j;
	int h = 4;
	int v = 6;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (j = 0; j < h; j++)
	{
		//top bun
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= v; i++)
		{ 
			glVertex3f(5 * cos((float)(j + 1) / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) - 8,
				5 * sin((float)(j + 1) / h * PI / 2.0) + 4,
				5 * cos((float)(j + 1) / h * PI / 2.0) * sin(2.0 * (float)i / v * PI));
			glColor3f(0.82352, 0.70588, 0.549019);
			glVertex3f(5 * cos((float)j / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) - 8,
				5 * sin((float)j / h * PI / 2.0) + 4,
				5 * cos((float)j / h * PI / 2.0) * sin(2.0 * (float)i / v * PI));
		}
		glEnd();
		//bottom bun
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= v; i++)
		{
			glVertex3f(5 * cos((float)(j + 1) / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) -8,
				-1 * 3 * sin((float)(j + 1) / h * PI / 2.0) + 0.5,
				5 * cos((float)(j + 1) / h * PI / 2.0) * sin(2.0 * (float)i / v * PI));
			glVertex3f(5 * cos((float)j / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) -8,
				-1 * 3 * sin((float)j / h * PI / 2.0) + 0.5,
				5 * cos((float)j / h * PI / 2.0) * sin(2.0 * (float)i / v * PI));
		}
		glEnd();
	}

	//draw lettuce
	glColor3f(0.25490, 0.921568, 0.55686); // RGB Values for lettuce green
	glBegin(GL_POLYGON);
	glVertex3f(-12, 4, 0.0);
	glVertex3f(-4, 4, 0.0);
	glVertex3f(-4, 3.5, 0.0);
	glVertex3f(-12, 3.5, 0.0);
	glEnd();

	//draw tomatoes
	glColor3f(1, 0.388235, 0.278431); // RGB Values for tomato red
	glBegin(GL_POLYGON);
	glVertex3f(-12, 3.5, 0.0);
	glVertex3f(-4, 3.5, 0.0);
	glVertex3f(-4, 3, 0.0);
	glVertex3f(-12, 3, 0.0);
	glEnd();

	//draw cheese
	glColor3f(1, 0.90980, 0.63137); // RGB Values for cheese yelloe
	glBegin(GL_POLYGON);
	glVertex3f(-12, 3, 0.0);
	glVertex3f(-4, 3, 0.0);
	glVertex3f(-4, 2.5, 0.0);
	glVertex3f(-12, 2.5, 0.0);
	glEnd();

	//draw meat
	glColor3f(0.32941, 0.1764705, 0.1764705); // RGB Values for meat color
	glBegin(GL_POLYGON);
	glVertex3f(-12, 2.5, 0.0);
	glVertex3f(-4, 2.5, 0.0);
	glVertex3f(-4, 1.5, 0.0);
	glVertex3f(-12, 1.5, 0.0);
	glEnd();

	//draw more cheese
	glColor3f(1, 0.90980, 0.63137); // RGB Values for cheese yelloe
	glBegin(GL_POLYGON);
	glVertex3f(-12, 1.5, 0.0);
	glVertex3f(-4, 1.5, 0.0);
	glVertex3f(-4, 1, 0.0);
	glVertex3f(-12, 1, 0.0);
	glEnd();

	//draw more meat
	glColor3f(0.32941, 0.1764705, 0.1764705); // RGB Values for meat color
	glBegin(GL_POLYGON);
	glVertex3f(-12, 1, 0.0);
	glVertex3f(-4, 1, 0.0);
	glVertex3f(-4, 0, 0.0);
	glVertex3f(-12, 0, 0.0);
	glEnd();


}

/******************************************
drawPizza()

draw a slice of pizza
*******************************************/
void drawPizza() { 

	//draw crust
	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	glBegin(GL_TRIANGLES);
	glVertex3f(-10, 10, -1);
	glVertex3f(0, 10, -1);
	glVertex3f(-5, -10, -1);
	glEnd();
	glFlush();

	//draw tomato sauce
	glColor3f(0.768627, 0.10196, 0.10196); // RGB Values for red variation
	glBegin(GL_TRIANGLES);
	glVertex3f(-9, 8, -2);
	glVertex3f(-1, 8, -2);
	glVertex3f(-5, -9, -2);
	glEnd();
	glFlush();

	//draw cheese
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_TRIANGLES);
	glVertex3f(-8.5, 7, -3);
	glVertex3f(-1.5, 7, -3);
	glVertex3f(-5, -8, -3);
	glEnd();
	glFlush();

	//draw pepperoni 

	glColor3f(0.8313725, 0.30588, 0.164705); //RGB Values for pepperoni color

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((cos(25 * PI*i / 999.0)) - 7, (sin(25 * PI*i / 999.0)) + 5, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((cos(25 * PI*i / 999.0)) - 3.5, (sin(25 * PI*i / 999.0)) + 5.5, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((cos(25 * PI*i / 999.0)) - 4.8, (sin(25 * PI*i / 999.0)) + 3, 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((cos(25 * PI*i / 999.0)) - 5.5, (sin(25 * PI*i / 999.0)), 0);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((cos(25 * PI*i / 999.0)) - 5, (sin(25 * PI*i / 999.0)) - 3, 0);
	}
	glEnd();



	glFlush();
}

/******************************************
fillPastaButton()

fill the radio button next to pasta
*******************************************/
void fillPastaButton() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0); // RGB Values for black
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) + 7.55, -1);
	}
	glEnd();
}

/******************************************
fillBurgerButton()

fill the radio button next to burger
*******************************************/
void fillBurgerButton() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0); // RGB Values for tan
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) + 4.55, -1);
	}
	glEnd();
}

/******************************************
fillPizzaButton()

fill the radio button next to pizza
*******************************************/
void fillPizzaButton() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0); // RGB Values for tan
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) + 1.55, -1);
	}
	glEnd();
}

/******************************************
fillSushiButton()

fill the radio button next to sushi
*******************************************/
void fillSushiButton() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0); // RGB Values for tan
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) - 1.55, -1);
	}
	glEnd();
}

/******************************************
drawCheckmark(int x, int y, int z)

draw a checkmark depending on the given location
*******************************************/
void drawCheckmark(int x, int y, int z) {
	glColor3f(1.0, 1.0, 1.0); //rgb for white
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y - 1, z);
	glVertex3f(x + 1, y - 1, z);
	glVertex3f(x + 2, y + 1, z);
	glEnd();
}

/******************************************
entreeSelection(int choice)

either deselect a radio button or fill it using the entreeChoice
global variable. 
*******************************************/
void entreeSelection(int choice) {
	if (entreeChoice == choice) {
		entreeChoice = 0;
	}
	else {
		entreeChoice = choice;
	}
}

/******************************************
drawScene1()

Drawing routine for first window.
*******************************************/
void drawScene1(void)
{
	// Choose window.
	glutSetWindow(id1);

	glClear(GL_COLOR_BUFFER_BIT);



	glColor3f(plateColorR, plateColorG, plateColorB);
	glBegin(GL_POLYGON); //draw the plate
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((17 * cos(25 * PI*i / 999.0)) + 0, (17 * sin(25 * PI*i / 999.0)) + 0, 0); 
	}
	glEnd();

	if (entreeChoice == 1) {
		drawPasta();
	}

	if (entreeChoice == 2) {
		drawBurger();
	}

	if (entreeChoice == 3) {
		drawPizza();
	}

	if (entreeChoice == 4) {
		drawSushi(); 
	}
	
	if (sideApple) {
		drawApple();
	}

	if (sideCarrot) {
		drawCarrot();
	}

	if (sideWasabi) {
		drawWasabi();
	}

	if (sideFries) {
		drawFries();
	}

	if (sideBrocolli) {
		drawBrocolli();
	}

	
	glFlush();
}

/******************************************
drawScene2()

Drawing routine for second window.
*******************************************/
void drawScene2(void)
{
	// Choose window.
	glClear(GL_COLOR_BUFFER_BIT);

	glutSetWindow(id2);
	

	//Draw Menu header
	glRasterPos3f(-17, 18, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "*******************************************");
	glRasterPos3f(-2.5, 15, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "MENU"); 
	glRasterPos3f(-17, 12, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "*******************************************"); 

	//Display the main courses
	glRasterPos3f(-17, 10, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "ENTREES:"); 
	glRasterPos3f(-10, 7, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Pasta"); 
	glRasterPos3f(-10, 4, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Burger"); 
	glRasterPos3f(-10, 1, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Pizza"); 
	glRasterPos3f(-10, -2, 0); 
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sushi"); 

	//Display the side courses
	glRasterPos3f(-17, -5, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "SIDES:"); 
	glRasterPos3f(-10, -8, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Apple");
	glRasterPos3f(-10, -11, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Carrot");
	glRasterPos3f(-10, -14, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Wasabi");
	glRasterPos3f(7, -8, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Fries");
	glRasterPos3f(7, -11, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Brocolli");

	//*********
	//Draw radio buttons
	//*********

	//sushi button
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1); // RGB Values for white
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2.4 * cos(10 * PI*i / 999.0)) -15, (1.25 * sin(10 * PI*i / 999.0)) -1.55, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) - 1.55, -1);
	}
	glEnd();

	//pizza button
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1); // RGB Values for white
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2.4 * cos(10 * PI*i / 999.0)) - 15, (1.25 * sin(10 * PI*i / 999.0)) + 1.55, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) + 1.55, -1);
	}
	glEnd();


	//burger button
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1); // RGB Values for white
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2.4 * cos(10 * PI*i / 999.0)) - 15, (1.25 * sin(10 * PI*i / 999.0)) + 4.55, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) + 4.55, -1);
	}
	glEnd();

	//pasta button
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1); // RGB Values for white
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2.4 * cos(10 * PI*i / 999.0)) - 15, (1.25 * sin(10 * PI*i / 999.0)) + 7.55, -1);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((2 * cos(10 * PI*i / 999.0)) - 15, (sin(10 * PI*i / 999.0)) + 7.55, -1);
	}
	glEnd();

	//*********
	//Draw checkboxes
	//*********

	//apple
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_POLYGON);
	glVertex3f(-15.5, -8.5, 0.0);
	glVertex3f(-12.5, -8.5, 0.0);
	glVertex3f(-12.5, -6.9, 0.0);
	glVertex3f(-15.5, -6.9, 0.0);
	glEnd();

	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	glBegin(GL_POLYGON);
	glVertex3f(-15.0, -8.25, 0.0);
	glVertex3f(-13, -8.25, 0.0);
	glVertex3f(-13, -7, 0.0);
	glVertex3f(-15.0, -7, 0.0);
	glEnd();

	//carrot
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_POLYGON);
	glVertex3f(-15.5, -11.5, 0.0);
	glVertex3f(-12.5, -11.5, 0.0);
	glVertex3f(-12.5, -9.9, 0.0);
	glVertex3f(-15.5, -9.9, 0.0);
	glEnd();

	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	glBegin(GL_POLYGON);
	glVertex3f(-15, -11.25, 0.0);
	glVertex3f(-13, -11.25, 0.0);
	glVertex3f(-13, -10, 0.0);
	glVertex3f(-15, -10, 0.0);
	glEnd();

	//wasabi
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_POLYGON);
	glVertex3f(-15.5, -14.5, 0.0);
	glVertex3f(-12.5, -14.5, 0.0);
	glVertex3f(-12.5, -12.9, 0.0);
	glVertex3f(-15.5, -12.9, 0.0);
	glEnd();

	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	glBegin(GL_POLYGON);
	glVertex3f(-15, -14.25, 0.0);
	glVertex3f(-13, -14.25, 0.0);
	glVertex3f(-13, -13, 0.0);
	glVertex3f(-15, -13, 0.0);
	glEnd();

	//fries
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_POLYGON);
	glVertex3f(5.5, -8.5, 0.0);
	glVertex3f(2.5, -8.5, 0.0);
	glVertex3f(2.5, -6.9, 0.0);
	glVertex3f(5.5, -6.9, 0.0);
	glEnd();

	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	glBegin(GL_POLYGON);
	glVertex3f(5.0, -8.25, 0.0);
	glVertex3f(3, -8.25, 0.0);
	glVertex3f(3, -7, 0.0);
	glVertex3f(5.0, -7, 0.0);
	glEnd();

	//brocolli
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_POLYGON);
	glVertex3f(5.5, -11.5, 0.0);
	glVertex3f(2.5, -11.5, 0.0);
	glVertex3f(2.5, -9.9, 0.0);
	glVertex3f(5.5, -9.9, 0.0);
	glEnd();

	glColor3f(0.82352, 0.70588, 0.549019); // RGB Values for tan
	glBegin(GL_POLYGON);
	glVertex3f(5.0, -11.25, 0.0);
	glVertex3f(3, -11.25, 0.0);
	glVertex3f(3, -10, 0.0);
	glVertex3f(5.0, -10, 0.0);
	glEnd();

	//draw checkmarks
	if (sideFries == 1) {
		drawCheckmark(3.5, -7.5, 0);
	}

	if (sideBrocolli == 1) {
		drawCheckmark(3, -10.5, 0);
	}

	if (sideWasabi == 1) {
		drawCheckmark(-15, -13.5, 0);
	}

	if (sideCarrot == 1) {
		drawCheckmark(-15, -10.5, 0);
	}

	if (sideApple == 1) {
		drawCheckmark(-15, -7.5, 0);
	}

	//draw radio selection
	if (entreeChoice == 1) {
		fillPastaButton();
	}

	if (entreeChoice == 2) {
		fillBurgerButton();
	}

	if (entreeChoice == 3) {
		fillPizzaButton();
	}

	if (entreeChoice == 4) {
		fillSushiButton();
	}

	glFlush();
}


// Initialization routine for first window.
void setup1(void)
{
	// White background.
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

// Initialization routine for second window.
void setup2(void)
{
	glClearColor(0.82352, 0.70588, 0.549019, 0.0); //rgb value for tan
}

// Reshape routine for first window.
void resize1(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -10.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

// Reshape routine for second window.
void resize2(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -10.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	//control the radio buttons via asdf keys
	case 'a':
		glutSetWindow(id2);
		entreeSelection(1);
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	case 's':
		glutSetWindow(id2);
		entreeSelection(2);
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	case 'd':
		glutSetWindow(id2);
		entreeSelection(3);
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	case 'f':
		glutSetWindow(id2);
		entreeSelection(4);
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	//control the checkboxes via zxcvb keys
	case 'z':
		glutSetWindow(id2);
		sideApple = !sideApple;
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	case 'x':
		glutSetWindow(id2);
		sideCarrot = !sideCarrot;
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	case 'c':
		glutSetWindow(id2);
		sideWasabi = !sideWasabi;
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	case 'v':
		glutSetWindow(id2);
		sideFries = !sideFries;
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	case 'b':
		glutSetWindow(id2);
		sideBrocolli = !sideBrocolli;
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

/******************************************
mouseControl()

enable mouse usability.
*******************************************/
void mouseControl(int button, int state, int x, int y)
{

	//make the checkboxes for the sides work
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if ((28.5 <= x && x <= 46.5) && (330.5 <= y && y <= 357.9)) {
			glutSetWindow(id2);
			sideApple = !sideApple;
			glutPostRedisplay();
		}

		if ((28.5 <= x && x <= 46.5) && (370.5 <= y && y <= 397.9)) {
			glutSetWindow(id1);
			sideCarrot = !sideCarrot;
			glutPostRedisplay();
		}
	
		if ((28.5 <= x && x <= 46.5) && (410.5 <= y && y <= 437.9)) {
			glutSetWindow(id1);
			sideWasabi = !sideWasabi;
			glutPostRedisplay();
		}

		if ((140.5 <= x && x <= 158.5) && (330.5 <= y && y <= 357.9)) {
			glutSetWindow(id1);
			sideFries = !sideFries;
			glutPostRedisplay();
		}

		if ((140.5 <= x && x <= 158.5) && (370.5 <= y && y <= 397.9)) {
			glutSetWindow(id1);
			sideBrocolli = !sideBrocolli;
			glutPostRedisplay();
		}


		if ((17.5 <= x && x <= 41.5) && (140.5 <= y && y <= 169.9)) {
			glutSetWindow(id1);
			entreeSelection(1);
			glutPostRedisplay();
		}

		if ((17.5 <= x && x <= 41.5) && (179.9 <= y && y <= 209.3)) {
			glutSetWindow(id1);
			entreeSelection(2);
			glutPostRedisplay();
		}

		if ((17.5 <= x && x <= 41.5) && (219.3 <= y && y <= 248.7)) {
			glutSetWindow(id1);
			entreeSelection(3);
			glutPostRedisplay();
		}

		if ((17.5 <= x && x <= 41.5) && (258.7 <= y && y <= 288.1)) {
			glutSetWindow(id1);
			entreeSelection(4);
			glutPostRedisplay();
		}
	}

	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void) {
	cout << "*Interactions:   Press the escape key to quit." << endl;
	cout << "Click the Pasta radio button to see it filled and see it displayed." << endl;
	cout << "Press a to fill the Pasta radio button and see it displayed." << endl;
	cout << "Click the Burger radio button to see it filled and see it displayed." << endl;
	cout << "Press s to fill the Burger radio button and see it displayed." << endl;
	cout << "Click the Pizza radio button to see it filled and see it displayed." << endl;
	cout << "Press d to fill the Pizza radio button and see it displayed." << endl;
	cout << "Click the Sushi radio button to see it filled and see it displayed." << endl;
	cout << "Press f to fill the Sushi radio button and see it displayed." << endl;
	cout << "Click the Apple checkbox to see it filled and see it displayed." << endl;
	cout << "Press z to fill the Apple checkbox and see it displayed." << endl;
	cout << "Click the Carrot checkbox to see it filled and see it displayed." << endl;
	cout << "Press x to fill the Carrot checkbox and see it displayed." << endl;
	cout << "Click the Wasabi checkbox to see it filled and see it displayed." << endl;
	cout << "Press c to fill the Wasabi checkbox and see it displayed." << endl;
	cout << "Click the Fries checkbox to see it filled and see it displayed." << endl;
	cout << "Press v to fill the Fries checkbox and see it displayed." << endl;
	cout << "Click the Brocolli checkbox to see it filled and see it displayed." << endl;
	cout << "Press b to fill the Brocolli checkbox and see it displayed." << endl;
	cout << " " << endl;
	cout << "Right click the Display Panel to display submenu's" << endl;
	cout << "Left click Change Plate Color > Silver to make the plate silver" << endl;
	cout << "Left click Change Plate Color > Purple to make the plate purple" << endl;
	cout << "Left click Change Plate Color > Silver to make the plate blue" << endl;
	cout << "Left click Rotate Plate > 90 to rotate the plate 90 degrees." << endl;
	cout << "Left click Entree Portion > Double to make the portion size bigger" << endl;
	cout << "Left click Entree Portion > Half to make the portion size smaller" << endl;
	cout << "Left click Entree Portion > Original to make the portion size reset back to normal" << endl;
	cout << "Left click Quit to exit the program." << endl;		
}


// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// First top-level window definition.
	glutInitWindowSize(900, 900); //changed to make display window larger than menu
	glutInitWindowPosition(100, 100);

	// Create the first window and return id.
	id1 = glutCreateWindow("Display Panel");

	// Initialization, display, and other routines of the first window. 
	setup1();
	glutDisplayFunc(drawScene1);
	glutReshapeFunc(resize1);
	glutKeyboardFunc(keyInput); // Routine is shared by both windows.

	// Second top-level window definition.
	glutInitWindowSize(250, 500);
	glutInitWindowPosition(1200, 100); //changed to make the menu not appear on top of the display
	makeMenu();

	// Create the second window and return id.
	id2 = glutCreateWindow("Control Panel");

	// Initialization, display, and other routines of the second window. 
	setup2();
	glutDisplayFunc(drawScene2);
	glutReshapeFunc(resize2);
	glutKeyboardFunc(keyInput); // Routine is shared by both windows.
	glutMouseFunc(mouseControl);

	glutMainLoop();

	return 0;
}