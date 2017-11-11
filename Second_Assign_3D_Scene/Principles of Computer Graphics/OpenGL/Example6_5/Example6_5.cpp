#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>



void Display(void)
{
 
 
  glClear (GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT );
  
  glutSolidSphere(2., 840,840);
  glFlush();
  
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

   		// position of light
	GLfloat light_position[] = { -1.0, 1.0, 0.0, 1.0 };
	GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);



    gluLookAt(0.,0.,5, 0,0,-100,0.,1.,0.);
	// model view matrix now has a translation of Z=-5!.. 
	// if we were to define the same light position at this point, this is how it should be
	// GLfloat light_position[] = { -1.0, 1.0, 5.0, 1.0 };
    // glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	


    
}


void init(void){
  
  //set the clear color to be white
  glClearColor(1.0,1.0,1.0,0.0);
	glShadeModel (GL_SMOOTH);

	 // Set up the lighting


  // diffuse light color
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };

 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.8,0.0,0.,1.};
  // set the ambient and diffuse reflectance of the material
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  glEnable(GL_DEPTH_TEST);
	
}


void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (640, 400);   
  glutCreateWindow("Spot Light");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}