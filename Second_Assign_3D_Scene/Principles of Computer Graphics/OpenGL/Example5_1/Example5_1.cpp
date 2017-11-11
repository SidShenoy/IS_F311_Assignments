#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls



#define PI 3.1415926535898 
GLint circle_points = 40; 
 
void MyCircle3f(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius){
  GLint i;
  GLdouble theta;
  glBegin(GL_POINTS);
 // glBegin(GL_POLYGON); 
  for (i = 0; i < circle_points; i++) {    
    theta = 2*PI*i/circle_points; 
	glColor3f(0.5*cos(theta)+0.5,0.,0.5*sin(theta)+0.5);
    glVertex3f(centerx+radius*cos(theta), centery, centerz+radius*sin(theta)); 
  } 
  glEnd();
}


void Display(void)
{

	glClear (GL_COLOR_BUFFER_BIT);


	glBegin(GL_LINES);
		glColor3f (1.0, 0.0, 0.0);
		glVertex3f(0,0.,0.);
		glVertex3f(1,0,.0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f (0.0, 1.0, 0.0);
		glVertex3f(0.,0.,0.);
		glVertex3f(0.,1,0);
	glEnd();

	glBegin(GL_LINES);
		glColor3f (0.0, 0.0, 1.0);
		glVertex3f(0.,0.,0.);
		glVertex3f(0.,0.,1.);
	glEnd();


	glPointSize(2.);
	MyCircle3f(0.,0.,0.,1);
	MyCircle3f(0.,0.5,0.,1);


	glFlush();

}




void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(60., (GLfloat)w/h, 1., 20.);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity (); 

	gluLookAt(0.2,0.2,3, 0,0,-100,0.,1.,0.);

}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,1.0);


}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("Displaying 3D shapes");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);    
  glutMainLoop();
}