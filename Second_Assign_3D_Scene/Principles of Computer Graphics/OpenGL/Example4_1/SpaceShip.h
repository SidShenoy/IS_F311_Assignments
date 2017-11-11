// SpaceShip1.h: interface for the SpaceShip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPACESHIP1_H__F85EAF04_680D_4A5C_99F7_DEC4A4097ACE__INCLUDED_)
#define AFX_SPACESHIP1_H__F85EAF04_680D_4A5C_99F7_DEC4A4097ACE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "global.h"


class SpaceShip  
{
public:
	SpaceShip();
	virtual ~SpaceShip();
	void SetPixels(BITMAPINFO *ssinfo, GLubyte    *sspixels);  // set the pixels and bitmapinfo for spaceship
  void Draw();					//Draw the spaceship
  void Update(GLfloat x, GLfloat y);		//update location of spaceship
  GLfloat GetXLocation(){ return location[0];}
  GLfloat GetYLocation() {return location[1];}
  void StartMove();	//start moving the spaceship	
  void StopMove();				//stop moving the spaceship: update of spaceship will not do anything
private:
  
  GLfloat location[2];
 
  GLubyte *mypixels;			//pixel info of spaceship
  BITMAPINFO *myimginfo;		//bitmap info of spacehsip image
	
  bool b_updatess;				//are we updating location of spaceship

};

#endif // !defined(AFX_SPACESHIP1_H__F85EAF04_680D_4A5C_99F7_DEC4A4097ACE__INCLUDED_)
