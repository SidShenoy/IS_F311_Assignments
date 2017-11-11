#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>

#include "..\vrml.h"

#define MAXSHAPES 25
#define MAXCOORDS  3000
GLfloat   coords[MAXSHAPES][3*MAXCOORDS];
GLint     indices[MAXSHAPES][3*MAXCOORDS];
GLfloat   normals[MAXSHAPES][3*MAXCOORDS];
GLint     nindices[MAXSHAPES][3*MAXCOORDS];
GLint     noofpoly[MAXSHAPES];
GLint     noofshapes;

#define ROOT 20
#define CHEST 19
#define NECK 18
#define FACE 17
#define LEFTUPPERARM 16
#define LEFTLOWERARM 15
#define LPALM 14
#define LFINGERS 13
#define RIGHTUPPERARM 12
#define RIGHTLOWERARM 11
#define RPALM 10
#define RFINGERS 9
#define PELVIS 8
#define LEFTTHIGH 7
#define LEFTCALF 6
#define LHEEL 5
#define LTOES 4
#define RIGHTTHIGH 3
#define RIGHTCALF 2
#define RHEEL 1
#define RTOES 0

int SPEED = 10; 

void draw_Component(int component) {
	int i;
	for (i=0;i<noofpoly[component]*3;i=i+3) {
		glBegin(GL_TRIANGLES);
		glVertex3fv(&(coords[component][3*indices[component][i]]));
		glVertex3fv(&(coords[component][3*indices[component][i+1]]));
		glVertex3fv(&(coords[component][3*indices[component][i+2]]));
	glEnd();
	}


}

void draw_RightCalf(GLfloat angx) {
  glPushMatrix();
  glTranslatef(-.14,-1.59,0.1);
  glRotatef(angx, 1.,0.,0.);
  glTranslatef(.14,1.59,-0.1);
  draw_Component(RIGHTCALF);
  draw_Component(RHEEL);
  draw_Component(RTOES);
  glPopMatrix();
}


void draw_RightThigh(GLfloat angx,GLfloat angz,GLfloat calfang) {
  glPushMatrix();
  glTranslatef(-.2,-.7,0.);
  glRotatef(angx, 1.,0.,0.);
  glRotatef(angz, 0.,0.,1.);
  glTranslatef(.2,.7,0.);
   draw_RightCalf(calfang);
   draw_Component(RIGHTTHIGH);
  glPopMatrix();
}

void draw_RightLeg(GLfloat *rightlegang) {
  draw_RightThigh(rightlegang[0], rightlegang[1],rightlegang[2]);
}


void draw_LeftCalf(GLfloat angx) {
  glPushMatrix();
  glTranslatef(.14,-1.59,0.);
  glRotatef(angx, 1.,0.,0.);
  glTranslatef(-.14,1.59,0.);
  draw_Component(LEFTCALF);
  draw_Component(LHEEL);
  draw_Component(LTOES);
  glPopMatrix();
}


void draw_LeftThigh(GLfloat angx,GLfloat angz,GLfloat calfang) {
  glPushMatrix();
  glTranslatef(.2,-.7,0.);
  glRotatef(angx, 1.,0.,0.);
  glRotatef(angz, 0.,0.,1.);
  glTranslatef(-.2,.7,0.);
   draw_LeftCalf(calfang);
   draw_Component(LEFTTHIGH);
  glPopMatrix();
}

void draw_LeftLeg(GLfloat *leftlegang) {
  draw_LeftThigh(leftlegang[0], leftlegang[1],leftlegang[2]);
}

void draw_LeftLowerArm(GLfloat angx) {
  glPushMatrix();
  glTranslatef(.45,-.4,0.);
  glRotatef(angx, 1.,0.,0.);
  glTranslatef(-.45,.4,0.);
  draw_Component(LEFTLOWERARM);
  draw_Component(LPALM);
  draw_Component(LFINGERS);
  glPopMatrix();
}


void draw_LeftUpperArm(GLfloat angx,GLfloat angz,GLfloat larmang) {
  glPushMatrix();
  glTranslatef(.35,.25,0.);
  glRotatef(angx, 1.,0.,0.);
  glRotatef(angz, 0.,0.,1.);
  glTranslatef(-.35,-.25,.0);
   draw_LeftLowerArm(larmang);
   draw_Component(LEFTUPPERARM);
  glPopMatrix();
}

void draw_LeftArm(GLfloat * leftarmang) {
  draw_LeftUpperArm(leftarmang[0], leftarmang[1], leftarmang[2]);
}

void draw_RightLowerArm(GLfloat angx) {
  glPushMatrix();
  glTranslatef(-.45,-.4,0.);
  glRotatef(angx, 1.,0.,0.);
  glTranslatef(.45,.4,0.);
  draw_Component(RIGHTLOWERARM);
  draw_Component(RPALM);
  draw_Component(RFINGERS);
  glPopMatrix();
}


void draw_RightUpperArm(GLfloat angx,GLfloat angz,GLfloat larmang) {
  glPushMatrix();
  glTranslatef(-.35,.25,0.);
  glRotatef(angx, 1.,0.,0.);
  glRotatef(angz, 0.,0.,1.);
  glTranslatef(.35,-.25,.0);
   draw_RightLowerArm(larmang);
   draw_Component(RIGHTUPPERARM);
  glPopMatrix();
}

void draw_RightArm(GLfloat * leftarmang) {
  draw_RightUpperArm(leftarmang[0], leftarmang[1], leftarmang[2]);
}


void draw_Face(GLfloat angy) {
 glPushMatrix();
  glRotatef(angy, 0.,1.,0.);
  draw_Component(FACE);
 glPopMatrix();
}

void draw_Neck(GLfloat headang) {
 draw_Face(headang);
 draw_Component(NECK);
}

void draw_Head(GLfloat headang){
  draw_Neck(headang);
}

void draw_Android(GLfloat *T, GLfloat *R,
                  GLfloat headang, 
                  GLfloat *leftarmang, GLfloat *leftlegang,
                  GLfloat *rightarmang, GLfloat *rightlegang)
{
  glPushMatrix();
  glTranslatef(T[0], T[1], T[2]);
  glRotatef(R[0],1.,0.,0.);
  glRotatef(R[1],0.,1.,0.);
  glRotatef(R[2],0.,0.,1.);
  draw_Component(ROOT);
  {
    draw_Component(CHEST);
    draw_RightArm(rightarmang);
    draw_LeftArm(leftarmang);
    draw_Head(headang);
  }
  {
    draw_Component(PELVIS);
    draw_LeftLeg(leftlegang);
    draw_RightLeg(rightlegang);
  }
  glPopMatrix();

}

GLfloat T[] = {0.,1.,-5.};
GLfloat R[] = {0.,-90.,0.};
GLfloat headang = 0;
GLfloat leftarmang[] = {-30.,0,-40.};
GLfloat leftlegang[] = {-60.,0,120.};
GLfloat rightarmang[] = {0.,0,0};
GLfloat rightlegang[] = {0.,0,0};
int cycle=0;
int pos=0;




void Display(void)
{
	
   if (cycle%2 ==0) {
    rightarmang[0]-=0.3; leftarmang[0]+=0.3;
    rightarmang[2]-=0.4; leftarmang[2]+=0.4;
    rightlegang[0]-=0.6; leftlegang[0]+=0.6;
    rightlegang[2]+=1.2; leftlegang[2]-=1.2;
  } else {
    rightarmang[0]+=0.3; leftarmang[0]-=0.3;
    rightarmang[2]+=0.4; leftarmang[2]-=0.4;
    rightlegang[0]+=0.6; leftlegang[0]-=0.6;
    rightlegang[2]-=1.2; leftlegang[2]+=1.2;
  }
  pos++;
  if (pos >=100) {
    pos = 0;
    cycle++;
  }
  
  glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
  glLoadIdentity();
   draw_Android(T, R, headang, leftarmang, leftlegang, rightarmang, rightlegang);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}



void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
	  glLoadIdentity();
    glFrustum (-0.5*(GLfloat)w/h,0.5*(GLfloat)w/h, -0.5,0.5, 1., 40.0);
    glMatrixMode (GL_MODELVIEW);

}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT, GL_LINE);

}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize (640, 400);   
  glutCreateWindow("Hierarchical models");

  noofshapes = ReadVRML("..\\Models\\robot.wrl", &coords[0][0], &normals[0][0],&indices[0][0],&nindices[0][0], &(noofpoly[0]), MAXSHAPES, MAXCOORDS);

  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  glutMainLoop();
}