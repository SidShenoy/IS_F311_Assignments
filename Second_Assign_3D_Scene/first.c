#include<GL/glut.h>

void myinit()
{

  glColor3d(0,1,0);
}

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
    glVertex2d(0,-25);
    glVertex2d(50,-25);
    glVertex2d(50,25);
    glVertex2d(0,25);
  glEnd();
  glFlush();
}

void myReshape(int w,int h)
{
  glViewport(0,0,w,h);
  gluOrtho2D(-100,100,-75 * (GLfloat)h/(GLfloat)w,75 * (GLfloat)h/(GLfloat)w);
}

int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitWindowSize(400, 300);
  glutCreateWindow("simple");
  glutDisplayFunc(myDisplay);
  glutReshapeFunc(myReshape);
  myinit();
  glutMainLoop();
  return 0;
}
