///////////////////////////////////////////////////////////////////////////////////////          
// animal.cpp
//
// 
//
// 
/////////////////////////////////////////////////////////////////////////////////////// 

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
static float R = 3.0; // Radius of head.
static int v = 6; // Number of longitudinal (verticle) slices.
static int h = 4; // Number of latitudinal (horizontal) slices 
                  //on hemisphere.
static float cx=3.0, cy=3.0, cz=-10.0;  //center of sphere - head 

static float necklength = 2.0;
static float nx, ny; //x and y components of neck, computed
static float neckAngle=PI/6.0;

static float torso=10.0; //length of body
static float girth=5.0;  //thickness of body
static float URx, URy; //upper right corner of body, computed


static float legx=3.0, legy=5.0; //x and y component of leg.
                  //use + or - legy for forward or backward step

static float tailx=5.0, taily=1.0; //x and y component of tail



void drawHead()
{
  int i, j;
  // Based on hemisphere.cpp from Guha
  // cx, cy,cz is the center of the sphere, R is the radius.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 0.0);
  
  for(j = 0; j < h; j++)
  {
    // One latitudinal triangle strip. top half
    glBegin(GL_TRIANGLE_STRIP);
    for(i = 0; i <= v; i++)
    {
      glVertex3f( R * cos( (float)(j+1)/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI )+cx,
                 R * sin( (float)(j+1)/h * PI/2.0 )+cy,
                 R * cos( (float)(j+1)/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI )+cz );
      glVertex3f( R * cos( (float)j/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI  )+cx,
                 R * sin( (float)j/h * PI/2.0  )+cy,
                 R * cos( (float)j/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI)+cz );         
    }
    glEnd();
    // One latitudinal triangle strip. bottom half
    glBegin(GL_TRIANGLE_STRIP);
    for(i = 0; i <= v; i++)
    {
      glVertex3f( R * cos( (float)(j+1)/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI )+cx,
                 -1*R * sin( (float)(j+1)/h * PI/2.0 )+cy,
                 R * cos( (float)(j+1)/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI )+cz );
      glVertex3f( R * cos( (float)j/h * PI/2.0 ) * cos( 2.0 * (float)i/v * PI  )+cx,
                 -1*R * sin( (float)j/h * PI/2.0  )+cy,
                 R * cos( (float)j/h * PI/2.0 ) * sin( 2.0 * (float)i/v * PI)+cz );         
    }
    glEnd();
  }
}

void drawStickNeck()
{
  //
  glLineWidth(5.0);
  glColor3f(0.6,0.4,0.6);
  nx=necklength*cos(neckAngle); //forward component of neck
  ny=necklength*cos(neckAngle); //up component of neck
  URx=cx+R*cos(PI+neckAngle)-nx; //upper right x coord of body
                                 // = lower left coord of neck
  URy=cy+R*sin(PI+neckAngle)-ny; //upper right y coord of body
  glBegin(GL_LINES);
  glVertex3f(cx+R*cos(PI+neckAngle),cy+R*sin(PI+neckAngle),cz);
  glVertex3f(URx,URy,cz);
  glEnd();
  glLineWidth(1.0);  //restore width and color
  glColor3f(0.0,0.0,0.0);
}

void drawRectBody()
{
  glLineWidth(1.0);
  glColor3f(0.0,1.0,0.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_POLYGON);
  glVertex3f(URx,URy,cz);      //upper right corner of body
  glVertex3f(URx-torso,URy,cz);
  glVertex3f(URx-torso,URy-girth,cz);
  glVertex3f(URx,URy-girth,cz);
  glEnd();
  glLineWidth(1.0);  //restore width and color
  glColor3f(0.0,0.0,0.0);
  
}


void drawTail()
{
  glLineWidth(2.0);
  glColor3f(0.3,0.3,1.0);
  glBegin(GL_LINES);
  glVertex3f(URx-torso,URy,cz);
  glVertex3f(URx-torso-tailx,URy+taily,cz);
  glEnd();
  glLineWidth(1.0);  //restore width and color
  glColor3f(0.0,0.0,0.0);
}


void drawStickLegs()
{
  glLineWidth(5.0);
  glColor3f(1.0,0.3,0.7);
  glBegin(GL_LINES);
  //two front legs
  glVertex3f(URx,URy-girth,cz); //at bottom right of body
  glVertex3f(URx+legx,URy-girth-legy,cz);//front forward
  glVertex3f(URx,URy-girth,cz); //at bottom right of body
  glVertex3f(URx-legx,URy-girth-legy,cz);//front backward
  //two back legs
  glVertex3f(URx-torso,URy-girth,cz); //at bottom left of body
  glVertex3f(URx-torso+legx,URy-girth-legy,cz);//back forward
  glVertex3f(URx-torso,URy-girth,cz); //at bottom left of body
  glVertex3f(URx-torso-legx,URy-girth-legy,cz);//back backward
  
  glEnd();
  glLineWidth(1.0);  //restore width and color
  glColor3f(0.0,0.0,0.0);
}

void drawAnimal()
{
  drawHead();
  drawStickNeck();
  drawRectBody();
  drawTail();
  drawStickLegs();
}

// Drawing routine.
void drawScene(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  
  //draw animal
  drawAnimal();
  
  glFlush();
}

// Initialization routine.
void setup(void) 
{
  //white background
  glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-20.0, 20.0, -20.0, 20.0, 0.0,20.0);
  
  glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
  switch(key) 
  {
    case 27:
      exit(0);
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
  
}

// Main routine.
int main(int argc, char **argv) 
{
  printInteraction();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100); 
  glutCreateWindow("A Person");
  setup(); 
  glutDisplayFunc(drawScene); 
  glutReshapeFunc(resize);  
  glutKeyboardFunc(keyInput);
  glutMainLoop(); 
  
  return 0;  
}


