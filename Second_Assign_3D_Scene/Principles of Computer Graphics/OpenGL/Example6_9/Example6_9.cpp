#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>

#include "Shapes.h"
#include "..\bmp.h"
#include "..\vrml.h"

#define MAXSHAPES 25
#define MAXCOORDS  3000
#define XMIN -0.6
#define XMAX 0.6
#define YMIN -.6
#define YMAX .6
GLfloat   coords[MAXSHAPES][3*MAXCOORDS];
GLint     indices[MAXSHAPES][3*MAXCOORDS];
GLfloat   normals[MAXSHAPES][3*MAXCOORDS];
GLint     nindices[MAXSHAPES][3*MAXCOORDS];
GLint     noofpoly[MAXSHAPES];
GLint     noofshapes;

GLubyte *bits1, *bits2, *bits3, *bits4, *bits5, *bits6;
BITMAPINFO *info1, *info2, *info3, *info4, *info5, *info6;
static GLuint texName[6];




void Display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
 
   gluLookAt(-1.,5.,5.,0.,-20.,-50.,0.,1.,0.);

   glTranslatef(-3.,1.5,-2.5);
   
   TexObject(&coords[0][0], &normals[0][0],&indices[0][0],&nindices[0][0], &(noofpoly[0]), noofshapes, 
             XMIN, XMAX, YMIN, YMAX);

   glTranslatef(2.2,0.,0.);
   TexSphere(1.);

   glTranslatef(2.2,0.,0.);
   TexCube(1.4,1.4,1.4);

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

void SetTexParams(){
  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
}


void init(void)
{    

   glClearColor (1, 1, 1.0, 0.0);
   glEnable(GL_DEPTH_TEST);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(6, texName);
   glBindTexture(GL_TEXTURE_2D, texName[0]);
    SetTexParams();
   bits1 = ReadBitmap("..\\Images\\top.bmp", &info1);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info1->bmiHeader.biWidth, 
                info1->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits1);

   
   glBindTexture(GL_TEXTURE_2D, texName[1]);
   SetTexParams();
   bits2 = ReadBitmap("..\\Images\\bottom.bmp", &info2);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info2->bmiHeader.biWidth, 
                info2->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits2);

   glBindTexture(GL_TEXTURE_2D, texName[2]);
   SetTexParams();
   bits3 = ReadBitmap("..\\Images\\front.bmp", &info3);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info3->bmiHeader.biWidth, 
                info3->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits3);

   glBindTexture(GL_TEXTURE_2D, texName[3]);
   SetTexParams();
   bits4 = ReadBitmap("..\\Images\\back.bmp", &info4);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info4->bmiHeader.biWidth, 
                info4->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits4);

   glBindTexture(GL_TEXTURE_2D, texName[4]);
   SetTexParams();
   bits5 = ReadBitmap("..\\Images\\right.bmp", &info5);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info5->bmiHeader.biWidth, 
                info5->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits5);

   glBindTexture(GL_TEXTURE_2D, texName[5]);
   SetTexParams();
   bits6 = ReadBitmap("..\\Images\\left.bmp", &info6);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info6->bmiHeader.biWidth, 
                info6->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits6);

   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   setTextures(texName);

   GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
   GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   GLfloat light_position1[] = { 0.0, 1.0, 0.0, 0.0 };
   
   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
   glEnable(GL_LIGHT1);
   glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
   GLfloat gray[]={0.8,0.8,0.5,1.};
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);


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