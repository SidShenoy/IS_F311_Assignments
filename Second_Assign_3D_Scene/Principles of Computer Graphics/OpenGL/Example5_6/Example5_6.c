//#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls



#define PI 3.1415926535898 
GLint circle_points = 40; 
void MyCone(GLfloat radius, GLfloat height){
  GLint i;
  GLdouble theta, ntheta;
  for (i = 0; i < circle_points; i++) {  
	glBegin(GL_POLYGON); 
		theta = (2*PI*i/circle_points); 
		ntheta = (2*PI*(i+1)/circle_points);
		glVertex3f(radius*cos(theta), 0, radius*sin(theta));
		glVertex3f(0, height, 0);
		glVertex3f(radius*cos(ntheta), 0, radius*sin(ntheta));
	glEnd();

  }  
}

void Display(void)
{

	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	glTranslatef(-1,0.,0.);
	MyCone(0.5, 1.);

	glTranslatef(2,0,0);
	glRotatef(-90,1.,0.,0.);
	glutSolidCone(0.5,1,40,10);

	glFlush();

}




void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.5,0.5, 1., 20.0);
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity (); 

	gluLookAt(0.2,0.2,3, 0,0,-100,0.,1.,0.);

}


void init(void){
  
  //set the clear color to be black
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_LINE);

}


void main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("A Cone");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);    
  glutMainLoop();
}
