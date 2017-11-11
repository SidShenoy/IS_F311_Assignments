#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include "..\utils.h"




GLfloat P1[3] = {0.5,0.,0.5};
GLfloat P2[3] = {0.,0.,-0.5};
GLfloat P3[3] = {-0.5,0.,0.5};
GLfloat u[3], v[3], uv[3];




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
    

	glClear (GL_COLOR_BUFFER_BIT );
	
 
	// draw the pyramid
	myPyramid();
	glFlush();

  
}



void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-1,1,-1,1,1.,20);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.,0.,5, 0,0,-100,0.,1.,0.);
    // rotate for top view
    // glRotatef(90,1.,0.,0.);
    // rotate for side view
    //glRotatef(-90,0.,1.,0.);
	

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
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (320, 200);   
  glutCreateWindow("Displaying Orthographic views");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  glutMainLoop();
}


  





