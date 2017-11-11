//Example1_4.cpp : An anti-aliased stick figure

#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls


// routine to draw a circle approximated by line segments
#define PI 3.1415926535898 
GLint circle_points = 100; 
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius){
  GLint i;
  GLdouble angle;
  glBegin(GL_POLYGON); 
  for (i = 0; i < circle_points; i++) {    
    angle = 2*PI*i/circle_points; 
    glVertex2f(centerx+radius*cos(angle), centery+radius*sin(angle)); 
  } 
  glEnd();
}


void Display(void)
{
  //clear all pixels with the specified clear color
  glClear(GL_COLOR_BUFFER_BIT);
  

  glColor3f(1.0,0.8,0.1);
  MyCircle2f(80.,85., 10.);
  // the eyes are black points 
  // set the point size to be 3.0 pixels 
  
  glBegin(GL_POINTS); 
   glColor3f(0.0, 0.0, 0.0);  
   glVertex2f(77.,88.);
   glVertex2f(83.,88.); 
  glEnd();


  // polygonal body
  glColor3f(0.8,0.0,0.9);
  glBegin(GL_POLYGON);
    glVertex2f(75.,75.);
    glVertex2f(85.,75.);
    glVertex2f(100.,30.);
    glVertex2f(60.,30.);
  glEnd();

  //rectangular legs
  glColor3f(1.0,0.8,0.1);

  glRectf(70.,5.,75.,30.);
  glRectf(85.,5.,90.,30.);


  // but lines for hands!

  glBegin(GL_LINES);
   glVertex2f (74.,70.); glVertex2f (50.,50.);
  glEnd();
  
  glBegin(GL_LINES);
   glVertex2f (86.,70.); glVertex2f (110.,50.);
  glEnd();
  //dont wait, start flushing opengl calls to display buffer
  glFlush();
}

void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   // keep our logical coordinate system constant
   gluOrtho2D(0.0, 160.0, 0.0, 120.0);

}


void init(void){
  
   glEnable (GL_LINE_SMOOTH); 
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT | GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
  

  //set the clear color to be white
  glClearColor(0.0,0.8,0.0,1.0);
  // set the point size of points drawn to be 5.0 pixels
  glPointSize(5.0);
  // set the line width to be 5.0 pixels 
  glLineWidth(5.0);
  // polygons drawn should be filled
  glPolygonMode(GL_FRONT, GL_FILL);

  
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Anti-Aliased Stick Figure");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}