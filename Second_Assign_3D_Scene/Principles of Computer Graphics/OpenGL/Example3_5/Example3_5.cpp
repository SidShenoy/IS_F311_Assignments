//Example3_5 Compositing Images
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
BITMAPINFO *maskinfo;       // Bitmap information 
GLubyte    *maskpixels;     // Actual pixel data 
BITMAPINFO *bginfo;       // Background Bitmap information 
GLubyte    *bgpixels;     // Actual background pixel data 
float       xpos, ypos;
boolean     USERCANCEL, FIRSTTIME;

void Display(void)
{
  if (bgpixels) {
    // First copy background image into frame buffer
    glLogicOp(GL_COPY);
    glRasterPos2i(0,0);
    // Draw the loaded pixels
    glPixelZoom(0.5,0.8);
    glDrawPixels(bginfo->bmiHeader.biWidth,
                 bginfo->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, bgpixels);
  }
  // perform an AND with destination and NOT(source)
  glLogicOp(GL_AND_INVERTED);
  glRasterPos2f(xpos,ypos);
  glPixelZoom(1.0,1.0);
  glDrawPixels(maskinfo->bmiHeader.biWidth,
               maskinfo->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, maskpixels);

  // Perform an OR with source
  glLogicOp(GL_OR);
  glDrawPixels(info->bmiHeader.biWidth,
               info->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
 

        
  //dont wait, start flushing opengl calls to display buffer
  glFlush();
  glutSwapBuffers();
  
  ypos = ypos + 0.1;
  if (ypos >=   120.)
    ypos =  0;
  glFinish();

 
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
  //set the clear color to be white
  glClearColor(0.0,0.8,0.0,1.0);
  glEnable(GL_COLOR_LOGIC_OP);
  // initial raster position set to 0,0
  xpos = 60;
  ypos = 0;
  USERCANCEL = FALSE;
  FIRSTTIME = TRUE;
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("Displaying images");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
 
  // read in the pixel data
  if (argc > 1)
    pixels = ReadBitmap(argv[1], &info);
  else
    pixels = ReadBitmap("F:\\CGbook\\GL\\Images\\smiley.bmp", &info);
  maskpixels = ReadBitmap("F:\\CGbook\\GL\\Images\\smileymask.bmp", &maskinfo);

  if (argc > 1)
    bgpixels = ReadBitmap(argv[2], &bginfo);
  else
    bgpixels = ReadBitmap("F:\\CGbook\\GL\\Images\\alpsbig.bmp", &bginfo);
  
  glutMainLoop();
}