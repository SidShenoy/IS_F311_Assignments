#include "Shapes.h"

#define PI 3.1415926535898 

#define MAXCOORDS  3000
GLfloat XMIN, XMAX;
GLfloat YMIN, YMAX;


void MapCoordinates(GLfloat x,GLfloat y, GLfloat z, int mapping) 
{
  glTexCoord2f((x-XMIN)/(XMAX-XMIN),(y-YMIN)/(YMAX-YMIN));
}

void TexObject(GLfloat *icoords, GLfloat *inormals, 
             GLint *iindices, GLint *inindices,  
             GLint *noofpoly, int noofshapes, 
             GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax,
             int mapping)
{
  int i,j;
  GLfloat *coords,  *normals;
  GLint *indices, *nindices;
  XMIN = xmin; XMAX = xmax; YMIN = ymin; YMAX= ymax;
  for (j=0;j<noofshapes;j++) {
    coords = icoords+j*(3*MAXCOORDS);
    indices = iindices+j*(3*MAXCOORDS);
    nindices = inindices + j*(3*MAXCOORDS);
    normals = inormals +j*(3*MAXCOORDS);

    for (i=0;i<noofpoly[j]*3;i=i+3) {
     glBegin(GL_TRIANGLES);
      MapCoordinates(coords[3*indices[i]], coords[3*indices[i]+1], coords[3*indices[i]+2], mapping);
      glNormal3fv(&(normals[3*nindices[i]]));
      glVertex3fv(&(coords[3*indices[i]]));
      
      MapCoordinates(coords[3*indices[i+1]], coords[3*indices[i+1]+1], coords[3*indices[i+1]+2],mapping);
      glNormal3fv(&(normals[3*nindices[i+1]]));
	    glVertex3fv(&(coords[3*indices[i+1]]));
      
      MapCoordinates(coords[3*indices[i+2]], coords[3*indices[i+2]+1], coords[3*indices[i+2]+2],mapping);
      glNormal3fv(&(normals[3*nindices[i+2]]));
	    glVertex3fv(&(coords[3*indices[i+2]]));
     glEnd();
    }
  }
}




void TexSphere(GLfloat radius, int mapping){
  GLdouble inc = PI/12;
  GLdouble theta, phi;
  bool even = true;
  for (theta=-PI/2; theta<=(PI/2-inc);theta+=inc){
    for (phi = 0; phi < 2*PI;phi+=inc) { 
    glBegin(GL_POLYGON);
      MapCoordinates(radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi),mapping);
      glNormal3f(radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi));
      glVertex3f(radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi));
      
      MapCoordinates(radius*cos(theta+inc)*cos(phi), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi),mapping);
      glNormal3f(radius*cos(theta+inc)*cos(phi), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi));
      glVertex3f(radius*cos(theta+inc)*cos(phi), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi));
      
      MapCoordinates(radius*cos(theta+inc)*cos(phi+inc), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi+inc),mapping);
      glNormal3f(radius*cos(theta+inc)*cos(phi+inc), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi+inc));
      glVertex3f(radius*cos(theta+inc)*cos(phi+inc), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi+inc));
      
      MapCoordinates(radius*cos(theta)*cos(phi+inc), radius*sin(theta),radius*cos(theta)*sin(phi+inc),mapping);
      glNormal3f(radius*cos(theta)*cos(phi+inc), radius*sin(theta),radius*cos(theta)*sin(phi+inc));
      glVertex3f(radius*cos(theta)*cos(phi+inc), radius*sin(theta),radius*cos(theta)*sin(phi+inc));
    glEnd();
    }
  }  
}



void TexCube(GLfloat length, GLfloat height, GLfloat depth, int mapping){
 
  XMIN = -length/2.;XMAX = length/2.;
  YMIN = -height/2; YMAX = height/2.;

  // base
  glNormal3f(0.,-1.,0.);
  glBegin(GL_POLYGON); 
    MapCoordinates(-length/2, -height/2, depth/2, mapping);
    glVertex3f(-length/2, -height/2, depth/2);
    MapCoordinates(-length/2, -height/2, -depth/2, mapping);
    glVertex3f(-length/2, -height/2, -depth/2);
    MapCoordinates(length/2, -height/2, -depth/2, mapping);
    glVertex3f(length/2, -height/2, -depth/2);
    MapCoordinates(length/2, -height/2, depth/2, mapping);
    glVertex3f(length/2, -height/2, depth/2);
	glEnd();

  // front face
  glNormal3f(0.,0.,1.);
  glBegin(GL_POLYGON);
  MapCoordinates(-length/2, -height/2, depth/2, mapping);
    glVertex3f(-length/2, -height/2, depth/2);
  MapCoordinates(length/2, -height/2, depth/2,mapping);
    glVertex3f(length/2, -height/2, depth/2);
  MapCoordinates(length/2, height/2, depth/2,mapping);
    glVertex3f(length/2, height/2, depth/2);
  MapCoordinates(-length/2, height/2, depth/2,mapping);
    glVertex3f(-length/2, height/2, depth/2);
	glEnd();

  // right side face
    glNormal3f(1.,0.,0.);
   glBegin(GL_POLYGON); 
   MapCoordinates(length/2, -height/2, depth/2,mapping);
    glVertex3f(length/2, -height/2, depth/2);
  MapCoordinates(length/2, -height/2, -depth/2,mapping);
    glVertex3f(length/2, -height/2, -depth/2);
    MapCoordinates(length/2, height/2, -depth/2,mapping);
    glVertex3f(length/2, height/2, -depth/2);
  MapCoordinates(length/2, height/2, depth/2,mapping);
    glVertex3f(length/2, height/2, depth/2);
	glEnd();
  // back side face
  glNormal3f(0.,0.,-1.);
   glBegin(GL_POLYGON);
   MapCoordinates(-length/2, -height/2, -depth/2,mapping);
    glVertex3f(-length/2, -height/2, -depth/2);
  MapCoordinates(-length/2, height/2, -depth/2,mapping);
    glVertex3f(-length/2, height/2, -depth/2);
  MapCoordinates(length/2, height/2, -depth/2,mapping);
    glVertex3f(length/2, height/2, -depth/2);
 MapCoordinates(length/2, -height/2, -depth/2,mapping);
    glVertex3f(length/2, -height/2, -depth/2);
	glEnd();
  // left side face
  glNormal3f(-1.,0.,0.);
   glBegin(GL_POLYGON); 
   MapCoordinates(-length/2, -height/2, depth/2,mapping);
    glVertex3f(-length/2, -height/2, depth/2);
    MapCoordinates(-length/2, height/2, depth/2,mapping);
    glVertex3f(-length/2, height/2, depth/2);
  MapCoordinates(-length/2, height/2, -depth/2,mapping);
    glVertex3f(-length/2, height/2, -depth/2);
    MapCoordinates(-length/2, -height/2, -depth/2,mapping);
    glVertex3f(-length/2, -height/2, -depth/2);
	glEnd();

  // top
  glNormal3f(0.,1.,0.);
   glBegin(GL_POLYGON);
   MapCoordinates(-length/2, height/2, depth/2,mapping);
    glVertex3f(-length/2, height/2, depth/2);
    MapCoordinates(length/2, height/2, depth/2,mapping);
    glVertex3f(length/2, height/2, depth/2);
  MapCoordinates(length/2, height/2, -depth/2,mapping);
    glVertex3f(length/2, height/2, -depth/2);
  MapCoordinates(-length/2, height/2, -depth/2,mapping);
    glVertex3f(-length/2, height/2, -depth/2);
	glEnd();
   
}