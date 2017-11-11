#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>


float Tz = -2;
float Tinc = 0.1;


void Display(void)
{
 
  

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  Tz = Tz + Tinc;

  if (Tz > 5)
    Tinc = -0.1;
  if (Tz < -5)
    Tinc = 0.1;


  glLoadIdentity();
  gluLookAt(0.,0.,10, 0,0,-100,0.,1.,0.);
  glRotatef(-90,1,0,0);
  {
    glColor3f(1.,0.,0.);
    glutSolidSphere(2., 12,12);
  }
  {
    glColor3f(0.,1.,0.);
    glTranslatef(0.,Tz,0);
    glutSolidCone(3.,2.,8,8);
  }

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
	  glFrustum (-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.5, 0.5, 1., 40.0);
    glMatrixMode (GL_MODELVIEW);
    
    
}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel (GL_SMOOTH);
// glEnable(GL_DEPTH_TEST); 

}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (640, 400);   
  glutCreateWindow("3D shapes: Hidden surface removal");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}