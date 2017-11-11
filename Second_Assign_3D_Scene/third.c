/* Sample Code for motion behaviour (2D Dragging!) */

#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int theta = 0;
int x=0,y=0;
float size = 5;
enum ButtonState{ DOWN, UP }bstate = UP;

void idle()
{
  theta += 2;

  if(theta>360) theta-=360;
  glutPostRedisplay();
}

void drawSquare(int x,int y)
{
  glColor3f(1,1,0);
  glBegin(GL_POLYGON);
    glVertex2f(x+size,y+size);
    glVertex2f(x-size,y+size);
    glVertex2f(x-size,y-size);
    glVertex2f(x+size,y-size);
  glEnd();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  drawSquare(x,y);
  glBegin(GL_QUADS);
    /*float thetar = theta/(3.14159/180);
    glVertex2f(100+100*cos(thetar),100+100*sin(thetar));
    glVertex2f(100-100*sin(thetar),100+100*cos(thetar));
    glVertex2f(100-100*cos(thetar),100-100*sin(thetar));
    glVertex2f(100+100*sin(thetar),100-100*cos(thetar));*/
  glEnd();
  glutSwapBuffers();
	//glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 0x1B:
    case 'q':
    case 'Q':
    exit(0);
    break;
  }
}

void mouse(int button, int state, int mx, int my)
{
   if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
     exit(0);

    /*if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
      glutIdleFunc(NULL);
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
      glutIdleFunc(idle);*/
}

void motion(int mx, int my)
{
  x = mx;
  y = glutGet(GLUT_WINDOW_HEIGHT) - my;
  glutPostRedisplay();
}

void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,0,h);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(400,400);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  reshape(400,400);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
