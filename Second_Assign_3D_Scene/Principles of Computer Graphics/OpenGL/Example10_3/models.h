#ifndef _MODELS
#define _MODELS

#include <math.h>

#define PI 3.1415926535898 

#define TORADIANS(x) ((double)x*PI/180.)

typedef struct _tCamera
{
	GLfloat position[3];
	GLfloat orientation[3];
} CAMERAINFO;



typedef struct _tModels
{
	GLfloat position[3];
	GLint type;
} MODELINFO;



#define TANDY 1
#define TCYLINDER 2



extern void drawWorld(CAMERAINFO camera);
extern void InitWorld();


#endif