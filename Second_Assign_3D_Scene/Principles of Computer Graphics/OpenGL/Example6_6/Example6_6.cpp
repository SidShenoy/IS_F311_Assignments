#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>

#include "snowman.h"
#include "..\bmp.h"


GLfloat spin = 0;
boolean     USERCANCEL, FIRSTTIME;


BITMAPINFO *bginfo;       // Background Bitmap information 
GLubyte    *bgpixels;     // Actual background pixel data 

GLfloat sXforms[9] = {0.,0.,0.,0.,45.,0.,1.,1.,1.};
GLfloat allXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};

void draw_Ground(){
	GLfloat mat_ambient[] = { 1,1,1, 1.0 };
	GLfloat snow_diffuse[] = {1,1,1,1.};
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, snow_diffuse);
	glPushMatrix();
	glTranslatef(0.,-5.5,0.);
	glScalef(25.,10.,10.);
	glutSolidCube(1.);
	glPopMatrix();
}


void Display(void)
{
 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// raster position of image (view coordinates)
	glRasterPos3i(-8,0.,-2.);
    // Draw the loaded pixels
    glPixelZoom(1,1.2);
    glDrawPixels(bginfo->bmiHeader.biWidth,
                 bginfo->bmiHeader.biHeight,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, bgpixels);
	
	
  draw_Ground();
  draw_SnowMan(sXforms, allXforms, allXforms, allXforms, allXforms, allXforms, allXforms, allXforms, allXforms);

  glFlush();
 
  
}


void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (45., (GLfloat)w/h,1., 50.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
	glPixelZoom(1,1.);
	glRasterPos3i(0,0.,-0.);
	GLfloat light1_position[] = { -1., -1.0, 0., 0.0 };
	glLightfv (GL_LIGHT1, GL_POSITION, light1_position);
	
	GLfloat light_position[] = { 1., 1.0, 1., 0.0 };
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light2_position[] = { 0., 1.0, 0., 0.0 };
	glLightfv (GL_LIGHT2, GL_POSITION, light2_position);


	gluLookAt(0,3.,10, 0,0,-100,0.,1.,0.);

  
    
}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel (GL_SMOOTH);
  USERCANCEL = FALSE;

  

  GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
  GLfloat light0_specular[] = { 0.2, 0.2, 0.2, 1.0 };

  GLfloat light1_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  GLfloat light1_diffuse[] = { 0.4, 0.4, 0.5, 1.0 };

  GLfloat light2_diffuse[] = { 1,1,1, 1.0 };


    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

//	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

    glEnable(GL_DEPTH_TEST);

	bgpixels = ReadBitmap("..\\Images\\alpsbig.bmp", &bginfo);
   
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (640, 400);   
  glutCreateWindow("Snowy on the Alps");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}