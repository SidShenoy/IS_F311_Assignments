#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include "..\vrml.h"

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
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	glLoadIdentity (); 
	glTranslatef(0.,1.,-5.);
	int i,j;
	glRotatef(-15,0,1.,0);
	/*
	for (j=0;j<noofshapes;j++) {
		 for (i=0;i<noofpoly[j]*3;i=i+3) {
		
     glBegin(GL_TRIANGLES);
      glVertex3f(coords[j][3*indices[j][i]], coords[j][3*indices[j][i]+1], coords[j][3*indices[j][i]+2]);
			glVertex3f(coords[j][3*indices[j][i+1]], coords[j][3*indices[j][i+1]+1], coords[j][3*indices[j][i+1]+2]);
      glVertex3f(coords[j][3*indices[j][i+2]], coords[j][3*indices[j][i+2]+1], coords[j][3*indices[j][i+2]+2]);
    
      glVertex3fv(&(coords[j][3*indices[j][i]]));
			glVertex3fv(&(coords[j][3*indices[j][i+1]]));
			glVertex3fv(&(coords[j][3*indices[j][i+2]]));
		glEnd();
		}
    */
	for (j=0;j<noofshapes;j++) {
		for (i=0;i<noofpoly[j]*3;i=i+3) {
			glBegin(GL_TRIANGLES);
			glVertex3fv(&(coords[j][3*indices[j][i]]));
			glVertex3fv(&(coords[j][3*indices[j][i+1]]));
			glVertex3fv(&(coords[j][3*indices[j][i+2]]));
		glEnd();
	}}

	//	glVertexPointer(3,GL_FLOAT, 0, &(coords[j][0]));
	//	glDrawElements(GL_TRIANGLES, noofpoly[j]*3, GL_UNSIGNED_INT,indices[j]); 

	glFlush();

}




void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.5, 0.5, 1., 40.0);
  //gluPerspective(60., (GLfloat)w/h, 1., 40.);
	glMatrixMode (GL_MODELVIEW);

}


void init(void){
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,1.0);
 // glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT, GL_LINE);
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("Displaying 3D shapes");

  
  noofshapes = ReadVRML("..\\Models\\robot.wrl", &coords[0][0], &normals[0][0],&indices[0][0],&nindices[0][0], &(noofpoly[0]), MAXSHAPES, MAXCOORDS);
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}