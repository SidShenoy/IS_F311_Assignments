#include <gl\glut.h>
#include <map>
#include <vector>

#include "..\vrml.h"
#include "Models.h"

#define MAXSHAPES 25
#define MAXCOORDS  3000
#define XMIN -0.72
#define XMAX 0.72
#define YMIN -1
#define YMAX 1


GLfloat   coords[MAXSHAPES][3*MAXCOORDS];
GLint     indices[MAXSHAPES][3*MAXCOORDS];
GLfloat   normals[MAXSHAPES][3*MAXCOORDS];
GLint     nindices[MAXSHAPES][3*MAXCOORDS];
GLint     noofpoly[MAXSHAPES];
GLint     noofshapes;

GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat_diffuse[] = { 0.5,0.5,0.3,1.};
GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat low_shininess[] = { 20 };

GLfloat Cylindermat_diffuse[] = { 0.6,0.1,0.1,1.};

using namespace std;

vector<MODELINFO *> Models;
	


extern GLuint textureIDs[2];

void draw_Ground()
{
	glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
	glBegin(GL_QUADS);

	glNormal3f(0,1,0);
	glVertex3f(100.,0,-100);

	glVertex3f(-100.,0,-100);

	glVertex3f(-100.,0,00);

	glVertex3f(100.,0,100);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void draw_Andy(GLfloat *position){
	int i,j;
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glPushMatrix();
  glTranslatef(position[0],position[1]+0.5,position[2]);
  glScalef(0.2,0.2,0.2);

	for (j=0;j<noofshapes;j++) {
		for (i=0;i<noofpoly[j]*3;i=i+3) {
			glBegin(GL_TRIANGLES);
			glNormal3fv(&(normals[j][3*nindices[j][i]]));
			glVertex3fv(&(coords[j][3*indices[j][i]]));
			glNormal3fv(&(normals[j][3*nindices[j][i+1]]));
			glVertex3fv(&(coords[j][3*indices[j][i+1]]));
			glNormal3fv(&(normals[j][3*nindices[j][i+2]]));
			glVertex3fv(&(coords[j][3*indices[j][i+2]]));
		glEnd();
		}
	}
	glPopMatrix();
}



GLUquadricObj  *cylinder;

void draw_Cylinder(GLfloat *position){

  
  glBindTexture(GL_TEXTURE_2D, textureIDs[1]);
  glPushMatrix();
  	
  glTranslatef(position[0],position[1]+3,position[2]);
  glRotatef(90,1,0,0);
  gluCylinder( cylinder, 1.,1., 7., 30,30 );

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);

}


bool WithinViewingCylinder(GLfloat *sphCenter, GLfloat *pos){
	if ( ((sphCenter[0]-pos[0])*(sphCenter[0]-pos[0]))
		+ ((sphCenter[2] - pos[2])*(sphCenter[2]-pos[2])) < (50.*50.))
		return TRUE;
	return FALSE;
}

void drawWorld(CAMERAINFO camera){

	GLfloat sphCenter[3];

	sphCenter[0] = camera.position[0] + sin(TORADIANS(camera.orientation[1]))*25.;
	sphCenter[2] = camera.position[2] + cos(TORADIANS(camera.orientation[1]))*25.;

	vector<MODELINFO *>::iterator it;
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	draw_Ground();

	for (it = Models.begin(); it!= Models.end(); ++it) {
		if (!(WithinViewingCylinder(sphCenter, (*it)->position)))
			continue;
		else {
			if ((*it)->type == TANDY)
				draw_Andy((*it)->position);
			else if ((*it)->type == TCYLINDER)
				draw_Cylinder((*it)->position);
		}
	}
	
}


int RandomPos(){
	return (((int)((GLfloat)rand()/RAND_MAX * 50)-25));
}

void InitWorld(){
	int i;
	SYSTEMTIME systime;
	GetSystemTime(&systime);
	// Seed random number generator
	srand(systime.wMinute*60+systime.wSecond);

	 noofshapes = ReadVRML("..\\Models\\robot.wrl", &coords[0][0], &normals[0][0],&indices[0][0],&nindices[0][0], &(noofpoly[0]), MAXSHAPES, MAXCOORDS);

	 MODELINFO *Andy, *Cylinder[25], *Teapot;

	 Andy = (MODELINFO *)malloc (sizeof(MODELINFO));
	 Andy->position[0] = RandomPos();
	 Andy->position[0] = 0;
	 Andy->position[1] = 0;
	 Andy->position[2] = RandomPos();
	 Andy->position[2] = 0;
	 Andy->type = TANDY;

	 
	 Models.push_back(Andy);
	 

		cylinder = gluNewQuadric( ); 	       /* Allocate quadric object */
		gluQuadricDrawStyle( cylinder, GLU_FILL );  /* Render it as solid */


	 for (i=0;i<25;i++){

		Cylinder[i] = (MODELINFO *)malloc (sizeof(MODELINFO));
		Cylinder[i]->position[0] = RandomPos();
		Cylinder[i]->position[1] = 0;
		Cylinder[i]->position[2] = RandomPos();
		Cylinder[i]->type = TCYLINDER;
		Models.push_back(Cylinder[i]);
	 }
	 


	 

}