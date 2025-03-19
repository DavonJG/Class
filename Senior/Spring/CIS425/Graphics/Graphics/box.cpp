/////////////////////////////////
// boxV6.cpp
//
// This program draws a wire box.
// and a sphere.
// 0: original location
// 1: translate both jointly
// 2: rotate both jointly
// 3: to translate and rotate both jointly
//
// Sumanta Guha/Marjory Baruch
/////////////////////////////////

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
static char transformationChoice = '0';
static int isModified = 0, otherMod = 0;
static int mainWindow, menuWindow; // Window identifiers.

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	// Modeling transformations.
	glTranslatef(0.0, 0.0, -15.0);

	if (transformationChoice == '0') //original location
	{
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}

	if (transformationChoice == '1')  //translate both
	{
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(5.0, 0.0, 0.0);  //apply to both
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}

	if (transformationChoice == '2') //rotate both
	{
		glColor3f(0.0, 0.0, 0.0);
		glRotatef(45.0, 0.0, 0.0, 1.0);  //apply to both
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}

	if (transformationChoice == '3')
	{
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(5.0, 0.0, 0.0);     //apply to both
		glRotatef(45.0, 0.0, 0.0, 1.0);  //apply to both
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}


	glFlush();
}

void drawScene2(void)
{
	glutSetWindow(menuWindow);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	// Modeling transformations.
	glTranslatef(0.0, 0.0, -15.0);

	if (transformationChoice == '0') //original location
	{
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}

	if (transformationChoice == '1')  //translate both
	{
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(5.0, 0.0, 0.0);  //apply to both
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}

	if (transformationChoice == '2') //rotate both
	{
		glColor3f(0.0, 0.0, 0.0);
		glRotatef(45.0, 0.0, 0.0, 1.0);  //apply to both
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}

	if (transformationChoice == '3')
	{
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(5.0, 0.0, 0.0);     //apply to both
		glRotatef(45.0, 0.0, 0.0, 1.0);  //apply to both
		glutWireCube(5.0);
		glTranslatef(0.0, 10.0, 0.0);
		glutWireSphere(2.0, 10, 8);
	}


	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	//glOrtho(-20,20,-20,20,5,100);

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

	case '0':
		transformationChoice = '0';
		glutPostRedisplay();
		break;

	case '1':
		transformationChoice = '1';
		glutPostRedisplay();
		break;
	case '2':
		transformationChoice = '2';
		glutPostRedisplay();
		break;
	case '3':
		transformationChoice = '3';
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
	cout << "Press 0 for original location." << endl;
	cout << "Press 1 to translate both jointly." << endl;
	cout << "Press 2 to rotate both jointly." << endl;
	cout << "Press 3 to translate and rotate both jointly." << endl;
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("boxV6.cpp");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	printInteraction();
	glutMainLoop();

	menuWindow = glutCreateWindow("menuWindow");
	setup();
	glutDisplayFunc(drawScene2);
	return 0;
}
