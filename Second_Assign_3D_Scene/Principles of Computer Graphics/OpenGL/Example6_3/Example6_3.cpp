#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>

#include "snowman.h"


GLfloat spin = 0;
boolean     USERCANCEL, FIRSTTIME;
GLfloat light_position[] = { 0., 0.0, -1., 0.0 };



GLfloat snomanXforms[9] = {0.,0.,0.,0.,45.,0.,1.,1.,1.};
GLfloat botXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat tumXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat headXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat lEyeXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat rEyeXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat noseXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat lHandXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat rHandXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};

void Display(void)
{
 
	
  
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  spin ++;
	glPushMatrix ();
	glRotatef ( spin, 0.0, 1.0, 0.0);
   // rotate light around the sphere
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix ();
  
draw_SnowMan(snomanXforms, botXforms, tumXforms, headXforms, lEyeXforms, lEyeXforms, noseXforms, lHandXforms, rHandXforms);

  glFlush();
  glutSwapBuffers();
  
  glutPostRedisplay();
  
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

	
    gluLookAt(0,3.,10, 0,0,-100,0.,1.,0.);



    
    
}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel (GL_SMOOTH);
  USERCANCEL = FALSE;

	GLfloat mat_ambient[] = { 0.1, 0.1, 0.2, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);


  GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
 // GLfloat light_specular[] = { 0., 0., 0., 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  //  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
   
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (640, 400);   
  glutCreateWindow("Snowman Specular+Diffuse");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}