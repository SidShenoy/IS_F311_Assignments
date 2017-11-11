// Bullet.h: interface for the Bullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BULLET_H__8CFC8048_763A_4FA3_9AFA_5020ACC7DCCF__INCLUDED_)
#define AFX_BULLET_H__8CFC8048_763A_4FA3_9AFA_5020ACC7DCCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "global.h"
#include "Meteor.h"

class Bullet  
{
public:
	Bullet(int time, int x, int y);	//Define a new bullet at location(x,y). ID is the current time
	virtual ~Bullet();
  void Draw();			//Draw Bullet
  void Update();		//Update Bulet location, for this example simply increment the value of location[1]
  bool OutOfScreen();	//returns true if Bullet is out of screen
  bool Collide(Meteor *);	//returns true if Bullet collides with Meteor	
  GLfloat ID;
private:
  
  GLfloat location[2];	//(x,y) location of bullet
};

typedef map<int, Bullet*> BulletMap;
static BulletMap Bullets;

#endif // !defined(AFX_BULLET_H__8CFC8048_763A_4FA3_9AFA_5020ACC7DCCF__INCLUDED_)
