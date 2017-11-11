//#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include<stdio.h>
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

void drawFence(int number, int x1, int z1, int x2, int z2, int height)	// x1 == x2 or z1 ==z2 and x1 < x2 and z1 < z2
{
	printf("HELLO");
	fflush(stdout);
	if(x1 == x2){
		int space = abs(z1-z2);
		float width = space / (number*2);
		float zpos = z1;
		for(int i = 0; i < number; i++){
			zpos += width;
			glBegin(GL_QUADS);
				glVertex3f(x1,0,zpos);
				glVertex3f(x1,height, zpos);
				zpos += width;
				glVertex3f(x1, height, zpos);
				glVertex3f(x1, 0, zpos);		
			glEnd();	
		}
	}else{
		int space = abs(x1-x2);
		float width = space / (number*2);
		float xpos = x1;
		for(int i = 0; i < number; i++){
			xpos += width;
			glBegin(GL_QUADS);
				glVertex3f(xpos,0,z1);
				glVertex3f(xpos,height, z1);
				xpos += width;
				glVertex3f(xpos, height, z1);
				glVertex3f(xpos, 0, z1);		
			glEnd();	
		}	
	}
fflush(stdout);	
}

void DrawCircle(float cx, float cz, float r, int num, int start, int end){
	glBegin(GL_LINE_STRIP);
	for(int i = start; i < end; i++){
		float theta = 2.0 * 3.14159 * (float)(i % 360) / (float)(num);
		float x  = r * cosf(theta);
		float z = r * sinf(theta);
		glVertex3f(x + cx, 0, z + cz);
	}
	glEnd();
}

void Display(void)
{

	glClear (GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		glColor3f (1.0, 0.0, 0.0);
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
		glColor3f (0.0, 1.0, 0.0);
		glVertex3f(0,0,0);
		glVertex3f(0,10,0);
		glColor3f (0.0, 0.0, 1.0);
		glVertex3f(0,0,0);
		glVertex3f(0,0,10);
	glEnd();
	glColor3f (1.0, 1.0, 1.0);	
	DrawCircle(0,0,20,360,280,620);
	DrawCircle(0,0,30,360,0,361);
	drawFence(15,-30,30,30,30,10);
	//drawFence(15,-30,30,30,30);
	//drawFence(15,-30,30,30,30);
	//drawFence(15,-30,30,30,30);
	glFlush();

 
}




void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	glFrustum (-10*(GLfloat)w/h,10*(GLfloat)w/h, -10,10, 50, 200.0);
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity (); 

	gluLookAt(0,100,100, 0,0,0,0.,1.,0.); //done
}


void init(void){
  
  //set the clear color to be black
  glClearColor(0.0,0.0,0.0,0.0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT, GL_FILL);
  //glPolygonMode(GL_BACK, GL_LINE);
}


void main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize (320, 200);   
  glutCreateWindow("A Scene");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  glutMainLoop();
}