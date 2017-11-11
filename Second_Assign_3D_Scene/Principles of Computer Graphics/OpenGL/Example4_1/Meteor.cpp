// Meteor.cpp: implementation of the Meteor class.
//
//////////////////////////////////////////////////////////////////////

#include "Meteor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Meteor::Meteor(int uID)
{
  //randomly create X, Y location of meteor within the boundaries of the screen
  // Y and Y coordinate should not be too small, so we add in a cheat
  location[0] = ((float)rand()/RAND_MAX)*SCREENMAXX +25;
  location[1] = ((float)rand()/RAND_MAX)*SCREENMAXY+200;
  ID = uID;
}

Meteor::~Meteor()
{
  //Meteors.erase(ID);
}

void Meteor::Draw()
{
  glBegin(GL_POINTS);                   
    glVertex2f(location[0],location[1]); 
  glEnd();
}

void Meteor::DrawCollision()
{
  glPointSize(20.0);
  glColor3f(1.,0.3, 0.);
  glBegin(GL_POINTS);                   
    glVertex2f(location[0],location[1]); 
  glEnd();
  glPointSize(6.0);
  glColor3f(1.,1., 1.);
}

void Meteor::Update() 
{
  location[1]--;

 // location[0] = prevLocation[0] +direction[0];
 // location[1]= prevLocation[1] - direction[1];
}

bool Meteor::OutOfScreen()
{
  if (location[1] <  0. || location[1] > SCREENMAXY ||
      location[0] <  0. || location[0] > SCREENMAXX)
      return true;
  return false;
}

bool Meteor::HitEarth()
{
  if (location[1] <  EARTHLOCATIONY)
    return true;
  return false;
 
}



