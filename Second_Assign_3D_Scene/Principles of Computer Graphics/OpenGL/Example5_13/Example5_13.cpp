#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls


#include "Snowman.h"

GLint SPEED = 100;
#define MAXFRAMES = 500;


GLfloat snomanXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat botXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat tumXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat headXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat lEyeXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat rEyeXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat noseXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat lHandXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat rHandXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};


int sign = 1;




void Display(void)
{
	GLfloat ypos, xpos;
	

	snomanXforms[5] += 1*sign;
	lHandXforms[5] += 2*sign;
	rHandXforms[5] += -2*sign;
	headXforms[4] += 2*sign;
	if (snomanXforms[5] == 30) 
		sign = -1;
	else if (snomanXforms[5] == -30) 
		sign = 1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_SnowMan(snomanXforms, botXforms, tumXforms, headXforms, lEyeXforms, lEyeXforms, noseXforms, lHandXforms, rHandXforms);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();      
}

void reshape (int w, int h)
{
   	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (45., (GLfloat)w/h,1., 50.0);
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt(0,3.,10, 0,0,-100,0.,1.,0.);
}


void init(void){


  //set the clear color to be aqua-blue
	glClearColor(0.,1.,1.0,1.0);
	glColor3f(1.,1.,1.);
  
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);


  glColor3f(0.6,0.3,0.);
  glEnable(GL_DEPTH_TEST);
  
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Snowman - Take 2");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}