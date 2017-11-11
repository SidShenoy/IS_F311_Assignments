//Example1_1.cpp : a simple example to open a window

#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls


void Display(void)
{
  //clear all pixels with the specified clear color
  glClear(GL_COLOR_BUFFER_BIT);
  //dont wait, start flushing opengl calls to display buffer
  glFlush();
}

void init(void){
  //set the clear color to be red
  glClearColor(1.0,0.0,0.0,1.0);
  // set the viewport to be 320 by 240, the initial size of the window
  glViewport(0,0,320,240);
  // set the 2D clipping area
  gluOrtho2D(0.0, 160.0, 0.0, 120.0);
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("My First OpenGL Window");
  init();
  glutDisplayFunc(Display);
  glutMainLoop();
}
