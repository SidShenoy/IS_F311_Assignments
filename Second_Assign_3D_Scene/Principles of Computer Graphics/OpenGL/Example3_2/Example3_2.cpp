//example3_2.cpp : A pixmap sprite

#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>	 // Math libraries for cos and sin functions
#include "..\bmp.h"

/*
 * Globals...
 */

BITMAPINFO *info;       // Bitmap information 
GLubyte    *pixels;     // Actual pixel data 
float xpos, ypos;         // x and y position for pixel data to be drawn
float xposball;         // x for ball to be drawn


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

GLfloat RadiusOfBall = 15.;
// Draw the ball, centered at the origin
void draw_ball(float centerx, float centery) {
  glColor3f(0.6,0.3,0.);
  MyCircle2f(centerx, centery,RadiusOfBall);
  
}

void Display(void)
{
  
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2f(100,ypos);
    // Draw the loaded pixels
    glDrawPixels(info->bmiHeader.biWidth,
                 info->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
 
	draw_ball(40.,ypos);
        
  //dont wait, start flushing opengl calls to display buffer
  glFlush();
  glutSwapBuffers();

  // 120 is max Y value in our logical coordinate system
  ypos = ypos + 0.1;
  if (ypos >=   120.)
    ypos =  0;
  // Force a redisplay
 
    glutPostRedisplay();
  
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
  //set the clear color to be purple
  glClearColor(1.0,0.0,1.0,1.0);
  // initial raster position set to 0,0
  xpos = 60;
  ypos = 0; 

}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Displaying images");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  // read in the pixel data
  if (argc > 1)
    pixels = ReadBitmap(argv[1], &info);
  else
    pixels = ReadBitmap("..\\Images\\smiley.bmp", &info);

  glutMainLoop();
}