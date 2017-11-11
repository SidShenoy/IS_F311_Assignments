#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include "..\cubicinterpolation.h"

GLint SPEED = 100;

GLfloat KeyFrameValues[9];
GLint KeyFramePositions[9];
GLfloat KeyFrameXPosValues[9];


int currentFrame;
int NumberofKeyFrames = 9;
int MAXFRAMES = 81;




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
	GLfloat ypos, xpos;
	glutSwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT );
  

    ypos = EvaluateCubicAt(KeyFrameValues, KeyFramePositions, NumberofKeyFrames, currentFrame);
	xpos = EvaluateCubicAt(KeyFrameXPosValues, KeyFramePositions, NumberofKeyFrames, currentFrame);
    glLoadIdentity ();
	gluLookAt(0.,0.,13, 0,0,-100,0.,1.,0.);
    glTranslatef(xpos,ypos,0.);

    glutWireSphere(.5,10,10);

	glFlush();
}

void reshape (int w, int h)
{
   	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	glFrustum (-.1*(GLfloat)w/h,.9*(GLfloat)w/h, -0.2, 0.8,1., 200.0);
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
  KeyFramePositions[3] = 30;
  KeyFramePositions[4] = 40;
  KeyFramePositions[5] = 50;
  KeyFramePositions[6] = 60;
  KeyFramePositions[7] = 70;
  KeyFramePositions[8] = 80;

  KeyFrameValues[0] = 0;
  KeyFrameValues[1] = 10;
  KeyFrameValues[2] = 0;
  KeyFrameValues[3] = 7;
  KeyFrameValues[4] = 0;
  KeyFrameValues[5] = 4;
  KeyFrameValues[6] = 0;
  KeyFrameValues[7] = 1;
  KeyFrameValues[8] = 0;

  KeyFrameXPosValues[0] = 0;
  KeyFrameXPosValues[1] = 3.5;
  KeyFrameXPosValues[2] = 6;
  KeyFrameXPosValues[3] = 8;
  KeyFrameXPosValues[4] = 9.5;
  KeyFrameXPosValues[5] = 11;
  KeyFrameXPosValues[6] = 12;
  KeyFrameXPosValues[7] = 12.5;
  KeyFrameXPosValues[8] = 13;


  glutTimerFunc(SPEED, timer, 0);
  glColor3f(0.6,0.3,0.);
  
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Bouncing Ball - Take 2");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}