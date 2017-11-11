#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>


#include "..\vrml.h"

GLfloat spin = 0;
GLfloat light_position[] = { 0., 10.0, 10., 1.0 };


#define MAXSHAPES 25
#define MAXCOORDS  3000
GLfloat   coords[MAXSHAPES][3*MAXCOORDS];
GLint     indices[MAXSHAPES][3*MAXCOORDS];
GLfloat   normals[MAXSHAPES][3*MAXCOORDS];
GLint     nindices[MAXSHAPES][3*MAXCOORDS];
GLint     noofpoly[MAXSHAPES];
GLint     noofshapes;


void Display(void)
{
 
  
  spin = spin+1;
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
	
  glPushMatrix ();
   glRotatef ( spin, 0.0, 1.0, 0.0);
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);
  glPopMatrix ();
	int i,j;
  glPushMatrix ();
  glTranslatef(0.,1.,-5.);
	glRotatef(-15,0,1.,0);
	for (j=0;j<noofshapes;j++) {
    for (i=0;i<noofpoly[j]*3;i=i+3) {
     glBegin(GL_TRIANGLES);
	    glNormal3fv(&(normals[j][3*nindices[j][i]]));
      glVertex3fv(&(coords[j][3*indices[j][i]]));
      glNormal3fv(&(normals[j][3*nindices[j][i+1]]));
	    glVertex3fv(&(coords[j][3*indices[j][i+1]]));
      glNormal3fv(&(normals[j][3*nindices[j][i+2]]));
	    glVertex3fv(&(coords[j][3*indices[j][i+2]]));
     glEnd();
    }
    /*
		glVertexPointer(3,GL_FLOAT, 0, &(coords[j][0]));
		glNormalPointer(GL_FLOAT, 0, &normals[j][0]);
		glDrawElements(GL_TRIANGLES, noofpoly[j]*3, GL_UNSIGNED_INT,indices[j]); */
  }
  glPopMatrix ();
  glFlush();
  glutSwapBuffers();

}

int SPEED = 50;

void timer(int value)
{
  glutPostRedisplay();
  glutTimerFunc(SPEED, timer, 0);
}


void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	  glFrustum (-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.5, 0.5, 1., 40.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    

   // gluLookAt(0.,2.,5, 0,0,-100,0.,1.,0.);

    
    
}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
//  glEnableClientState(GL_VERTEX_ARRAY);
//  glEnableClientState(GL_NORMAL_ARRAY);
  //glShadeModel (GL_FLAT);

  GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
  GLfloat mat_diffuse[] = { 0.9,0.9,0.3,1.};
  GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat low_shininess[] = { 20 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

  GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0 };
    
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
  


  noofshapes = ReadVRML("..\\Models\\robot.wrl", &coords[0][0], &normals[0][0],&indices[0][0],&nindices[0][0], &(noofpoly[0]), MAXSHAPES, MAXCOORDS);

}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize (640, 400);   
  glutCreateWindow("Rendering Andy");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutTimerFunc(SPEED, timer, 0);
  glutMainLoop();

 }
