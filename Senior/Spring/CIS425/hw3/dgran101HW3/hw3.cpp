/******************************************
*
* Official Name:  Davon Grant
*
* Nickname:  N/A
*
* E-mail:  dgran101@syr.edu
*
* Assignment:  Homework 3
*
* Environment/Compiler:  Visual Studio 2017
*
* Date:  March 20, 2019
*
* References:  Computer Graphics Through OpenGL by Sumanta Guha and lecture notes
			   RotatingHelix3.cpp was the starting point of this program, so there are many
			   similar methods. Other references include BoxAndCubesPickingUpAndDragging.cpp (DIDNT END UP USING, FAILED TO IMPLEMENT MOUSE)
			   ballAndTorus.cpp, and glutObjects.cpp
*
* Interactions:
	Press 'esc' to quit
	Press 'r' to reset the scene
	Press 's' to send the bird on it's flight path
	Press 'f' to toggle the wing flapping
	Press '0' to view from overhead
	Press '1' to view from north
	Press '2' to view from east
	Press '3' to view from south
	Press '4' to view from west
	Press 'up' to increase flight speed along the path
	Press 'down' to decrease flight speed along the path
*
*******************************************/

#include <cstdlib>
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
static int onPath = 0; //used to determine if the bird is flying
static int pathTime = 30; //used to determine flight speed
static int atTree = 1;
static int birdX = -10;
static int birdY = -6;
static int birdZ = -10;
static int wingAngle = 30; //used to flap the bird's wings
static int flying = 0; //determines if wings are flapping
static int currentView = 2; //default view is from the east

//draw the cube used to represent grass
void drawGrass(float x, float y, float z) {
	glColor3f(0.568627, 0.86666, 0.043137);
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(5.0, 1.5, 1.0);
	glutSolidCube(50);
	glPopMatrix();
}

void drawBird(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	//draw birds body
	glPushMatrix();
	glColor3f(0.17647, 0.666666, 0.882352);
	glTranslatef(-5.0, -10.0, -15.0);
	glRotatef(45, 10.0, 10.0, 0.0);
	glScalef(1.0, 0.5, 0.5);
	glutSolidSphere(2.0, 100.0, 100.0);
	glPopMatrix();

	//draw birds head
	glPushMatrix();
	glColor3f(0.17647, 0.666666, 0.882352);
	glTranslatef(-3.5, -8.0, -15.0);
	glRotatef(45, 10.0, 10.0, 0.0);
	glScalef(1.0, 1, 0.5);
	glutSolidSphere(1.0, 100.0, 100.0);
	glPopMatrix();

	//draw birds eye
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(-2.9, -7.0, -14.0);
	glRotatef(45, 10.0, 10.0, 0.0);
	glutSolidSphere(0.2, 100.0, 100.0);
	glPopMatrix();

	//draw birds beak
	glPushMatrix();
	glColor3f(0.89803, 0.58039, 0.160784);
	glTranslatef(-2.2, -7.2, -14.0);
	glRotatef(150, 10.0, 10.0, 0.0);
	glutSolidCone(0.2, 2.0, 10, 10);
	glPopMatrix();

	//draw birds wings
	glPushMatrix();
	glColor3f(1, 0.666666, 0.182352);
	glTranslatef(-6.6, -9.9, -16);
	glRotatef(wingAngle, 1.0, 0.0, 0.0);
	glScalef(1.0, 1.5, 0.5);
	glutSolidSphere(1.0, 100.0, 100.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.17647, 0.666666, 0.182352);
	glTranslatef(-4.6, -9.9, -14);
	glRotatef(-wingAngle, 1.0, 0.0, 0.0);
	glScalef(1.0, 1.5, 0.5);
	glutSolidSphere(1.0, 100.0, 100.0);
	glPopMatrix();
	glPopMatrix();
}

//draw a tree
void drawTree() {
	//draw leaves on top
	glColor3f(0.00392, 0.2666666, 0.1294117);
	glPushMatrix();
	glTranslatef(1.5, 5.4, -28.0);
	glutWireSphere(9, 75, 75);
	glPopMatrix();

	//draw tree trunk
	glPushMatrix();
	glColor3f(0.55294, 0.172549, 0.09019);
	glTranslatef(0, -12, -30);
	glScalef(0.5, 5.0, 0.5);
	glutSolidCube(5);
	glPopMatrix();
}

//draws a nest. could not figure out why it wouldn't appear under the bird, so decided to draw it next to the bird.
void drawNest() {
	glPushMatrix();
	glColor3f(0.945098, 0.941176, 0.941176);
	glTranslatef(-9.0, -15.0, -20.0);
	glRotatef(30, 10.0, 10.0, 0.0);
	glScalef(1.5, 0.5, 0.1);
	glutSolidSphere(2.0, 100.0, 100.0);
	glPopMatrix();
}

//drawImage is used in order to draw everything that needs to be drawn,
//rather than doing it all in drawScene.
void drawImage(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw the grass
	drawGrass(0.0, -45.0, -100.0);
	if (currentView == 1) { //North
		gluLookAt(50.0, 10.0, -45.0, -1000.0, -30.0, 0.0, 0.0, 1.0, 0.0);
	}
	else if (currentView == 2) { //East
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	else if (currentView == 3) { //South
		gluLookAt(-50.0, 0.0, -50.0, 1000.0, -30.0, 0.0, 0.0, 1.0, 0.0);
	}
	else if (currentView == 4) { //West
		gluLookAt(0.0, 0.0, -90.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	else if (currentView == 0) { //Top view
		gluLookAt(0.0, 60.0, -30.0, 0.0, -200.0, 0.0, 0.0, 1.0, 0.0);
	}
	//draw trees
	
	//left middle
	glPushMatrix();
	glTranslatef(-18.0, 0.0, -40.0);
	glScalef(0.5, 0.5, 1.0);
	drawTree();
	glPopMatrix();
	
	//right middle
	glPushMatrix();
	glTranslatef(20.0, 0.0, -40.0);
	glScalef(0.5, 0.5, 1.0);
	drawTree();
	glPopMatrix();
	
	//rightmost
	glPushMatrix();
	glTranslatef(27.0, 0.0, -10.0);
	glScalef(0.5, 0.5, 1.0);
	drawTree();
	glPopMatrix();
	
	//leftmost 
	glPushMatrix();
	glTranslatef(-20.0, 0.0, -10.0);
	glScalef(0.5, 0.5, 1.0);
	drawTree();
	glPopMatrix();

	//draw the bird
	glPushMatrix();
	drawBird(birdX, birdY, birdZ);
	glPopMatrix();

	//draw the nest
	glPushMatrix();
	drawNest();
	glPopMatrix();
}

//flap wings
void flap() {
	if (wingAngle == 60) {
		wingAngle = -30;
	}
	else {
		wingAngle = 60;
	}
	glutPostRedisplay();
}

//run flap() if the flying global variable is 1
void startFlying(int x) {
	if (flying) {
		flap();
	}
	glutTimerFunc(20, startFlying, 1);
}

//define the path that the bird follows
void birdPath() {

	flying = 1;
	glutIdleFunc(flap);

	//start the path and move to the first tree, as well as the second.
	if (atTree == 1) {
		if ((birdX == -18) && (birdY == 0) && (birdZ == -40)) {
			atTree = 2;
		}
		else {
			if (birdX < (-18))
				birdX += 1;
			else if (birdX > (-18))
				birdX -= 1;
			if (birdZ < (-40))
				birdZ += 1;
			else if (birdZ > (-40))
				birdZ -= 1;
			if (birdY < 0)
				birdY += 1;
			else if (birdY > 0)
				birdY -= 1;
		}
	}
	
	//move to the third tree, and set atTree to 3 when it arrives
	if (atTree == 2) {
		if ((birdX == 19) && (birdY == 0) && (birdZ == -40)) {
			atTree = 3;
		}

		else {
			if (birdX < 20)
				birdX += 1;
			else if (birdX > 20)
				birdX -= 1;
			if (birdZ < (-40))
				birdZ += 1;
			else if (birdZ > (-40))
				birdZ -= 1;
			if (birdY < 0)
				birdY += 1;
			else if (birdY > 0)
				birdY -= 1;
		}
	}
	
	//move to the fourth tree, and set atTree to 4 when it arrives
	if (atTree == 3) {
		if ((birdX == 19) && (birdY == 0) && (birdZ == -10)) {
			atTree = 4;
		}
		else {
			if (birdX < (-20))
				birdX += 1;
			if (birdZ < (-10))
				birdZ += 1;
			else if (birdZ > (-10))
				birdZ -= 1;

			if (birdY < 0)
				birdY += 1;
			else if (birdY > 0)
				birdY -= 1;
		}
	}

	//move to the default location, and set atTree back to 1 when it arrives
	if (atTree == 4) {
		if ((birdX == -10) && (birdY == -6) && (birdZ == -10)) {
			flying = 0;
			glutIdleFunc(NULL);
			onPath = 0;
			atTree = 1;
		}
		if ((birdX <= 19) && (birdY <= 0) && (birdZ == -10)) {
			if (birdX > -10)
				birdX -= 1;
			if (birdY > -6)
				birdY -= 1;
		}
	}
	glutPostRedisplay();
} 

//send the bird on it's path by reading the onPath global variable.
void startPath(int x) {
	if (onPath)
		birdPath();
	glutTimerFunc(pathTime, startPath, 1);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (currentView == 0) {
		glOrtho(-50, 50, -50, 50, 5, 100);
	}
	else
		glFrustum(-5, 5, -5, 5, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawImage();
	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(0.447058, 0.85098, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
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
	case '0': //overhead
		currentView = 0;
		glutPostRedisplay();
		break;
	case '1': //north
		currentView = 1;
		glutPostRedisplay();
		break;
	case '2': //east (default)
		currentView = 2;
		glutPostRedisplay();
		break;
	case '3': //south
		currentView = 3;
		glutPostRedisplay();
		break;
	case '4': //west
		currentView = 4;
		glutPostRedisplay();
		break;
	case 'f': //make the bird flap its wings
		if (flying) {
			flying = 0;
			glutIdleFunc(NULL);
		}
		else {
			flying = 1;
			glutIdleFunc(flap);
		}
		break;
	case 's': //fly the path
		onPath = 1;
		glutPostRedisplay();
		break;
	case 'r': //reset scene 
		currentView = 2;
		birdX = -11;
		birdY = -5;
		birdZ = -11;
		if (flying) {
			flying = 0;
			glutIdleFunc(NULL);
		}
		onPath = 0;
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
	if (key == GLUT_KEY_DOWN) 
		pathTime += 5;
	if (key == GLUT_KEY_UP)
		if (pathTime > 120)
			pathTime -= 5;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Press 'esc' to quit" << endl
		<< "Press the up/down arrow keys to speed up/slow down animation." << endl
		<< "Press 'r' to reset the scene" << endl
		<< "Press 's' to send the bird on it's flight path" << endl
		<< "Press 'f' to toggle the wing flapping" << endl
		<< "Press '0' to view from overhead" << endl
		<< "Press '1' to view from north" << endl
		<< "Press '2' to view from east" << endl
		<< "Press '3' to view from south" << endl
		<< "Press '4' to view from west" << endl
		<< "Press 'up' to increase flight speed along the path" << endl
		<< "Press 'down' to decrease flight speed along the path" << endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 3");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	glutTimerFunc(5, startFlying, 1);
	glutTimerFunc(5, startPath, 1);
	glutMainLoop();
	return 0;
}