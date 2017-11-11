#ifndef __vrml_h__
#define __vrml_h__

#include <gl/glut.h>
#include <windows.h>


int ReadVRML(const char *filename, 
             GLfloat *coordinates, GLfloat *normals, 
             GLint *indices, GLint *nindices,  
             GLint *noofpoly, int maxshapes, int maxcoords);  
#endif