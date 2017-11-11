
#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include "..\bmp.h"


GLfloat ctrlPoints[8][3] = 
                  {-5.,-5.,0.,\
                  -5.,5.,0.,\
                  0.,5.,0.,\
                  0.,-5.,0.,\
                  5.,-5.,0.,\
                  8.,5.,0.,\
                  12.,5.,0.,\
                  12.,-5.,0.};
int numPoints = 8;
GLfloat Knots1[12] = {0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.};
GLfloat Knots2[12] = {0.,1.,2.,3.,4.,4.,5.,6.,7.,8.,9.,10.};
GLfloat Knots3[12] = {0.,1.,2.,3.,4.,4.,4.,5.,6.,7.,8.,9.};

GLUnurbsObj *pNurb = NULL;


// Draw the house around the origin
void draw_ControlPoints() {
  int i;
  glColor3f(0.,0.0,0.);
  glPointSize(10.0);
  glBegin(GL_POINTS);
    for (i=0;i<numPoints;i++)
    glVertex2fv(ctrlPoints[i]);
  glEnd();
  
}


void Display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  draw_ControlPoints();
  glLineWidth(5.0);
  gluBeginCurve(pNurb);

  gluNurbsCurve(pNurb,12,Knots1,3, &ctrlPoints[0][0],4,GL_MAP1_VERTEX_3);

  gluEndCurve(pNurb);

  glFlush();

}

void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   // keep our logical coordinate system constant
   gluOrtho2D(-8.0, 14.0, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

}


void init(void){
  //set the clear color to be white
  glClearColor(1.,1.,1.0,1.0);

  pNurb = gluNewNurbsRenderer();
  gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 25.f);
  gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, GLU_LINE);

}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Nurbs");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}