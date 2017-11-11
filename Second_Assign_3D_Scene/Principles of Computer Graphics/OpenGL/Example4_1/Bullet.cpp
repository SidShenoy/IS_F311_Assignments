// Bullet.cpp: implementation of the Bullet class.
//
//////////////////////////////////////////////////////////////////////

#include "Bullet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


Bullet::Bullet(int uID, int x, int y)
{
  
  location[0] = x;
  location[1] = y;
  ID = uID;
}

Bullet::~Bullet()
{
  //Bullets.erase(ID);
}

void Bullet::Draw()
{
  glBegin(GL_POINTS); 
    glVertex2f(location[0],location[1]); 
  glEnd();
}

void Bullet::Update() 
{
  location[1]++;
  
}

bool Bullet::OutOfScreen()
{
  if (location[1] > SCREENMAXY)
      return true;
  return false;
}

bool EqualErr(GLfloat a, GLfloat b){
  if (fabs(a-b) < 6.) 
    return true;
  return false;
}

bool Bullet::Collide(Meteor * m)
{

  GLfloat *mloc = m->GetLocation();

  if (EqualErr(mloc[0],location[0]) && EqualErr(mloc[1],location[1]))
    return true;
 
  return false;
  
 
}


