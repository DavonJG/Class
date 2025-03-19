
//BoxAndCubesPickingAndDragging

//Example of dragging using world coordinates.

//Allows dragging of red cube, not green cube.
//Uses picking to know if clicked red cube,
//  to initiate the dragging

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//GLOBALS

bool isDragging = false;  //dragging object
GLsizei w = 0, h = 0; //width and height of the window
double xred = 2.0, yred = 0.0, zred = -5.0;

//from BallAndTorusPicking
int closestName;

static unsigned int buffer[1024]; // Hit buffer.
static int hits; // Number of entries in hit buffer.
bool isSelecting = false;

void printInteraction()
{
	cout << "Click and drag red cube" << endl;
} // end printInteraction

// Process hit buffer to find record with smallest min-z value.
// Copied (almost) exactly from BallAndTorusPicking
void findClosestHit(int hits, unsigned int buffer[])
{
	unsigned int *ptr, minZ;

	minZ = 0xffffffff; // 2^32 - 1
	ptr = buffer;
	closestName = 0;
	for (int i = 0; i < hits; i++)
	{
		ptr++;
		if (*ptr < minZ)
		{
			minZ = *ptr;
			ptr += 2;
			closestName = *ptr;
			ptr++;
		}
		else ptr += 3;
	}
} // end findClosestHit


void setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
} // end setup


void setProjection();


void resize(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	h = height;
	w = width;

	setProjection();

} //end resize

void setProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, 1, 21);


	glMatrixMode(GL_MODELVIEW);
} // end setProjection

void setPointOfView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


} // end setPointOfView

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:  //exit with escape key
		exit(0);
		break;


	} //end switch
} // end keyInput


void drawBoxAndCubes()//assemble the entire scene
	  //called by drawScene for rendering
	  //called by mousePickFunction for selecting
{
	setPointOfView();

	//red cube
	glPushMatrix();
	cout << "red location:" << xred << ", " << yred << ", " << zred << endl;
	glTranslatef(xred, yred, zred);

	if (isSelecting) glLoadName(1); // Name 1 is red cube. ***
	//draw a red cube

	glColor3f(1.0, 0.0, 0.0);

	glutSolidCube(1.0);

	glPopMatrix();

	//green cube
	glPushMatrix();
	glTranslatef(-2.0, 0.0, -15.0);
	if (isSelecting) glLoadName(2);  // Name 2 is green cube.  ***
	//draw a green cube
	glColor3f(0.0, 1.0, 0.0);

	glutSolidCube(1.0);

	glPopMatrix();

	//draw a cube
	glPushMatrix();
	glTranslatef(-9.0, -9.0, -2.0);
	glScalef(18.0, 18.0, 18.0);

	if (isSelecting) glLoadName(0); // cube doesn't count ***

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	//front face
	glColor3f(1.0, 0.0, 0.0); //red
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); //green
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 0.0); //red
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); //green
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);

	//to back face
	glColor3f(0.0, 0.0, 1.0); //blue
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -1.0);

	//back face
	glColor3f(1.0, 0.0, 0.0); //red  
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(1.0, 0.0, -1.0);

	glColor3f(0.0, 1.0, 0.0); //green  
	glVertex3f(1.0, 0.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);

	glColor3f(1.0, 0.0, 0.0); //red
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(0.0, 1.0, -1.0);

	glColor3f(0.0, 1.0, 0.0); //green
	glVertex3f(0.0, 1.0, -1.0);
	glVertex3f(0.0, 0.0, -1.0);

	glColor3f(0.0, 0.0, 1.0); //blue
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, -1.0);

	glColor3f(0.0, 0.0, 1.0); //blue
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, -1.0);

	glColor3f(0.0, 0.0, 1.0); //blue
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, -1.0);
	glEnd();
	glPopMatrix();


} // end drawBoxAndCubes

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);



	//draw the picture for real
	isSelecting = 0;
	drawBoxAndCubes();
	glutSwapBuffers();

} //end drawScene

// The mouse callback routine.
//based on BallAndTorusPicking pickFunction
void mousePickFunction(int button, int state, int x, int y)
{
	int viewport[4]; // Viewport data.

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //mouse clicked
	{
		//**
		//cout << "left button pressed" << endl;
		glGetIntegerv(GL_VIEWPORT, viewport); // Get viewport data.
		glSelectBuffer(1024, buffer); // Specify buffer to write hit records in selection mode
		(void)glRenderMode(GL_SELECT); // Enter selection mode.

		//**************  Set new viewing volume ***********
		// Save the viewing volume defined in the setProjection routine,
		// the real projection matrix for rendering
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

		// Define a viewing volume corresponding to selecting in 
		//    3 x 3 region around the cursor.
		glLoadIdentity();
		gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);

		//real projection used, copied from setProjection
		//DON'T load identity here

		glOrtho(-10, 10, -10, 10, 1, 21);

		//************** END of Set new viewing volume ***********

		//---------------  Selecting --------------
		//set up modelview for selecting
		glMatrixMode(GL_MODELVIEW); // Return to modelview mode before drawing.
		glLoadIdentity();  //I do this later, in setPointOfView

		glInitNames(); // Initializes the name stack to empty.
		glPushName(0); // Puts name 0 on top of stack.

		// Determine hits by drawing so that names are assigned.
		isSelecting = 1;
		drawBoxAndCubes();  //ALL drawing must be done
							  //NO MESSING with projection matrix

		hits = glRenderMode(GL_RENDER); // Return to rendering mode, returning number of hits.

		// Determine closest of the hit objects (if any).
		// closest object name will be saved in closestName.
		findClosestHit(hits, buffer);

		//if red cube was hit, start dragging.
		if (closestName == 1) //clicked on red cube
			isDragging = true;
		//**
		cout << "closest hit = " << closestName << endl;
		//---------------  END OF Selecting --------------

		//back to drawing mode
		// Restore viewing volume of the resize routine and return to modelview mode.
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();  //redraw for real, knowing what was hit.

	} // end if left button pressed

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) //mouse released
	{
		isDragging = false;
	}
} //end mousePickFunction


/* EXPLANATION OF TRANSFORMATION MOUSE to OBJECT
 x,y values from mouse
 screen   object
 xsc
 0 <-> -10
 w <-> 10
 xsc = x

 ysc
 0 <-> -10
 h <-> 10
 ysc = h - y

 xsc=w <-> xobj=10
 xsc=0 <-> xobj=-10
 xobj = xsc * ( (10 - -10)/(w-0) ) + -10

 ysc=h <-> yobj=10
 ysc=0 <-> yobj=-10
 yobj = ysc * ( (10 - -10)/(h-0) ) + -10

 */
void mouseMotion(int x, int y)
{
	if (isDragging)
	{
		double xsc, ysc, xobj, yobj;
		// convert to screen coords
		xsc = x;
		ysc = h - y;
		// convert to object coords
		xobj = xsc * (20.0 / w) - 10.0;
		yobj = ysc * (20.0 / h) - 10.0;

		xred = xobj;
		yred = yobj;

		glutPostRedisplay();
	} // end of dragging
} // end mouseMotion

int main(int argc, char ** const argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("two cubes with dragging");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mousePickFunction);
	glutMotionFunc(mouseMotion);
	glutMainLoop();
	return 0;
}