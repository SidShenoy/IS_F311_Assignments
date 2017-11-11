//Example1_2.cpp : let the drawing begin

#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls


void Display(void)
{
  //clear all pixels with the specified clear color
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POINTS); 
   glColor3f(0.0, 1.0, 0.0);                  /* green */ 
   glVertex2f(10.,10.); 
   glColor3f(1.0, 1.0, 0.0);                  /* yellow */ 
   glVertex2f(10.,110.); 
   glColor3f(0.0, 0.0, 1.0);                  /* blue */ 
   glVertex2f(150.,110.); 
   glColor3f(1.0, 1.0, 1.0);                  /* white */ 
   glVertex2f(150.,10.); 
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
  //set the clear color to be red
  glClearColor(1.0,0.0,0.0,1.0);
  // set the point size to be 3.0 pixels 
  glPointSize(5.0);
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("My First OpenGL Window");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}

