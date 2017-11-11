#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>



void Display(void)
{
 
 
  glClear (GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT );
  // ambient material color set to red in the init function
 
  glutSolidSphere(2., 40,32);
  glFlush();
  
}



void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	glFrustum (-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.5, 0.5, 1., 40.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.,0.,5, 0,0,-100,0.,1.,0.);
    
}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel (GL_SMOOTH);

  GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
  glEnable(GL_LIGHTING);

  GLfloat mat_ambient[] = { 1, 0.0, 0.0, 1.0 };
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

  glEnable(GL_DEPTH_TEST);

  
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (320, 200);   
  glutCreateWindow("Rendering 3D shapes");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}