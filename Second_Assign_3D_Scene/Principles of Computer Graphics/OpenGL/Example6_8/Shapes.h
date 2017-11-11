#ifndef __shapetextures_h__
#define __shapetextures_h__

#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define PLANAR 0
#define CYLINDRICAL 1
#define SPHERICAL 2


extern void TexSphere(GLfloat radius, int mapping);
extern void TexSphere1(GLfloat radius, int mapping);
extern void TexCube(GLfloat length, GLfloat height, GLfloat depth, int mapping);
extern void TexCylinder(GLfloat radius, GLfloat height, int mapping);
extern void TexObject(GLfloat *coordinates, GLfloat *normals, 
             GLint *indices, GLint *nindices,  
             GLint *noofpoly, int noofshapes, 
             GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax,int mapping);

#endif