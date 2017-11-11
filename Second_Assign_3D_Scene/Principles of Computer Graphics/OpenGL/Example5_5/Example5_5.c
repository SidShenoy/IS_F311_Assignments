//#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls


#define PI 3.1415926535898 

void MySphere(GLfloat radius){
  
  GLdouble inc = PI/12;
  GLdouble theta, phi;
  //bool even = true;
  for (theta=-PI/2; theta<(PI/2-inc);theta+=inc){
    for (phi = 0; phi < 2*PI;phi+=inc) { 
    glBegin(GL_POLYGON); 
      glVertex3f(radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi));
      glVertex3f(radius*cos(theta+inc)*cos(phi), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi));
      glVertex3f(radius*cos(theta+inc)*cos(phi+inc), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi+inc));
      glVertex3f(radius*cos(theta)*cos(phi+inc), radius*sin(theta),radius*cos(theta)*sin(phi+inc));
    glEnd();
    }
  }  
  glFlush();
}

void Display(void)
{

	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	glTranslatef(0.,0.,-5.);
	//draw a sphere
    glTranslatef(-2,0.,0.);
	MySphere(1.5);

  // draw a sphere using builtin primitive
	glMatrixMode(GL_MODELVIEW);	
	
	glTranslatef(1, 1, 1);
	//glColor3f(COLOR_OF_LEAVES[0],COLOR_OF_LEAVES[1],COLOR_OF_LEAVES[2]);
	glutSolidSphere(2, 12, 24);
	glFlush();
	
	/*glTranslatef(4,0.,0);
	glRotatef(90,1.,0.,0.); // primitive is sliced along XY not XZ
	glutSolidSphere(1.5,24,12);

	glFlush();*/

 
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
  glClearColor(0.0,0.0,0.0,0.0);
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_LINE);
}


void main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("A Sphere");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  glutMainLoop();
}
