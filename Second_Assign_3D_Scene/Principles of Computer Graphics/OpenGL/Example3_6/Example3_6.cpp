//Example3_6.cpp: Red-Eye removal
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

float       xpos, ypos;


GLubyte *pixel_row;
float alpha;

void Display(void)
{
	int col,row;
	
  glRasterPos2i(0,0);
 

	// length of each row - 
	//remember that the color component values are padded to a 32 bit value

  int length = (info->bmiHeader.biWidth * 3 + 3) & ~3;    
  // for each row
  for (row=0; row < info->bmiHeader.biHeight; row++) {
    pixel_row = pixels + row*length;
    for (col=0; col< info->bmiHeader.biWidth; col++, pixel_row+=3) {
		if (pixel_row[0] == 0 && pixel_row[1] == 0 && pixel_row[2] == 255){
			pixel_row[0] = 255; pixel_row[2] = 0;
		}
	}
  }
  

  glRasterPos2f(xpos,ypos);
 
  glDrawPixels(info->bmiHeader.biWidth,
               info->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
       
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

  glClearColor(0.0,0.8,0.0,1.0);
  glEnable(GL_BLEND);
  // initial raster position set to 0,0
  xpos = 0;
  ypos = 0;
  alpha = 1.;
  
  
}


void main(int argc, char* argv[])
{
  GLubyte *pptr, *aptr;
  int x,y;
 
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize (256, 256);   
  glutCreateWindow("Displaying images");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);



  // read in the pixel data
  if (argc > 1)
    pixels = ReadBitmap(argv[1], &info);
  else
    pixels = ReadBitmap("..\\Images\\smiley_redeyes.bmp", &info);
  
  glutMainLoop();
}