//#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include<stdio.h>
#define PI 3.1415926535898 
#define WIDTH_OF_BENCH 5;
#define LENGTH_OF_BENCH 10;
float COLOR_OF_TRUNK[3] = {73.0/255, 36.0/255, 0.0};
float COLOR_OF_LEAVES[3] = {0, 1.0, 0};

float rotate_x = 45;
float rotate_y = 0;

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

void drawCircle(float cx, float cy, float cz, float r, int num, int start, int end, float* color){
	glBegin(GL_LINE_STRIP);
	glColor3f(color[0], color[1], color[2]);
	for(int i = start; i < end; i++){
		float theta = 2.0 * 3.14159 * (float)(i % 360) / (float)(num);
		float x  = r * cosf(theta);
		float z = r * sinf(theta);
		glVertex3f(x + cx, cy, z + cz);
	}
	glEnd();
}

void drawTree(float x, float z, float height, float radBase, float radSphere){
	float height_of_trunk = height - sqrt(radSphere*radSphere - radBase*radBase);
	float y = 0;
	while(y <= height_of_trunk){
		drawCircle(x, y, z, radBase, 360, 0, 360, COLOR_OF_TRUNK);
		y += 0.5;
	}
	y = height;
	glMatrixMode(GL_MODELVIEW);	
	//glLoadIdentity();
	glTranslatef(x, y, z);
	glColor3f(COLOR_OF_LEAVES[0],COLOR_OF_LEAVES[1],COLOR_OF_LEAVES[2]);
	glutSolidSphere(radSphere, 12, 24);
	glTranslatef(-x, -y, -z);
	glFlush();
}

void drawBench(float x, float z, float theta_x){
	float length = LENGTH_OF_BENCH;
	float width = WIDTH_OF_BENCH;
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glColor3f(1,1,1);
	glTranslatef(x, 0, z);
	glRotatef(theta_x, 0, 1 , 0);
	glTranslatef((-1)*length / 4, 4.75, 0);	
	glScalef(length / 6, 9.5, width);
	glutSolidCube(1);
	glScalef(6 / length, 1/9.5, 1/width);
	glTranslatef(length / 4, -4.75, 0);
	glRotatef(-theta_x, 0, 1 , 0);
	glTranslatef(-x, 0, -z);	
	//glLoadIdentity();
	glTranslatef(x,0,z);
	glRotatef(theta_x, 0, 1, 0);
	glTranslatef(length/ 4, 4.75, 0);
	glScalef(length / 6, 9.5 , width);
	glutSolidCube(1);
	glScalef(6 / length, 1/9.5, 1/width);
	glTranslatef(-length / 4, -4.75, 0);
	glRotatef(-theta_x, 0, 1 , 0);
	glTranslatef(-x, 0, -z);
	//glLoadIdentity();
	glColor3f(0,1,1);
	glTranslatef(x, 10, z);
	glRotatef(theta_x, 0, 1, 0);
	glScalef(length, 1, width);
	glutSolidCube(1);
	glScalef(1/length, 1, 1/width);	//rev
	glRotatef(-theta_x, 0, 1, 0);	//rev
	glTranslatef(-x, -10, -z);		//rev
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
			glBegin(GL_LINES);
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
			glBegin(GL_LINES);
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

void specialKeys( int key, int x, int y ) {
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 0.2;
 
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 0.2;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 0.2;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 0.2;
 

  //  Request display update
  glutPostRedisplay();
 
}

void Display(void)
{
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity (); 

	gluLookAt(100*sin(rotate_y),100*sin(rotate_x),100*cos(rotate_y)*cos(rotate_x), 0,0,0,0.,1.,0.); //done
	
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
	float white[3] = {1.0, 1.0, 1.0};
	drawCircle(0,0,0,20,360,280,620,white);
	drawCircle(0,0,0,30,360,0,361,white);
	drawFence(15,-30,30,30,30,10);
	drawFence(15,-30,-30,-30,30,10);
	drawFence(15,-30,-30,30,-30,10);
	drawFence(15,30,-30,30,30,10);
	drawTree(20, 20, 30, 3, 10);
	drawBench(-7, -7, 60);
	glFlush();

 
}




void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	glFrustum (-10*(GLfloat)w/h,10*(GLfloat)w/h, -10,10, 50, 200.0);
    
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
  glutSpecialFunc(specialKeys);
  glutMainLoop();
}
