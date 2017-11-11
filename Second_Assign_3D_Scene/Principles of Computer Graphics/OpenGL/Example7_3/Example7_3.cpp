
#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls



GLfloat ctrlPoints[7][4][3] = 
{{{-12.,0.,10.},{-12.f,0.f,5.f},{-12.f,0.f,-5.f},{-12.f,0.f,-10.f}},
{{-8.,0.,10.},{-8.,0.,5.},{-8.,0.,-5.},{-8.,0.f,-10.f}},
{{-4.,0.,10.},{-4,0,5},{-4,0,-5},{-4,0,-10}},
{{0.,0.,10.},{0,0,5},{-0,0,-5},{0,0,-10}},
{{4.,0.,10.},{4,0,5},{4,0,-5},{4,0,-10}},
{{8.,0.,10.},{8,0,5},{8,0,-5},{8,0,-10}},
{{12.,0.,10.},{12,0,5},{12,0,-5},{12,0,-10}}
};

GLfloat Knotst[8] = {0.,0.,1.,1.,2.,2.,3.,3.};
GLfloat Knotss[11] = {0.,0.,0.,0.,1.,2.,3.,4.,4.,4.,4.};


GLUnurbsObj *pNurb = NULL;


GLint sign =1;
GLint turn =0;
int SPEED = 200;

// Draw the house around the origin
void draw_ControlPoints() {
  int i,j;
  glPointSize(10.0);
  glBegin(GL_POINTS);
  for (i=0;i<7;i++){
    for (j=0;j<4;j++){
      glColor3f(j/4.,0.,0.);
      glVertex3fv(ctrlPoints[i][j]);
    }
    
  }
  glEnd();
  
}

void InitWave() {
  int i,j;
  for (i=1;i<6;i++){
    for (j=0;j<4;j++){
      if (i <3) {
        ctrlPoints[i][j][1] =-5;
      }else if (i > 3) 
        ctrlPoints[i][j][1] =5;
    }
  }
}

void MakeWave() {
  int i,j;
  if (turn == 40) {
    turn = 0;
    sign =-sign;
  }
  for (i=1;i<6;i++){
    for (j=0;j<4;j++){
      if (i <3) {
        ctrlPoints[i][j][1] += sign*0.25;
      }else if (i > 3) {
        ctrlPoints[i][j][1] -= sign*0.25;
        }
    }
  }
}

void timer(int value)
{
  turn++;
  MakeWave();
  glutPostRedisplay();         
  glutTimerFunc(SPEED, timer, 0);
}

void Display(void)
{
  glutSwapBuffers();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
//glTranslatef(0.,0.,-12);
//glRotatef(-45.,1.,0.,0.);
  draw_ControlPoints();
  

  gluBeginSurface(pNurb);

  gluNurbsSurface(pNurb,11,Knotss,8,Knotst, 4*3, 3, &ctrlPoints[0][0][0],4,4,GL_MAP2_VERTEX_3);

  gluEndSurface(pNurb);

  glFlush();
  


}

void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
	  //glFrustum (-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.3,0.3, 1., 40.0);
   //glOrtho(-15,15,-15,15,-15,15);
   //(-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.3,0.3, 1., 40.0);
   gluPerspective(75,w/h,1,40);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt(0.,25.,0.,0.,-100.,-00.,0.,0.,-1.);
   glRotatef(-30,1.,0.,0.);
   



}


void init(void){
  //set the clear color to be white
  glClearColor(1.,1.,1.0,1.0);

  //glMap1f(GL_MAP1_VERTEX_3,0.,1.,3,numPoints,&ctrlPoints[0][0]);
  //glEnable(GL_MAP1_VERTEX_3);
  pNurb = gluNewNurbsRenderer();
  gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 30.f);
  gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, GLU_FILL);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
  GLfloat mat_diffuse[] = { 0.,0.5,1.,1.};
  GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat low_shininess[] = { 2 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
  
  InitWave();
  glutTimerFunc(SPEED, timer, 0);
  
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Bezier Curve");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}