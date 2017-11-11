//#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include "../utils.h"

GLfloat P1[3] = {0.5,0.,0.5};
GLfloat P2[3] = {0.,0.,-0.5};
GLfloat P3[3] = {-0.5,0.,0.5};
GLfloat u[3], v[3], uv[3];

GLfloat ang = 0;

void myPyramid(){
	
	glColor3f (1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3fv(P1);
		glVertex3fv(uv);
		glVertex3fv(P3);
	glEnd();

	glColor3f (0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3fv(P1);
		glVertex3fv(P2);
		glVertex3fv(uv);
	glEnd();

	glColor3f (0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3fv(P3);
		glVertex3fv(uv);
		glVertex3fv(P2);
	glEnd();

	glColor3f (1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3fv(P3);
		glVertex3fv(P2);
		glVertex3fv(P1);
	glEnd();
}

void Display(void)
{
    // swap the buffers
	glutSwapBuffers();

	glClear (GL_COLOR_BUFFER_BIT );
	glColor3f (1.0, 1.0, 1.0);

	glLoadIdentity ();
	// translate pyramid back by 4 units, and down by 1 unit
	glTranslatef(0.,-1.,-4);
	// scale pyramid 
	 glScalef(2.,2.,1.);

	// rotate the pyramid
	glRotatef(ang,0.,1.,0.);

	if (ang >=360) ang = 0; else ang++;
	// draw the pyramid
	myPyramid();
	glFlush();
	glutPostRedisplay();   
  
}




void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., (GLfloat)w/h, 1., 20.);
    glMatrixMode (GL_MODELVIEW);
	
	

}


void init(void){
  
  //set the clear color to be black
   glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_FILL);

	vecsub(P1,P2,u);
	vecsub(P1,P3,v);
	crossproduct(u,v,uv);

}


void main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("Displaying 3D shapes");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  glutMainLoop();
}
