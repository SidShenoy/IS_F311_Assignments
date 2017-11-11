//Example3_3.cpp : Smiley face on the Alps

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
BITMAPINFO *bginfo;       // Background Bitmap information 
GLubyte    *bgpixels;     // Actual background pixel data 
float       xpos, ypos;



void Display(void)
{
  if (bgpixels) {
    // set raster position to xpos and ypos
    glRasterPos2i(0,0);
    // Draw the loaded pixels
    glPixelZoom(0.5,0.8);
    glDrawPixels(bginfo->bmiHeader.biWidth,
                 bginfo->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, bgpixels);
  }
  if (pixels) {
    // set raster position to xpos and ypos
    glRasterPos2f(xpos,ypos);
    glPixelZoom(1.0,1.0);
    // Draw the loaded pixels
    glDrawPixels(info->bmiHeader.biWidth,
                 info->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
  }
  
        
  //dont wait, start flushing opengl calls to display buffer
  glFlush();
  glutSwapBuffers();

  // 120 is max Y value in our logical coordinate system
  ypos = ypos + 0.1;
  if (ypos >=   120.)
    ypos =  0;
  // Force a redisplay, unless the user has cancelled
  
    glutPostRedisplay();

// To save the image, actually we should append the filename with a sequence number
  /*
  BITMAPINFO *saveinfo;
  GLubyte * savebits = ReadBitmapFromScreen(&saveinfo); 
  SaveBitmap("F:\\CGbook\\GL\\Images\\test.bmp", saveinfo,savebits);
  */
  
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
  // initial raster position set to 0,0
  xpos = 60;
  ypos = 0;
  
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (320, 200);   
  glutCreateWindow("Displaying images");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  // read in the pixel data
  if (argc > 1)
    pixels = ReadBitmap(argv[1], &info);
  else
    pixels = ReadBitmap("..\\Images\\smiley.bmp", &info);

  if (argc > 1)
    bgpixels = ReadBitmap(argv[2], &bginfo);
  else
    bgpixels = ReadBitmap("..\\Images\\alpsbig.bmp", &bginfo);

  glutMainLoop();
}