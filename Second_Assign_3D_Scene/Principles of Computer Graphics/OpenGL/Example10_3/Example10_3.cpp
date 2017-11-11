#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>


#include "Example10_3.h"

#include "..\bmp.h"






void UpdateCameraPosition(CAMERAINFO *camera) {
	LARGE_INTEGER currentTime;
	GLfloat elapsedTime;
	GLfloat velocity=0;
	GLfloat avelocity= 0;
	
	// if up arrow has been pressed, velocity is now forward
	if (KEYDOWN(VK_UP))
		velocity = 0.4f;
	if (KEYDOWN(VK_DOWN))
		velocity = -0.4f;
	if (KEYDOWN(VK_LEFT))
		avelocity = -7;
	if (KEYDOWN(VK_RIGHT))
		avelocity = 7;
	
	QueryPerformanceCounter(&currentTime);
	elapsedTime = (GLfloat)(currentTime.QuadPart - lastTime.QuadPart)/frequency.QuadPart;
	lastTime = currentTime;

	
	camera->orientation[0] = 0.;
	camera->orientation[1] += avelocity*elapsedTime;
	camera->orientation[2] = 0.0;

	camera->position[0] +=  elapsedTime * velocity * ((GLfloat)sin(TORADIANS(camera->orientation[1]))) ;
	camera->position[1] = 0.2;
	camera->position[2] -= elapsedTime * velocity * ((GLfloat)cos(TORADIANS(camera->orientation[1])));


}

void MoveCameraPosition(CAMERAINFO camera){

	glRotatef(camera.orientation[2], 0.,0.,1.);
	glRotatef(camera.orientation[1], 0.,1.,0.);
	glRotatef(camera.orientation[0], 1.,0.,0.);
	
	glTranslatef(-camera.position[0], -camera.position[1], -camera.position[2]);

}




void Display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glLoadIdentity();
   
   UpdateCameraPosition(&camera);
   MoveCameraPosition(camera);
 
   drawWorld(camera);
   
   glFlush();
   glutSwapBuffers();
   
}

void reshape(int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
	gluPerspective(35., (GLfloat)w/h, 0.5, 50.0);
  glMatrixMode(GL_MODELVIEW);
}

void timer(int value)
{ 
  // Force a redisplay .. , also contains game logic
  glutPostRedisplay();         
 // Restart the timer
  glutTimerFunc(10, timer, 0);
}




void InitCameraPosition(CAMERAINFO *camera){
	camera->position[0] =0;
	camera->position[1] = 0.2;
	camera->position[2] =0 ;

	camera->orientation[0] += 0.0;
	camera->orientation[1] = 0.0;
	camera->orientation[2] = 0.0;
}


void init(void)
{    

   glClearColor (0.5,0.5,0.5,0);
   glEnable(GL_DEPTH_TEST);


   // OpenGL's automatic generation of texture coordinates
   {
        /* Use the x=0 and z=0 plane for s and t generation 
			because the plane and the cylinders 
			(in Object space) rest on the x-z plane */
        float tPlane[4] = {0., 0., 1., 0.};
        glTexGenfv (GL_T, GL_OBJECT_PLANE, tPlane);

		float sPlane[4] = {1., 0., 0., 0.};
        glTexGenfv (GL_S, GL_OBJECT_PLANE, sPlane);
    }

	// Generate the texture coordinates based on object coords distance from the axis.
    glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	// Enable OpenGL's automatic generation of texture coordinates
    glEnable (GL_TEXTURE_GEN_S);
    glEnable (GL_TEXTURE_GEN_T);



   glGenTextures(2, textureIDs);
   glBindTexture(GL_TEXTURE_2D, textureIDs[0]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);


   bits = ReadBitmap("..\\Images\\terrain.bmp", &info);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, 
                info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits);

  
   glBindTexture(GL_TEXTURE_2D, textureIDs[1]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);


   bits2 = ReadBitmap("..\\Images\\windows.bmp", &info2);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, info2->bmiHeader.biWidth, 
                info2->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, 
                bits2);



  
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   GLfloat light_position[] = { 0.0, 1.0, 1.0, 0.0 };
   GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };

   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   GLfloat light_position1[] = { -1.0, -1.0, 0.0, 0.0 };

   glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   glShadeModel (GL_SMOOTH);

	GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};		// Fog Color
	glFogi(GL_FOG_MODE, GL_LINEAR);		// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.35f);				// How Dense Will The Fog Be
	glFogf(GL_FOG_START, 1.0f);				// Fog Start Depth
	glFogf(GL_FOG_END, 25.0f);				// Fog End Depth
	glEnable(GL_FOG);


   glutTimerFunc(10, timer, 0);
   InitCameraPosition(&camera);
   InitWorld();

 

   QueryPerformanceCounter(&lastTime);
   QueryPerformanceFrequency(&frequency);

   }

void main(int argc, char** argv)
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 400);
  glutCreateWindow("Terrain Viewing");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutTimerFunc(10, timer, 0);
  glutMainLoop();
}