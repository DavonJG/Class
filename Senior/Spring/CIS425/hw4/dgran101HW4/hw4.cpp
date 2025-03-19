/******************************************
*
* Official Name:  Davon Grant
*
* Nickname:  N/A
*
* E-mail:  dgran101@syr.edu
*
* Assignment:  Homework 4
*
* Environment/Compiler:  Visual Studio 2017
*
* Date:  March 8, 2019
*
* References:  Computer Graphics Through OpenGL by Sumanta Guha and lecture notes
			   walkingAroundForClassv2.cpp was the starting point of this program, so there are many
			   similar methods. Other references include glutObjects.cpp, and the textbook chapters that
			   referred to Quadric objects
*
* Interactions:	    Press the escape key to quit.
					up arrow - step forward
					down arrow - step backward
					right arrow - turn to the right
					left arrow - turn to the left
					shift+up arrow - look up
					shift+down arrow - look down
					d - opens the doors. can only be used when next to the door.
					l - flick the light switch. can only be used when next to the light switch
					p - light up the pumpkin. can only be used when next to the pumpkin (INCOMPLETE)
					b - have the ball move to the hat and start the game
					h - choose a house. can only be used when the game is in effect.

*
*******************************************/

#include <iostream>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159
using namespace std;

static float meX = 0, meY = 0, meZ = 0;
static float angle = 0;
static int gameWinner = rand() % 3;
static float haveFlashlight = 0;
static float gameStart = 0;
static float gameChoice = 99;
static float pumpkinLit = 0;
static float bulbLit = 0;
static float doorAngle = 0;
static float neckAngle = 0;
static float stepsize = 5.0;  //step size
static float turnsize = 10.0; //degrees to turn

// Initialization routine.
void setup(void)
{

	//glEnable(GL_LIGHTING);
	glClearColor(0.0784, 0.219607, 0.419607, 0.0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.
	//glEnable(GL_NORMALIZE);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

// Routine to draw a stroke character string.
void writeStrokeString(void *font, const char *string)
{
	const char *c;
	for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

//draw a wall
void drawWall(float r, float g, float b, float x, float y, float z) {
	glColor3f(r, g, b);
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(10.0, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();
}

void drawDoors(float doorAngle) {
	//left door
	glColor3f(0.8274, 0.8274, 0.8274);
	glPushMatrix();
	glTranslatef(3, 0, 55);
	glRotatef(doorAngle, 0.0, 1.0, 0.0);
	glScalef(2.0, 5.0, 0.2);
	glutSolidCube(4.0);
	glPopMatrix();
	//left doorknob
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	if(doorAngle == 0)
		glTranslatef(0, 0, 54.1);
	else
		glTranslatef(1, 0, 54.1);
	glRotatef(doorAngle, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
	//right door
	glColor3f(0.8274, 0.8274, 0.8274);
	glPushMatrix();
	glTranslatef(-5, 0, 55);
	glRotatef(-doorAngle, 0.0, 1.0, 0.0);
	glScalef(2.0, 5.0, 0.2);
	glutSolidCube(4.0);
	glPopMatrix();
	//right doorknob
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	if (doorAngle == 0)
		glTranslatef(-1.8, 0, 54.1);
	else
		glTranslatef(-2.8, 0, 54.1);
	glRotatef(doorAngle, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
}

void drawHouseWalls() {

	//front and back walls

	//for the front wall, we cant use drawWall since there is a door to draw around.
	//front left wall outside
	glPushMatrix();
	glColor3f(0.39607, 0.26274, 0.12941);
	glTranslatef(20, 0, 55);
	glScalef(4, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();
	//front left wall inside
	glPushMatrix();
	glColor3f(0.972549, 0.874509, 0.694117);
	glTranslatef(20, 0, 56);
	glScalef(4, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();
	//front right wall outside
	glPushMatrix();
	glColor3f(0.39607, 0.26274, 0.12941);
	glTranslatef(-22, 0, 55);
	glScalef(4, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();
	//front right wall inside
	glPushMatrix();
	glColor3f(0.972549, 0.874509, 0.694117);
	glTranslatef(-22, 0, 56);
	glScalef(4, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();
	//top middle wall outside
	glPushMatrix();
	glColor3f(0.39607, 0.26274, 0.12941);
	glTranslatef(3, 23, 55);
	glScalef(6, 6.2, 0.2);
	glutSolidCube(4.0);
	glPopMatrix();
	//top middle wall inside
	glPushMatrix();
	glColor3f(0.972549, 0.874509, 0.694117);
	glTranslatef(3, 23, 56);
	glScalef(6, 6.2, 0.2);
	glutSolidCube(4.0);
	glPopMatrix();

	drawWall(0.39607, 0.26274, 0.12941, 0, 0, 120); //back wall outside
	drawWall(0.63921, 0.43137, 0.26666, 0, 0, 119); //back wall inside


	//ceiling
	glPushMatrix();
	glColor3f(0.41568, 0.27843, 0.19607);
	glTranslatef(-2, 35, 87);
	glRotatef(90, 1, 0, 0);
	glScalef(7.5, 7.2, 0.2);
	glutSolidCube(9.0);
	glPopMatrix();

	//floor
	glPushMatrix();
	glColor3f(0.8, 0.65882, 0.478431);
	glTranslatef(-2, -5, 87);
	glRotatef(90, 1, 0, 0);
	glScalef(7.5, 7.2, 0.2);
	glutSolidCube(9.0);
	glPopMatrix();

	//side walls
	glPushMatrix();
	glRotatef(90, 0, 1, 0);

	//for the left wall, we cant use drawWall since there is a window to draw around.

	//left (right) wall outside
	glPushMatrix();
	glColor3f(0.39607, 0.26274, 0.12941);
	glTranslatef(-110, 0, 33);
	glScalef(4, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left (right) wall inside
	glPushMatrix();
	glColor3f(0.81568, 0.603921, 0.411764);
	glTranslatef(-110, 0, 32);
	glScalef(4, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left (left) wall outside
	glPushMatrix();
	glColor3f(0.39607, 0.26274, 0.12941);
	glTranslatef(-65, 0, 33);
	glScalef(3, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left (left) wall inside
	glPushMatrix();
	glColor3f(0.81568, 0.603921, 0.411764);
	glTranslatef(-65, 0, 32);
	glScalef(3, 10.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left (top) wall outside
	glPushMatrix();
	glColor3f(0.39607, 0.26274, 0.12941);
	glTranslatef(-95, 28, 33);
	glScalef(7, 2.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left (top) wall inside
	glPushMatrix();
	glColor3f(0.81568, 0.603921, 0.411764);
	glTranslatef(-95, 28, 32);
	glScalef(7, 2.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left (bottom) wall outside
	glPushMatrix();
	glColor3f(0.39607, 0.26274, 0.12941);
	glTranslatef(-95, -1, 33);
	glScalef(7, 1.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left (bottom) wall inside
	glPushMatrix();
	glColor3f(0.81568, 0.603921, 0.411764);
	glTranslatef(-95, -1, 32);
	glScalef(7, 1.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//middle window bar
	glColor3f(0.8274509, 0.8274509, 0.8274509);
	glPushMatrix();
	glTranslatef(-86, 11, 32);
	glScalef(0.1, 2.3, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//left window bar
	glColor3f(0.8274509, 0.8274509, 0.8274509);
	glPushMatrix();
	glTranslatef(-76, 11, 32);
	glScalef(0.1, 2.3, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	//right window bar
	glColor3f(0.8274509, 0.8274509, 0.8274509);
	glPushMatrix();
	glTranslatef(-95, 11, 32);
	glScalef(0.1, 2.3, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();

	
	drawWall(0.39607, 0.26274, 0.12941, -90, 0, -35);//right wall outside
	drawWall(0.81568, 0.603921, 0.411764, -90, 0, -34); //right wall inside
	glPopMatrix();
}

void drawBulb(){
	//draw string
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 30, 90);
	glScalef(0.1, 2.0, 0.2);
	glutSolidCube(7.0);
	glPopMatrix();
	//draw light bulb
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 20, 90);
	glScalef(1.0, 1.0, 1.0);
	glutSolidSphere(3.0, 100, 100);
	glPopMatrix();

}


void drawLightSwitch() {
	//white box
	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-60, 0, -33); 
	glScalef(0.5, 1.0, 0.2);
	glutSolidCube(3.0);
	glPopMatrix();

	//switch
	glColor3f(0, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	if(bulbLit == 0)
		glTranslatef(-60, -1, -32.6);
	else
		glTranslatef(-60, 1, -32.6);
	glScalef(0.3, 0.1, 0.2);
	glutSolidCube(3.0);
	glPopMatrix();
}

void drawTable() {
	//draw base
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-2, -3, 95);
	glRotatef(90, 1, 0, 0);
	glScalef(2.5, 2.2, 0.2);
	glutSolidCube(3.0);
	glPopMatrix();

	//draw legs
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-5, -3.5, 92);
	glScalef(0.1, 0.5, 0.2);
	glutSolidCube(3.0);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-5, -3.5, 98);
	glScalef(0.1, 0.5, 0.2);
	glutSolidCube(3.0);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(1, -3.5, 92);
	glScalef(0.1, 0.5, 0.2);
	glutSolidCube(3.0);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(1, -3.5, 98);
	glScalef(0.1, 0.5, 0.2);
	glutSolidCube(3.0);
	glPopMatrix();
}

void drawPumpkin() {

	float glowing[] = { 1, 0, 0 };
	float notGlowing[] = { 0, 0, 0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glowing);
	//base
	glPushMatrix();
	glColor3f(1.0, 0.45882, 0.09411);
	glTranslatef(0, -2, 92.5);
	glRotatef(90, 1, 0, 0);
	glutSolidSphere(1.0, 100, 100);
	glPopMatrix();

	//stem
	glColor3f(0.05490, 0.2274, 0.09803);
	glPushMatrix();
	glTranslatef(0, -0.8, 92.5);
	glScalef(0.1, 0.5, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawBall(float r, float g, float b, float x, float y, float z) {
	glPushMatrix();
	glColor3f(r,g,b);
	glTranslatef(x, y, z);
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
}

void drawGrass() {
	glColor3f(0.196, 0.804, 0.196);
	glScalef(1, 1, 1.5);
	glutSolidCube(90);
}

void drawFlashlight() {
	//draw base
	glPushMatrix();
	glColor3f(0.521568, 0.5176470, 0.541176);
	glTranslatef(-4, -2, 95);
	glRotatef(0, 1, 0, 0);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj, 0.4, 0.4, 2, 100, 100);
	glPopMatrix();

	//draw light
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-4, -2, 95);
	glRotatef(90, 1, 0, 0);
	glutSolidSphere(0.3, 100, 100);
	glPopMatrix();
}

void drawHat(){
	//top
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-2, -0.5, 95);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj, 1.0, 1.0, 2, 100, 100);
	glPopMatrix();

	//bottom
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-2, -2.5, 95);
	glRotatef(90, 1, 0, 0);
	gluDisk(obj, 0, 1.4, 100, 100);
	glPopMatrix();

}

void drawGame() {
	drawBall(0.97254, 0.74117, 0.015686, 0, 2, 95);
	drawBall(0.07058, 0.27058, 0.062745, -4, 2, 95);
}

void drawHouse() {
	int ballX = -18;
	int ballY = -3;
	int ballZ = -113;
	drawHouseWalls();
	drawDoors(doorAngle);
	drawBulb();
	drawLightSwitch();
	drawTable();
	drawPumpkin();
	if (haveFlashlight == 0) {
		drawFlashlight();
	}
	if (gameStart == 0) {
		drawBall(0.95686, 0.3725, 0.2588, -18, -3, 113);
	}
	else {
		drawBall(0.95686, 0.3725, 0.2588, -2, 2, 95);
	}
	drawHat();
	if (gameStart == 1) {
		drawGame();
	}
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(meX, meY, meZ, meX + sin(angle*PI / 180), meY + sin(neckAngle*PI / 180), meZ + cos(angle*PI / 180), 0, 1, 0);
	glColor4f(0.0, 0.0, 0.0, 1.0);

	//draw house
	drawHouse();
	glPushMatrix();
	glTranslatef(0.0, -50.0, 30.0);
	glScalef(1, 1, 2);
	drawGrass();
	glPopMatrix();


	glutSwapBuffers();
}

void specialKeyInput(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: //forward
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
			if (neckAngle < 50) //cap how high the user can look because otherwise things look not great
				neckAngle += turnsize;
			else
				break;		
		else
			meZ = meZ + stepsize * cos(angle*PI / 180);
			meX = meX + stepsize * sin(angle*PI / 180);
		break;
	case GLUT_KEY_DOWN: //back
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
			if (neckAngle > -50) //cap how low the user can look because otherwise things look not great
				neckAngle -= turnsize;
			else
				break;
		else
			meZ = meZ - stepsize * cos(angle*PI / 180);
			meX = meX - stepsize * sin(angle*PI / 180);
		break;
	case GLUT_KEY_RIGHT: //turn right
		angle -= turnsize;
		break;
	case GLUT_KEY_LEFT: //turn left
		angle += turnsize;
		break;
	}//end switch
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "\tup arrow - step forward" << endl;
	cout << "\tdown arrow - step backward" << endl;
	cout << "\tright arrow - turn to the right" << endl;
	cout << "\tleft arrow - turn to the left" << endl;
	cout << "\tshift+up arrow - look up" << endl;
	cout << "\tshift+down arrow - look down" << endl;
	cout << "\td - opens the doors. can only be used when next to the door." << endl;
	cout << "\tl - flick the light switch. can only be used when next to the light switch" << endl;
	cout << "\tp - light up the pumpkin. can only be used when next to the pumpkin (INCOMPLETE)" << endl;
	cout << "\tb - have the ball move to the hat and start the game" << endl;
	cout << "\th - choose a house. can only be used when the game is in effect.(INCOMPLETE)" << endl;
	if (gameWinner == 0) {
		cout << "\tThe correct answer to the game is the green ball, which represents Slytherin" << endl;
	}
	else if (gameWinner == 1) {
		cout << "\tThe correct answer to the game is the red ball, which represents Griffindor" << endl;
	}
	else if (gameWinner == 2) {
		cout << "\tThe correct answer to the game is the yellow ball, which represents Hufflepuff" << endl;
	}
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case 'b':
		if ((-13 > meX) && (-23 < meX) && (meZ < 116) && (meZ > 106)) {
			gameStart = 1;	
		}
		break;

	case 'f':
		if ((-2.8 > meX) && (-9 < meX) && (meZ < 102) && (meZ > 86)) {
			if (haveFlashlight == 1) {
				haveFlashlight = 0;
			}
			else
				haveFlashlight = 1;
		}
		break;

	case 'p':
		if ((-2 < meX) && (meX < 5) && (meZ < 94) && (meZ > 88)) {
			if (pumpkinLit == 1) {
				pumpkinLit = 0;
			}
			else
				pumpkinLit = 1;
		}
		break;

	case 'l':
		if ((-32 < meX) && (meX < -22) && (meZ < 65) && (meZ > 55)) {
			if (bulbLit == 1) {
				bulbLit = 0;
			}
			else
				bulbLit = 1;
		}
		break;

	case 'd':
		if ((-5 < meX) && (meX < 3) && (meZ < 65) && (meZ > 45)) {
			if (doorAngle == 60) {
				doorAngle = 0;
			}
			else
				doorAngle = 60;
		}
	default:
		break;
	}
	glutPostRedisplay();
}


// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("HW4");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	glutMainLoop();

	return 0;
}