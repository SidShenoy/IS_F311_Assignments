#include <windows.h> //the windows include file, required by all windows applications
 
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include "..\utils.h"  




void Display(void)
{

	GLfloat P1[3] = {0.5,0.,0.5};
	GLfloat P2[3] = {0.,0.,-0.5};
	GLfloat P3[3] = {-0.5,0.,0.5};
	
	GLfloat u[3], v[3], uv[3];

	glClear (GL_COLOR_BUFFER_BIT);

/*
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

*/
	vecsub(P1,P2,u);
	vecsub(P1,P3,v);
	crossproduct(u,v,uv);

	glColor3f (1.0, 1.0, 1.0);
	glPointSize(5.);

	glBegin(GL_POINTS);	
		glVertex3fv(P1);
		glVertex3fv(P2);
		glVertex3fv(P3);
		glVertex3fv(uv);
	glEnd();


	glBegin(GL_LINES);
		glVertex3fv(uv);
		glVertex3fv(P1);
	glEnd();

	glBegin(GL_LINES);
		glVertex3fv(uv);
		glVertex3fv(P2);
	glEnd();

	glBegin(GL_LINES);
		glVertex3fv(uv);
		glVertex3fv(P3);
	glEnd();

	glBegin(GL_LINES);
		glVertex3fv(P2);
		glVertex3fv(P1);
	glEnd();

	glBegin(GL_LINES);
		glVertex3fv(P3);
		glVertex3fv(P2);
	glEnd();

	glBegin(GL_LINES);
		glVertex3fv(P1);
		glVertex3fv(P3);
	glEnd();
		
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