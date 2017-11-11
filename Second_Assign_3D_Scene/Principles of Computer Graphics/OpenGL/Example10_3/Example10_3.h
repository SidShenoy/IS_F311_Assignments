
#ifndef _EXAMPLE101
#define _EXAMPLE101

#include "models.h"



CAMERAINFO camera;

#define KEYDOWN(vkcode) (GetAsyncKeyState(vkcode) & 0x8000) ? 1 : 0
#define KEYUP(vkcode)   (GetAsyncKeyState(vkcode) & 0x8000) ? 0 : 1

GLubyte *bits;
BITMAPINFO *info;
GLubyte *bits2;
BITMAPINFO *info2;


GLuint textureIDs[3];


LARGE_INTEGER lastTime, frequency;


#endif
