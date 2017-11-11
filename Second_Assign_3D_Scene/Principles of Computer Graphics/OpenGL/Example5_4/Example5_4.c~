//#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls



void MyCube( GLfloat length, GLfloat height, GLfloat depth){
 
  // base
  glBegin(GL_POLYGON); 
    glVertex3f(-length/2, -height/2, depth/2);
    glVertex3f(-length/2, -height/2, -depth/2);
    glVertex3f(length/2, -height/2, -depth/2);
    glVertex3f(length/2, -height/2, depth/2);
	glEnd();

  // front face
  glBegin(GL_POLYGON); 
    glVertex3f(-length/2, -height/2, depth/2);
    glVertex3f(length/2, -height/2, depth/2);
    glVertex3f(length/2, height/2, depth/2);
    glVertex3f(-length/2, height/2, depth/2);
	glEnd();

  // right side face
   glBegin(GL_POLYGON); 
    glVertex3f(length/2, -height/2, depth/2);
    glVertex3f(length/2, -height/2, -depth/2);
    glVertex3f(length/2, height/2, -depth/2);
    glVertex3f(length/2, height/2, depth/2);
	glEnd();
  // back side face
   glBegin(GL_POLYGON); 
    glVertex3f(-length/2, -height/2, -depth/2);
    glVertex3f(-length/2, height/2, -depth/2);
    glVertex3f(length/2, height/2, -depth/2);
    glVertex3f(length/2, -height/2, -depth/2);
	glEnd();
  // left side face
   glBegin(GL_POLYGON); 
    glVertex3f(-length/2, -height/2, depth/2);
    glVertex3f(-length/2, height/2, depth/2);
    glVertex3f(-length/2, height/2, -depth/2);
    glVertex3f(-length/2, -height/2, -depth/2);
	glEnd();

  // top
   glBegin(GL_POLYGON); 
    glVertex3f(-length/2, height/2, depth/2);
    glVertex3f(length/2, height/2, depth/2);
    glVertex3f(length/2, height/2, -depth/2);
    glVertex3f(-length/2, height/2, -depth/2);
	glEnd();
   
}

void Display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(0,0,0);
	glEnd();
	glColor3f (1.0, 1.0, 1.0);
	glTranslatef(-1.,0.,0.);
 	MyCube(1.,1.,1.);
  	glTranslatef(2.,0.,0.);
	glutWireCube(1.);
 	glFlush();
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
 // glEnable(GL_CULL_FACE);
 // glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_LINE);
}


void main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("A Cube");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  glutMainLoop();
}
