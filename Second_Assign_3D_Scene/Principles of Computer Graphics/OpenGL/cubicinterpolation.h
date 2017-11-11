#include <windows.h> 
#include <gl\glut.h> 

extern GLfloat HermiteValue(GLfloat KFValue1, GLfloat KFValue2, GLfloat KFValue3, GLfloat KFValue4, int N, int f);
extern GLfloat EvaluateCubicAt(GLfloat *KeyFrameValues, GLint *KeyFramePositions, GLint NumOfKeyFrames, GLint f);
