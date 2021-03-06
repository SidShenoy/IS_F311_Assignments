#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

void init()
{
	GLfloat light_ambient[] = {1,1,1,1};
	GLfloat light_diffuse[] = {1,1,1,1};
	GLfloat light_specular[] = {1,1,1,1};
	
	GLfloat light_position[] = {1,1,1,0.2};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(60,0,0,1);
	glutSolidCube(0.7);
	glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  //init();
  //glutMouseFunc(mouse);
  //glutMotionFunc(motion);
  //glutKeyboardFunc(keyboard);
  //glutReshapeFunc(reshape);
  //reshape(400,400);
  //glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
