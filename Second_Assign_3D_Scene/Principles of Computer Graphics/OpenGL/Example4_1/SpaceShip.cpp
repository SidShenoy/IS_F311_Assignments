// SpaceShip1.cpp: implementation of the SpaceShip class.
//
//////////////////////////////////////////////////////////////////////

#include "SpaceShip.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SpaceShip::SpaceShip()
{
  location[0] = SCREENMAXX/2. ;
  location[1] = 50;
  b_updatess = 0;
}



SpaceShip::~SpaceShip( )
{
	
}

void SpaceShip::SetPixels(BITMAPINFO *ssinfo, GLubyte    *sspixels){
	mypixels = sspixels;
	myimginfo = ssinfo;
}

void SpaceShip::Draw()
{
  glRasterPos2i(location[0],location[1]);
  glDrawPixels(myimginfo->bmiHeader.biWidth,
               myimginfo->bmiHeader.biHeight,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, mypixels);
}

void SpaceShip::StartMove() {
	b_updatess = TRUE;
}

void SpaceShip::StopMove() {
	b_updatess = FALSE;
}

void SpaceShip::Update(GLfloat x, GLfloat y) 
{
	if (b_updatess) {
		location[0]  = x; //location[1] = y;
	}
}


