/******************************************
*
* Official Name:  Davon Grant
*
* Nickname:  N/A
*
* E-mail:  dgran101@syr.edu
*
* Assignment:  Homework 1
*
* Environment/Compiler:  Visual Studio 2017
*
* Date:  February 4, 2019
*
* References:  Computer Graphics Through OpenGL by Sumanta Guha
			   Animal.cpp was a large part of this program, so there are many similar methods and possibly
			   leftover variables from testing with it.
*
* Interactions:   Press the escape key to quit.
*                 Press O to switch to glOrtho view.
				  Press F to switch to glFrustum view.
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

// Globals. The globals were changed to favor creating Coleman rather than an actual animal
static float R = 0.7; // Radius of head. Edited the original value of 3.0 to make it scale better with the window size.
static int v = 6; // Number of longitudinal (verticle) slices.
static int h = 4; // Number of latitudinal (horizontal) slices 
				  //on hemisphere.
static float cx = -14.0, cy = -13.0, cz = -10.0;  //center of sphere - head 

static float necklength = 1; //Edited the original value of 2.0 to make it scale better with the window size.
static float nx, ny; //x and y components of neck, computed
static float neckAngle = 1;

static float torso = 1.0; //length of body Edited the original value of 10.0 to make it scale better with the window size.
static float girth = 2.0;  //thickness of body. Edited the original value of 5.0 to make it scale better with the window size.
static float URx, URy; //upper right corner of body, computed


static float legx = 1.0, legy = 3.0; //x and y component of leg.
				  //use + or - legy for forward or backward step

static float tailx = 5.0, taily = 1.0; //x and y component of tail

static float shellColors[2][3] = //used in the color gradient for the shell.
{
	{0.0, 0.0, 0.0},
	{0.125, 0.698, 0.666}
};

static float cageVertices[24][3]{ //used in the creation of the cage boundaries.
	//front face
	{-10.0, -2.0, 0.0},
	{-10.0, -10.0, 0.0},
	{0.0, -2.0, 0.0},
	{0.0, -10.0, 0.0},
	{-10.0, -10.0, 0.0},
	{0.0, -10.0, 0.0},
	{-10.0, -2.0, 0.0},
	{0.0, -2.0, 0.0},

	//top face
	{-10.0, -2.0, 0.0},
	{-7.0, 3.0, 0.0},
	{0.0, -2.0, 0.0},
	{3.0, 3.0, 0.0},
	{-7.0, 3.0, 0.0},
	{3.0, 3.0, 0.0},

	//right face
	{3.0, 3.0, 0.0},
	{3.0, -5.0, 0.0},
	{3.0, -5.0, 0.0},
	{0.0, -10.0, 0.0},

	//left face
	{-7.0, 3.0, 0.0},
	{-7.0, -5.0, 0.0},
	{-7.0, -5.0, 0.0},
	{-10.0, -10.0, 0.0},

	//back face
	{-7.0, -5.0, 0.0},
	{3.0, -5.0, 0.0}
};

/******************************************
drawCage()

Draws the cage that is supposed to hold a pig.
*******************************************/
void drawCage() {
	glLineWidth(8.0);
	glColor3f(0.75294, 0.75294, 0.75294); // RGB Values for silver
	glBegin(GL_LINES);

	//draw front face
	glVertex3f(-10,-2,0);
	glVertex3f(-10, -10, 0);
	glVertex3f(0, -2, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(-10, -10, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(-10, -2, 0);
	glVertex3f(0, -2, 0);

	//draw top face
	glVertex3f(-10, -2, 0);
	glVertex3f(-7, 3, 0);
	glVertex3f(0, -2, 0);
	glVertex3f(3, 3, 0);
	glVertex3f(-7, 3, 0);
	glVertex3f(3, 3, 0);

	//draw right side
	glVertex3f(3, 3, 0);
	glVertex3f(3, -5, 0);
	glVertex3f(3, -5, 0);
	glVertex3f(0, -10, 0);

	//draw left side
	glVertex3f(-7, 3, 0);
	glVertex3f(-7, -5, 0);
	glVertex3f(-7, -5, 0);
	glVertex3f(-10, -10, 0);

	//draw back side
	glVertex3f(-7, -5, 0);
	glVertex3f(3, -5, 0);

	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.75294, 0.75294, 0.75294); // RGB Values for silver

	//draw parellopiped outline to represent restrictions inside of the cage
	glLineWidth(3.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 25; ++i)
	{
		glVertex3fv(cageVertices[i]);
	}
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.75294, 0.75294, 0.75294); // RGB Values for silver
}


void drawStickNeck()
{
	//
	glLineWidth(5.0);
	glColor3f(1, 0.8705, 0.6784); // RGB Values for cream
	nx = necklength * cos(neckAngle); //forward component of neck
	ny = necklength * cos(neckAngle) + 0.4; //up component of neck
	URx = cx + R * cos(PI + neckAngle) - nx; //upper right x coord of body
								   // = lower left coord of neck
	URy = cy + R * sin(PI + neckAngle) - ny; //upper right y coord of body
	glBegin(GL_LINES);
	glVertex3f(cx + R * cos(PI + neckAngle) - 1.05, cy + R * sin(PI + neckAngle), cz);
	glVertex3f(URx - 0.5, URy, cz);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
}

void drawRectBody()
{
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(URx, URy, cz);      //upper right corner of body
	glVertex3f(URx - torso, URy, cz);
	glVertex3f(URx - torso, URy - girth, cz);
	glVertex3f(URx, URy - girth, cz);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);

}



void drawStickLegs()
{
	glLineWidth(5.0);
	glColor3f(0.0, 0.0, 0.5019);
	glBegin(GL_LINES);
	//two legs
	glVertex3f(URx - torso + 0.85, URy - girth, cz); //at bottom left of body
	glVertex3f(URx - torso + legx, URy - girth - legy + 1.3, cz);//back forward
	glVertex3f(URx - torso + 0.1, URy - girth, cz); //at bottom left of body
	glVertex3f(URx - torso - legx + 1, URy - girth - legy + 1.3, cz);//back backward

	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
}

/******************************************
drawStickArms()

Draws Coleman's arms which stick out to touch the tortoise. 
This is heavily based on drawStickLegs().
*******************************************/
void drawStickArms() {

	//actual arms
	glLineWidth(5.0);
	glColor3f(1, 0.8705, 0.6784); // RGB Values for cream
	glBegin(GL_LINES);

	//left arm
	glVertex3f(-16, -15, 0.5);
	glVertex3f(-16, -16, 0.5); 
	//right arm
	glVertex3f(-14.8, -15, 0.5);
	glVertex3f(-14.4, -16, 0.5);

	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);

	//arm sleeves of shirt
	glLineWidth(5.0);
	glColor3f(0,0,0); // RGB Values for black
	glBegin(GL_LINES);
	//left arm sleeve
	glVertex3f(-16, -15, 0.5);
	glVertex3f(-16, -15.4, 0.5);
	//right arm sleeve
	glVertex3f(-14.8, -15, 0.5);
	glVertex3f(-14.6, -15.5, 0.5);

	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
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
drawSign()

Draws the sign that "Coleman's Zoo" is posted on.
Supposed to represent wood. This function is heavily based
on drawRectBody, as the shapes are similar.
*******************************************/
void drawSign()
{
	glLineWidth(1.0);
	glColor3f(0.62, 0.32, 0.17); // obtained by dividing brown's RGB values by 255.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-21.0, -10.0, 0.5); //Vertex values were obtained
	glVertex3f(-27.0, -10.0, 0.5); //through extensive testing.
	glVertex3f(-27.0, -14.0, 0.5);
	glVertex3f(-21.0, -14.0, 0.5);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3f(-26.25, -10.8, 0); //taken from textbook and edited position through extensive testing.
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "*********************"); //learned font name from textbook
	glRasterPos3f(-25.25, -11.5, 0); //taken from textbook and edited position through extensive testing.
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Coleman's"); //learned font name from textbook
	glRasterPos3f(-24.5, -12.8, 0); //taken from textbook and edited position through extensive testing.
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Zoo"); //learned font name from textbook
	glRasterPos3f(-26.25, -13.8, 0); //taken from textbook and edited position through extensive testing.
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "*********************"); //learned font name from textbook
	glLineWidth(15.0);
	glColor3f(0.62, 0.32, 0.17);
	glBegin(GL_LINES);
	glVertex3f(-24.0, -14.0, 0.0);
	glVertex3f(-24.0, -17.0, 0.0);
	glEnd();
	glLineWidth(15.0);
}

/******************************************
drawBackground()

Draws the grass and the sky.
This function is also based on drawRectBody,
similar to drawSign().
*******************************************/
void drawBackground(){
	/**********Draw the grass*******************/
	glLineWidth(1.0);
	glColor3f(0.13, 0.545, 0.13); // obtained by dividing green's RGB values by 255.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-30.0, -5.0, 5.0); // Vertex values were obtained
	glVertex3f(10.0, -5.0, 5.0); // through extensive testing. The z value
	glVertex3f(10.0, -50.0, 5.0); // is important here, as the background should be
	glVertex3f(-30.0, -50.0, 5.0); // behind everything
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);

	/**********Draw the sky*******************/
	glLineWidth(1.0);
	glColor3f(0.0, 0.75, 1.0); // obtained by dividing sky blue's RGB values by 255.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-30.0, -5.0, 0.0); // Vertex values were obtained
	glVertex3f(10.0, -5.0, 0.0); // through extensive testing. The z value
	glVertex3f(10.0, 50.0, 0.0); // is important here, as the background has to be
	glVertex3f(-30.0, 50.0, 0.0); // behind everything
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
}

/******************************************
drawSun()

Draws the sun. Initially, I tried to include this in the drawBackground
function, but I was not able to get it to show up properly, so I tried 
making it it's own function.
*******************************************/
void drawSun() {
	//this method uses an large number of points to create a circle. Initially, I tried
	//larger numbers than 999 (i.e 999999), but this caused the program to lag and take a while to load.
	//999 seemed liked the sweet spot between looking like a circle and not affecting
	//performance

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((5 * cos(25 * PI*i / 999.0)) + 9, (5 * sin(25 * PI*i / 999.0)) + 18, -5); //z value is negative to make it appear above everything
	}
	glEnd();

	//The following creates the rays of the sun using GL_LINES
	glLineWidth(5.0);
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	//Horizontal Rays
	glVertex3f(2.7, 19.0, 0.0);
	glVertex3f(5.0, 19.0, 0.0);
	glVertex3f(2.7, 18.0, 0.0);
	glVertex3f(5.0, 18.0, 0.0);
	glVertex3f(2.7, 17.0, 0.0);
	glVertex3f(5.0, 17.0, 0.0);
	//Vertical Rays
	glVertex3f(9.5, 14.0, 0.0);
	glVertex3f(9.5, 11.5, 0.0);
	glVertex3f(8.5, 14.0, 0.0);
	glVertex3f(8.5, 11.5, 0.0);
	glVertex3f(7.5, 14.0, 0.0);
	glVertex3f(7.5, 11.5, 0.0);
	//Diagonal Rays. If I had more knowledge, I would've used some sort of mathematical way to actually
	//get evenly dispersed/sized ways, but for now I just had to do it manually.
	glVertex3f(6.5, 14.0, 0.0);
	glVertex3f(5.8, 12.0, 0.0);
	glVertex3f(5.8, 14.8, 0.0);
	glVertex3f(4.6, 13.0, 0.0);
	glVertex3f(5.8, 15.8, 0.0);
	glVertex3f(3.8, 13.9, 0.0);
	glVertex3f(5.8, 16.1, 0.0);
	glVertex3f(3.3, 14.7, 0.0);
	glVertex3f(5.8, 16.7, 0.0);
	glVertex3f(2.9, 16.0, 0.0);
	glEnd();
	glLineWidth(5.0);

}

/******************************************
drawTortoise()

Draws the tortoise. This includes the shell and the tortoise's other body parts.
*******************************************/
void drawTortoise() {
	int i, j;
	//draw the shell. Based on the original version of drawHead() in animal.cpp.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.125, 0.698, 0.666); // RGB Values for light sea green

	for (j = 0; j < h; j++)
	{
		
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= v; i++)
		{  //the original drawHead() uses R, which is a global variable we use here to
			//draw  Coleman's head. This is why we replaced R with 2.3, which is bigger
			//than Coleman's head. We also replaced cx and cy to position it correctly.
			glColor3fv(shellColors[i%2]);
			glVertex3f(2.3 * cos((float)(j + 1) / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) -10,
				2.3 * sin((float)(j + 1) / h * PI / 2.0) - 17,
				2.3 * cos((float)(j + 1) / h * PI / 2.0) * sin(2.0 * (float)i / v * PI));
			glColor3f(0.125, 0.698, 0.666);
			glVertex3f(2.3 * cos((float)j / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) -10,
				2.3 * sin((float)j / h * PI / 2.0) - 17,
				2.3 * cos((float)j / h * PI / 2.0) * sin(2.0 * (float)i / v * PI));
		}
		glEnd();
	}

	//outline the shell to give it more of a "shell" look
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 0, 0); // RGB Values for black
	for (j = 0; j < h; j++)
	{

		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= v; i++)
		{  //the original drawHead() uses R, which is a global variable we use here to
			//draw  Coleman's head. This is why we replaced R with 2.3, which is bigger
			//than Coleman's head. We also replaced cx, cy and cz to position it correctly.
			glVertex3f(2.3 * cos((float)(j + 1) / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) - 10,
				2.3 * sin((float)(j + 1) / h * PI / 2.0) - 17,
				2.3 * cos((float)(j + 1) / h * PI / 2.0) * sin(2.0 * (float)i / v * PI) -5);
			glVertex3f(2.3 * cos((float)j / h * PI / 2.0) * cos(2.0 * (float)i / v * PI) - 10,
				2.3 * sin((float)j / h * PI / 2.0) - 17,
				2.3 * cos((float)j / h * PI / 2.0) * sin(2.0 * (float)i / v * PI)- 5);
		}
		glEnd();
	}

	//draw the tortoise's legs & neck

	glLineWidth(5.0);
	glColor3f(0.5019, 0.5019, 0.0);
	glBegin(GL_LINES);
	//two legs
	glVertex3f(-11.5, -17, 0.0); //bottom left leg
	glVertex3f(-11.5, -18, 0.0);
	glVertex3f(-9.0, -17, 0.0); //bottom right leg
	glVertex3f(-9.0, -18, 0.0);
	glVertex3f(-7.5, -16, 0); //neck
	glVertex3f(-7.7, -16.5, 0);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);

	//draw the tortoise's head

	glColor3f(0.5019, 0.5019, 0); // RGB Values for olive green
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.5* (cos(2 * PI*i / 999.0)) - 7.3, 0.5 * (sin(2 * PI*i / 999.0)) - 16, -5);
	}
	glEnd();

	//draw the tortoise's left eyeball
	glColor3f(0, 0, 0); // RGB Values for black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.1* (cos(2 * PI*i / 999.0)) - 7.45, 0.1 * (sin(2 * PI*i / 999.0)) - 16, -5);
	}
	glEnd();

	//draw the tortoise's right eyeball
	glColor3f(0, 0, 0); // RGB Values for black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.1* (cos(2 * PI*i / 999.0)) - 7.05, 0.1 * (sin(2 * PI*i / 999.0)) - 16, -5);
	}
	glEnd();
}

/******************************************
drawHumanHead()

Draws Coleman's head. This includes his head, hair, eyes, and mouth.
*******************************************/
void drawHumanHead() {

	//draw the circle of his head
	glColor3f(1, 0.8705, 0.6784); // RGB Values for cream
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i) //the more points we include, the rounder it will look.
	{
		glVertex3f((cos(25 * PI*i / 999.0)) - 15, (sin(25 * PI*i / 999.0)) -13, -1); //z value is negative to make it appear above everything
	}
	glEnd();

	//draw his hair
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//left most part of his hair
	glBegin(GL_POLYGON);
	glVertex3f(-16.1, -12.6, 0.0);
	glVertex3f(-15.7, -12.6, 0.0);
	glVertex3f(-15.7, -11.9, 0.0);
	glVertex3f(-16.1, -11.9, 0.0);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
	//right most part of his hair
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-13.93, -12.6, 0.0);     
	glVertex3f(-14.33, -12.6, 0.0);
	glVertex3f(-14.33, -11.9, 0.0);
	glVertex3f(-13.93, -11.9, 0.0);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
	//center part of hair
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-16.1, -12.3, 0.0);
	glVertex3f(-13.93, -12.3, 0.0);
	glVertex3f(-13.93, -11.7, 0.0);
	glVertex3f(-16.1, -11.7, 0.0);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);
	
	//draw mouth
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-14.55, -13.5, 0.0);
	glVertex3f(-14.95, -13.9, 0.0);
	glVertex3f(-15.35, -13.5, 0.0);
	glEnd();
	glLineWidth(1.0);  //restore width and color
	glColor3f(0.0, 0.0, 0.0);

	//draw left eyeball
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.3* (cos(2 * PI*i / 999.0)) - 15.4, 0.3 * (sin(2 * PI*i / 999.0)) - 13, -5); //z value is nearer than the head
	}
	glEnd();

	//draw left pupil
	glColor3f(0, 0, 0); // RGB Values for white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.1* (cos(2 * PI*i / 999.0)) - 15.4, 0.1 * (sin(2 * PI*i / 999.0)) - 13, -5); //z value is nearer than the head
	}
	glEnd();

	//draw right eyeball
	glColor3f(1, 1, 1); // RGB Values for white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.3* (cos(2 * PI*i / 999.0)) - 14.6, 0.3 * (sin(2 * PI*i / 999.0)) - 13, -5); //z value is nearer than the head
	}
	glEnd();

	//draw right pupil
	glColor3f(0, 0, 0); // RGB Values for white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.1* (cos(2 * PI*i / 999.0)) - 14.6, 0.1 * (sin(2 * PI*i / 999.0)) - 13, -5); //z value is nearer than the head
	}
	glEnd();

}

/******************************************
drawPig()

Draws the pig that is displayed in the cage
*******************************************/
void drawPig() {

	glColor3f(0.8588, 0.4392, 0.57647); // obtained by dividing pink's RGB values by 255.

	/* This was my attempt at creating a parellelpiped through a single triangle strip.
	   I tried figuring out the vertices in my head, but that wasn't even close. Then, I drew
	   everything out on a piece of paper and tried to really examine which vertices would
	   have to go in which order, but no matter what I did I just could not figure it out. I'm
	   guessing that I was somewhat close, as I at least got one face correct (I think?)
	glLineWidth(1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(-1.0, 1.0, 4.0);
	glVertex3f(1.0, 1.0, 4.0);
	glVertex3f(-1.0, -1.0, 4.0);
	glVertex3f(1.0, -1.0, 4.0);

	glVertex3f(-1.0, -1.0, -4.0);
	glVertex3f(1.0, -1.0, -4.0);
	glVertex3f(-1.0, 1.0, -4.0);
	glVertex3f(1.0, 1.0, -4.0);

	glVertex3f(-1.0, 1.0, -4.0);
	glVertex3f(-1.0, -1.0, -4.0);
	glVertex3f(1.0, -1.0, -4.0);
	glVertex3f(1.0, -1.0, 4.0);
	*/

	//Normal rectangular body 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5, -7.9, 0.0);
	glVertex3f(-2.5, -7.9, 0.0);
	glVertex3f(-2.5, -5.7, 0.0);
	glVertex3f(-5.5, -5.7, 0.0);
	glEnd();

	//legs and neck
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex3f(-5.5, -7.9, 0.0); //back right leg
	glVertex3f(-5.5, -9.0, 0.0);
	glVertex3f(-4.7, -7.9, 0.0); //back left leg
	glVertex3f(-4.7, -8.4, 0.0);
	glVertex3f(-3.4, -7.9, 0.0); //front right leg
	glVertex3f(-3.4, -9.0, 0.0);
	glVertex3f(-2.6, -7.9, 0.0); //front left leg
	glVertex3f(-2.6, -8.4, 0.0);
	glVertex3f(-2.5, -5.7, 0); //neck
	glVertex3f(-2.1, -5.1, 0);
	glEnd();
	glLineWidth(1.0);  //restore width and color

	//head
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f((cos(25 * PI*i / 999.0)) - 2.5, (sin(25 * PI*i / 999.0)) - 5.7, 0.0);
	}
	glEnd();

	//eyes

	//left eyeball
	glColor3f(0, 0, 0); // RGB Values for black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.1* (cos(2 * PI*i / 999.0)) - 3.0, 0.1 * (sin(2 * PI*i / 999.0)) - 5.7, 0);
	}
	glEnd();

	//right eyeball
	glColor3f(0, 0, 0); // RGB Values for black
	glBegin(GL_POLYGON);
	for (int i = 0; i < 999; ++i)
	{
		glVertex3f(0.1* (cos(2 * PI*i / 999.0)) - 2.0, 0.1 * (sin(2 * PI*i / 999.0)) - 5.7, 0);
	}
	glEnd();
}

/******************************************
drawColeman()

Originally named drawAnimal() and was from animal.cpp from the textbook. 
This was modified and ended up being used strictly to draw Coleman.
*******************************************/
void drawColeman()
{
	drawHumanHead();
	drawStickNeck();
	drawRectBody();
	drawStickArms();
	drawStickLegs();
}
// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(10, 0, -10);
	drawBackground(); //call drawBackground() function
	drawColeman(); //call drawColeman() function
	drawTortoise(); //call drawTortoise() function
	drawPig(); //call drawPig() function
	drawSign(); //call drawSign() function
	drawSun();//call drawSun() function
	drawCage(); //call drawCage() function
	glPopMatrix();

	glFlush();
}

// Initialization routine.
void setup(void)
{
	//white background
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	//enabled to use vertex array and color array as per the requirements.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -10.0, 20.0);

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
	//if the user presses O, switch to orthographic projection
	case 'o':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-20.0, 20.0, -20.0, 20.0, -10.0, 20.0);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
		break;

	//if the user presses F, switch to frustum
	case 'f':
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-15.0, 7.0, -15.0, -3.0, 5.0, 12.0);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Press escape key to close window" << endl;
	cout << "Press O to see glOrtho view" << endl; //added for requirements
	cout << "Press F to see glFrustum view" << endl; //added for requirements

}


// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Coleman & The Tortoise");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMainLoop();

	return 0;
}