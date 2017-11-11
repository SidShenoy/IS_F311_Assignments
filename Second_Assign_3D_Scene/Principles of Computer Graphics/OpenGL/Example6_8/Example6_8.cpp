#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>

#include "Shapes.h"
#include "..\bmp.h"
#include "..\vrml.h"

#define MAXSHAPES 25
#define MAXCOORDS  3000
#define XMIN -0.72
#define XMAX 0.72
#define YMIN -1
#define YMAX 1
GLfloat   coords[MAXSHAPES][3*MAXCOORDS];
GLint     indices[MAXSHAPES][3*MAXCOORDS];
GLfloat   normals[MAXSHAPES][3*MAXCOORDS];
GLint     nindices[MAXSHAPES][3*MAXCOORDS];
GLint     noofpoly[MAXSHAPES];
GLint     noofshapes;

GLubyte *bits;
BITMAPINFO *info;
static GLuint texName;


int mapping;



void Display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
 
   gluLookAt(-1.,5.,5.,0.,-20.,-50.,0.,1.,0.);

   glTranslatef(0.0, 0.0, -1);
     
   mapping = PLANAR;

   
   // Just the plane texture map
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(-3.0, 0.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-3.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(-2.0, 0.0, 0.0);
   glEnd();

   glTranslatef(-3.,1.5,-1.5);
   
   TexObject(&coords[0][0], &normals[0][0],&indices[0][0],&nindices[0][0], &(noofpoly[0]), noofshapes, 
             XMIN, XMAX, YMIN, YMAX, mapping);

   glTranslatef(2.2,0.,0.);

   TexSphere(1.,mapping);

   glTranslatef(2.2,0.,0.);
   TexCube(1.4,1.4,1.4,mapping);

   glFlush();
}

void reshape(int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glLoadIdentity();
	glFrustum (-0.3*(GLfloat)w/h,0.3*(GLfloat)w/h, -0.3,0.3, 1., 20.0);
  glMatrixMode(GL_MODELVIEW);
}



void init(void)
{    

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);



   bits = ReadBitmap("..\\Images\\checktexture.bmp", &info);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, 
                info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits);

   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
   GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glShadeModel (GL_SMOOTH);

   noofshapes = ReadVRML("..\\Models\\vase.wrl", &coords[0][0], &normals[0][0],&indices[0][0],&nindices[0][0], &(noofpoly[0]), MAXSHAPES, MAXCOORDS);  
}

void main(int argc, char** argv)
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(320, 200);
  glutCreateWindow("Planar Texture Mapping");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}