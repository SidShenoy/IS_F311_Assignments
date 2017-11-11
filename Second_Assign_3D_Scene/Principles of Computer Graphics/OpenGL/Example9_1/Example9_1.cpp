#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include "..\linearinterpolation.h"

GLint SPEED = 100;

GLfloat KeyFrameValues[5];
GLint KeyFramePositions[5];
int currentFrame;
int NumberofKeyFrames = 3;
int MAXFRAMES = 21;




void timer(int value)
{
  
  glutPostRedisplay();      
  currentFrame++;
  if (currentFrame == MAXFRAMES)
	currentFrame = 0;
  glutTimerFunc(SPEED, timer, 0);
  
  
  

}

void Display(void)
{
	GLfloat ypos;
	glutSwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT );
  

    ypos = EvaluateLinearAt(KeyFrameValues, KeyFramePositions, NumberofKeyFrames, currentFrame);
    
	glLoadIdentity ();
	gluLookAt(0.,0.,13, 0,0,-100,0.,1.,0.);
    glTranslatef(0.,ypos,0.);
    glutWireSphere(.5,10,10);

	glFlush();
	
}

void reshape (int w, int h)
{
   
   
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	glFrustum (-.5*(GLfloat)w/h,.5*(GLfloat)w/h, -0.2, 0.8,1., 200.0);
    glMatrixMode (GL_MODELVIEW);
	gluLookAt(0.,0.,5, 0,0,-100,0.,1.,0.);


}


void init(void){

	currentFrame = 0;

  //set the clear color to be white
  glClearColor(1.,1.,1.0,1.0);
  

  KeyFramePositions[0] = 0;
  KeyFramePositions[1] = 10;
  KeyFramePositions[2] = 20;

  KeyFrameValues[0] = 0;
  KeyFrameValues[1] = 10;
  KeyFrameValues[2] = 0;

  glutTimerFunc(SPEED, timer, 0);
  glColor3f(0.6,0.3,0.);
  
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Bouncing Ball");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}