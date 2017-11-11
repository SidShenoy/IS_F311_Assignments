//Example3_4.cpp : Using the XOR operator

#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include "..\bmp.h"

/*
 * Globals...
 */

BITMAPINFO *info;       // Bitmap information 
GLubyte    *pixels;     // Actual pixel data 
float xpos, ypos;         // x and y position for pixel data to be drawn
float prevx, prevy;       // previous x and y positions of pixel data
boolean USERCANCEL, FIRSTDISPLAY;

void Display(void)
{
 
 // 

  if (FIRSTDISPLAY) {
    // Only clear the background the first time, and set the logical operation
    glClear(GL_COLOR_BUFFER_BIT);
    FIRSTDISPLAY = FALSE;
    glEnable(GL_COLOR_LOGIC_OP);
    glLogicOp(GL_XOR);
  } else {
    // XOR to erase the previous image drawn
    glRasterPos2f(prevx,prevy);
    glDrawPixels(info->bmiHeader.biWidth,
                 info->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    } 
	// XOR image at new position
	glRasterPos2f(xpos,ypos);
	glDrawPixels(info->bmiHeader.biWidth,
                 info->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
  
        
  //dont wait, start flushing opengl calls to display buffer
  glFlush();
  glutSwapBuffers();
  prevy = ypos; prevx = xpos;
  ypos = ypos + 0.1;
  if (ypos >=   120.)
    ypos =  0;

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
  glClearColor(1.0,0.0,1.0,1.0);
  // initial raster position set to 0,0
  xpos = 60;
  ypos = 0; 
  prevx = prevy = -1;
  USERCANCEL = FALSE;
  FIRSTDISPLAY = TRUE;

  
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