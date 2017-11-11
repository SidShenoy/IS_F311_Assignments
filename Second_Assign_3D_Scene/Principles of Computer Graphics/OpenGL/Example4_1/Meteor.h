// Meteor.h: interface for the Meteor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_METEOR_H__B84D157A_0E93_46E0_B9DA_F7E5909E07B8__INCLUDED_)
#define AFX_METEOR_H__B84D157A_0E93_46E0_B9DA_F7E5909E07B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "global.h"



class Meteor;


class Meteor  
{
public:

  Meteor(int uID);
  virtual ~Meteor();
  void Draw();			//Draw the meteor
  void DrawCollision(); //Draw the meteor that has collided
  void Update();		//Update meteor location: for this example simply decrement it' y-cooridnate in order to move it down	
  bool HitEarth();		//returns true if the metor has hit Earth
  bool OutOfScreen();    //returns true if the metor is out of screen
  GLfloat* GetLocation() {return location;}
  GLint ID;				// unique ID to identify the meteor

private:
  
  GLfloat location[2];	//meteor's location: location[0]=x-coordinate; location[1] =y-coordinate 
};

typedef map<int, Meteor*> MeteorMap;
static MeteorMap Meteors;


#endif // !defined(AFX_METEOR_H__B84D157A_0E93_46E0_B9DA_F7E5909E07B8__INCLUDED_)
