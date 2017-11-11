#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <time.h>
#include "..\bmp.h"
#include "global.h"
#include "Meteor.h"
#include "Bullet.h"
#include "SpaceShip.h"


BITMAPINFO *bginfo;				// Background Bitmap information 
GLubyte    *bgpixels;				// Actual background pixel data 
BITMAPINFO *ssinfo;				// Spaceship Bitmap information 
GLubyte    *sspixels;				// Spaceship pixel data

SpaceShip * spaceship;				// our spaceship object




// Using STL container - a vector. Vector works much like a 1 dimensional array.
// You can change this data structure to use an array instead
vector<Meteor *> destroym;			// list to hold meteors to be destroyed
vector<Bullet *> destroyb;			// list to hold bullets to be destroyed

// Iterators used to loop throught the STL containers
MeteorMap::iterator it;
BulletMap::iterator bit;

vector<Meteor *>::iterator itv;		
vector<Bullet *>::iterator bitv;


// Create the spaceship, image size is 50 by 50
void createSpaceShip() {
	spaceship = new SpaceShip();
	spaceship->SetPixels(ssinfo, sspixels);
}

// create a meteor and add it to our MeteorMap
void createMeteor() {
  if ( ((float)rand()/RAND_MAX) < 0.99)
    return;
  SYSTEMTIME systime;
  GetSystemTime(&systime);
  int ID = systime.wMinute*60+systime.wSecond;
  Meteors[ID] = new Meteor(ID);
}

// Create a bullet and add it to a Bulletmap
void createBullet(int x, int y) {
  SYSTEMTIME systime;
  GetSystemTime(&systime);
  int ID = systime.wMinute*60+systime.wSecond;
  Bullets[ID]= new Bullet(ID,x,y);
}

// End Program by displaying a sequence of images to represent an explosion
// Can do better! Just a sample
void EndProgram(Meteor *m) {
  BITMAPINFO *info;
  GLubyte *pixels;

  m->DrawCollision();
  glutSwapBuffers();
  Sleep(300);
  
  pixels = ReadBitmap("..\\Images\\chapter4\\explode1.bmp", 
    &info);
  glDrawPixels(info->bmiHeader.biWidth,
               info->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
  glFlush();
  glutSwapBuffers();
  Sleep(300);
   pixels = ReadBitmap("..\\Images\\chapter4\\explode2.bmp", 
    &info);
  glDrawPixels(info->bmiHeader.biWidth,
               info->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
  glFlush();
  glutSwapBuffers();
  Sleep(200);
   pixels = ReadBitmap("..\\Images\\chapter4\\explode3.bmp", 
    &info);
  glDrawPixels(info->bmiHeader.biWidth,
               info->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
  glFlush();
  glutSwapBuffers();
  Sleep(200);
  pixels = ReadBitmap("..\\Images\\chapter4\\explode4.bmp", 
    &info);
  glDrawPixels(info->bmiHeader.biWidth,
               info->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
  glFlush();
  glutSwapBuffers();
  Sleep(1000);
  exit(0);
  
}






void Display() {
 
	Meteor *m;
	Bullet *b;

	// Draw the background
  glRasterPos2i(0,0);
  glDrawPixels(bginfo->bmiHeader.biWidth,
               bginfo->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, bgpixels);
   
    
  glPointSize(6.0);
  // Clear out the destroy lists
  destroym.clear(); destroyb.clear();

  // If no meteors, just update the bullets
  if (Meteors.size() == 0) {
	  glColor3f(1.,0., 0.0); 
	  for (bit = Bullets.begin(); bit!= Bullets.end(); ++bit) {
      b = (Bullet *)((*bit).second);
      b->Update();
      b->Draw();
        if (b->OutOfScreen())
          destroyb.push_back(b);
	  } 
  }  else {
// Algorithm for updating meteors and bullets
	for (it = Meteors.begin(); it!= Meteors.end(); ++it) {
		m = (Meteor *)((*it).second);
		glColor3f(1.,1., 1.0); 
		m->Update();
		if (m->HitEarth()){
			// Destruction!!
			EndProgram(m);
		
		}
		m->Draw();
		glColor3f(1.,0., 0.0); 
		for (bit = Bullets.begin(); bit!= Bullets.end(); ++bit) {
			b = (Bullet *)((*bit).second);
			b->Update();
			b->Draw();
			if (b->Collide(m)) {
				m->DrawCollision();
				destroym.push_back(m);
				destroyb.push_back(b);
		
			}
			else {
				if (b->OutOfScreen())
					destroyb.push_back(b);
				if (m->OutOfScreen())
					destroym.push_back(m);
			}
		}
	}
	}

	//	Remove all the meteors in our destory list
	 for (itv = destroym.begin(); itv!= destroym.end(); ++itv){
	    if (Meteors.size() == 0) break;
		m =((Meteor *)(*itv));
		Meteors.erase(m->ID);
	}
	// Remove all bullets in our destroy list
	for (bitv = destroyb.begin(); bitv!= destroyb.end(); ++bitv) {
		if (Bullets.size() == 0) break;
		b = ((Bullet *)(*bitv));
		Bullets.erase(b->ID);
	}

	spaceship->Draw();

	glFlush();
	glutSwapBuffers();

}


void timer(int value)
{ 
  // randomly create meteor
  createMeteor();
  // Force a redisplay .. , also contains game logic
  glutPostRedisplay();         
 // Restart the timer
  glutTimerFunc(10, timer, 0);
}

void getMouse(int button, int state, int x, int y){
  // If right mouse clicked up, create a bullet at location of spaceship +25) (midpoint of spaceship)
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		createBullet(spaceship->GetXLocation()+25,spaceship->GetYLocation()+25);
		spaceship->StopMove();}
	else
	  spaceship->StartMove();
}

void getMouseMotion(int x, int y){
	// update spaceship when mouse is moved
	// spaceship motion is enabled only when button is clicked down
	spaceship->Update(x-25, SCREENMAXY-y );
}




void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   // keep our logical coordinate system constant
   gluOrtho2D(0.0, SCREENMAXX, 0.0, SCREENMAXY);

}


void init(void){

  // Timer callback
  glutTimerFunc(100, timer, 0);
  // Define mouse callback function
  glutMouseFunc(getMouse);
  // Define Mouse Motion callback function
  glutMotionFunc(getMouseMotion);

  // random number generator seeded by current time
  SYSTEMTIME systime;
  GetSystemTime(&systime);
  // Seed random number generator
  srand(systime.wMinute*60+systime.wSecond);

  //Create spaceship
  createSpaceShip();
  
}



void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (SCREENMAXX, SCREENMAXY);   
  glutCreateWindow("Our First Game!");

  // read in the background bitmap images
   if (argc > 1)
    bgpixels = ReadBitmap(argv[2], &bginfo);
  else
    bgpixels = ReadBitmap("..\\Images\\Chapter4\\space.bmp", &bginfo);
	// read in the spaceship imape
  sspixels = ReadBitmap("..\\Images\\Chapter4\\spaceshipsmall.bmp", &ssinfo);

  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);

  

  glutMainLoop();
}

