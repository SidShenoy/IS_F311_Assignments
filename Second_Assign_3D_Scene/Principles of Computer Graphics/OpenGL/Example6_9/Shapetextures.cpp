#include "Shapes.h"
#include "..\utils.h"

#define PI 3.1415926535898 

#define MAXCOORDS  3000
#define TOPFACE 0
#define BOTTOMFACE 1
#define FRONTFACE 2
#define BACKFACE 3
#define RTFACE 4
#define LTFACE 5

GLfloat XMIN, XMAX;
GLfloat YMIN, YMAX;
GLfloat ZMIN, ZMAX;

GLuint t[6];

void setTextures(GLuint *tex) {
  int i;
  for (i=0;i<6;i++)
    t[i] = tex[i];
}

int BindTexture(GLfloat nx, GLfloat ny, GLfloat nz) {
   GLfloat norm[] = {nx,ny,nz};
  normalize(norm);
  if ( (fabs(norm[1]) >= fabs(norm[2])) && (fabs(norm[1])>= fabs(norm[0]))){
    if (norm[1] >=0.) {
    // top only
    glBindTexture(GL_TEXTURE_2D, t[0]);
    return TOPFACE;
    } else{
    // bottom only
    glBindTexture(GL_TEXTURE_2D, t[1]);
    return BOTTOMFACE;
    }
  } else if (fabs(norm[2])> fabs(norm[0])){
    if (norm[2] >=0.) {
      glBindTexture(GL_TEXTURE_2D, t[2]);
      return FRONTFACE;
    } else  {
      glBindTexture(GL_TEXTURE_2D, t[3]);
      return BACKFACE;
    }
  } else 
  {
    if (norm[0]>=0.) {
      glBindTexture(GL_TEXTURE_2D, t[4]);
      return RTFACE;
    }
    else{
      glBindTexture(GL_TEXTURE_2D, t[5]);
      return LTFACE;
    }
  } 
  return -1;
}


void MapCoordinates(GLfloat nx,GLfloat ny, GLfloat nz, 
                    int face) 
{
  if (face == TOPFACE) 
    glTexCoord2f((nx/ny+1)/2.,(1-nz/ny)/2.);
  else if (face == BOTTOMFACE)
    glTexCoord2f((1-(nx/ny))/2.,(1-(nz/ny))/2.);
  else if (face == FRONTFACE)
    glTexCoord2f((nx/nz+1)/2.,(ny/nz+1)/2.);
  else if (face == BACKFACE)
    glTexCoord2f((1+nx/nz)/2.,(1-ny/nz)/2.);
  else if (face == RTFACE)
    glTexCoord2f((1-(nz/nx))/2.,(ny/nx+1)/2.);
  else 
    glTexCoord2f((-(nz/nx)+1)/2.,(-(ny/nx)+1)/2.);
}

void TexObject(GLfloat *icoords, GLfloat *inormals, 
             GLint *iindices, GLint *inindices,  
             GLint *noofpoly, int noofshapes, 
             GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax)
{
  int i,j;
  GLfloat *coords,  *normals;
  GLint *indices, *nindices;
  XMIN = xmin; XMAX = xmax; YMIN = ymin; YMAX= ymax;
  ZMIN = xmin; ZMAX = xmax;
  int face;
  for (j=0;j<noofshapes;j++) {
    coords = icoords+j*(3*MAXCOORDS);
    indices = iindices+j*(3*MAXCOORDS);
    nindices = inindices + j*(3*MAXCOORDS);
    normals = inormals +j*(3*MAXCOORDS);

    for (i=0;i<noofpoly[j]*3;i=i+3) {
     face =  BindTexture( normals[3*indices[i]], normals[3*indices[i]+1], normals[3*indices[i]+2]);
     glBegin(GL_TRIANGLES);
      
     MapCoordinates(normals[3*indices[i]], normals[3*indices[i]+1], normals[3*indices[i]+2],
                    face);
    
      glNormal3fv(&(normals[3*nindices[i]]));
      glVertex3fv(&(coords[3*indices[i]]));
      
      
      MapCoordinates(normals[3*indices[i+1]], normals[3*indices[i+1]+1], normals[3*indices[i+1]+2],
                    face);
     
      glNormal3fv(&(normals[3*nindices[i+1]]));
	    glVertex3fv(&(coords[3*indices[i+1]]));
     
      MapCoordinates(normals[3*indices[i+2]], normals[3*indices[i+2]+1], normals[3*indices[i+2]+2],
                    face);
      
      glNormal3fv(&(normals[3*nindices[i+2]]));
	    glVertex3fv(&(coords[3*indices[i+2]]));
     glEnd();
    }
  }
}




void TexSphere(GLfloat radius){
  GLdouble inc = PI/40;
  GLdouble theta, phi;
  int face;
  bool even = true;
  XMIN = - radius; XMAX = radius;
  YMIN = - radius; YMAX = radius;
  ZMIN = - radius; ZMAX = radius;

  for (theta=-PI/2; theta<=(PI/2-inc);theta+=inc){
    for (phi = 0; phi < 2*PI;phi+=inc) { 
    face =  BindTexture( radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi));

    glBegin(GL_POLYGON);
      MapCoordinates(radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi),
        face);
      glNormal3f(radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi));
      glVertex3f(radius*cos(theta)*cos(phi), radius*sin(theta),radius*cos(theta)*sin(phi));
      
      MapCoordinates(radius*cos(theta+inc)*cos(phi), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi),
        face);
      glNormal3f(radius*cos(theta+inc)*cos(phi), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi));
      glVertex3f(radius*cos(theta+inc)*cos(phi), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi));
      
      MapCoordinates(radius*cos(theta+inc)*cos(phi+inc), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi+inc),
        face);
      glNormal3f(radius*cos(theta+inc)*cos(phi+inc), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi+inc));
      glVertex3f(radius*cos(theta+inc)*cos(phi+inc), radius*sin(theta+inc),radius*cos(theta+inc)*sin(phi+inc));
      
      MapCoordinates(radius*cos(theta)*cos(phi+inc), radius*sin(theta),radius*cos(theta)*sin(phi+inc),
        face);
      glNormal3f(radius*cos(theta)*cos(phi+inc), radius*sin(theta),radius*cos(theta)*sin(phi+inc));
      glVertex3f(radius*cos(theta)*cos(phi+inc), radius*sin(theta),radius*cos(theta)*sin(phi+inc));
    glEnd();
    }
  }  
}



void TexCube(GLfloat length, GLfloat height, GLfloat depth){
 
  XMIN = -length/2.;XMAX = length/2.;
  YMIN = -height/2; YMAX = height/2.;
  ZMIN = -depth/2.; ZMAX = depth/2;
  int face;
  // base
  glNormal3f(0.,-1.,0.);
  face = BindTexture(0.,-1.,0.);
  glBegin(GL_POLYGON); 
    MapCoordinates(-length/2, -height/2, depth/2, face);
    glVertex3f(-length/2, -height/2, depth/2);
    MapCoordinates(-length/2, -height/2, -depth/2, face);
    glVertex3f(-length/2, -height/2, -depth/2);
    MapCoordinates(length/2, -height/2, -depth/2,face);
    glVertex3f(length/2, -height/2, -depth/2);
    MapCoordinates(length/2, -height/2, depth/2,face);
    glVertex3f(length/2, -height/2, depth/2);
	glEnd();

  // front face
  face = BindTexture(0.,0.,1.);
  glNormal3f(0.,0.,1.);
  glBegin(GL_POLYGON);
  MapCoordinates(-length/2, -height/2, depth/2, face);
    glVertex3f(-length/2, -height/2, depth/2);
  MapCoordinates(length/2, -height/2, depth/2,face);
    glVertex3f(length/2, -height/2, depth/2);
  MapCoordinates(length/2, height/2, depth/2,face);
    glVertex3f(length/2, height/2, depth/2);
  MapCoordinates(-length/2, height/2, depth/2,face);
    glVertex3f(-length/2, height/2, depth/2);
	glEnd();

  // right side face
  face = BindTexture(1.,0.,0.);
    glNormal3f(1.,0.,0.);
   glBegin(GL_POLYGON); 
   MapCoordinates(length/2, -height/2, depth/2,face);
    glVertex3f(length/2, -height/2, depth/2);
  MapCoordinates(length/2, -height/2, -depth/2,face);
    glVertex3f(length/2, -height/2, -depth/2);
    MapCoordinates(length/2, height/2, -depth/2,face);
    glVertex3f(length/2, height/2, -depth/2);
  MapCoordinates(length/2, height/2, depth/2,face);
    glVertex3f(length/2, height/2, depth/2);
	glEnd();
  // back side face
  face = BindTexture(0.,0.,-1.);
  glNormal3f(0.,0.,-1.);
   glBegin(GL_POLYGON);
   MapCoordinates(-length/2, -height/2, -depth/2,face);
    glVertex3f(-length/2, -height/2, -depth/2);
  MapCoordinates(-length/2, height/2, -depth/2,face);
    glVertex3f(-length/2, height/2, -depth/2);
  MapCoordinates(length/2, height/2, -depth/2,face);
    glVertex3f(length/2, height/2, -depth/2);
 MapCoordinates(length/2, -height/2, -depth/2,face);
    glVertex3f(length/2, -height/2, -depth/2);
	glEnd();
  // left side face
  face = BindTexture(-1.,0.,0.);
  glNormal3f(-1.,0.,0.);
   glBegin(GL_POLYGON); 
   MapCoordinates(-length/2, -height/2, depth/2,face);
    glVertex3f(-length/2, -height/2, depth/2);
    MapCoordinates(-length/2, height/2, depth/2,face);
    glVertex3f(-length/2, height/2, depth/2);
  MapCoordinates(-length/2, height/2, -depth/2,face);;
    glVertex3f(-length/2, height/2, -depth/2);
    MapCoordinates(-length/2, -height/2, -depth/2,face);
    glVertex3f(-length/2, -height/2, -depth/2);
	glEnd();

  // top
  face = BindTexture(0.,1.,0.);
  glNormal3f(0.,1.,0.);
   glBegin(GL_POLYGON);
   MapCoordinates(-length/2, height/2, depth/2,face);
    glVertex3f(-length/2, height/2, depth/2);
    MapCoordinates(length/2, height/2, depth/2,face);
    glVertex3f(length/2, height/2, depth/2);
  MapCoordinates(length/2, height/2, -depth/2,face);
    glVertex3f(length/2, height/2, -depth/2);
  MapCoordinates(-length/2, height/2, -depth/2,face);
    glVertex3f(-length/2, height/2, -depth/2);
	glEnd();
   
}

