
#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls



GLfloat ctrlPoints[4][3] = 
                  {-6.,0.,0.,\
                  -4.,6.,0.,\
                  4.,-6.,0.,\
                  6.,0.,0.};
int numPoints = 4;


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
   glLineWidth(3.0);
  draw_ControlPoints();
  glMapGrid1d(20.,0.,1.0);
  glEvalMesh1(GL_LINE,0,20);
  

  glFlush();

}

void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   // keep our logical coordinate system constant
   gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

}


void init(void){
  //set the clear color to be white
  glClearColor(1.,1.,1.0,1.0);

  glMap1f(GL_MAP1_VERTEX_3,0.,1.,3,numPoints,&ctrlPoints[0][0]);
  glEnable(GL_MAP1_VERTEX_3);
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Bezier Curve");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}