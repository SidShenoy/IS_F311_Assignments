#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>

GLfloat LinearValue(GLfloat KFInitValue, GLfloat KFFinalValue, int N, int f){
	GLfloat ivalue;
	ivalue = KFInitValue + f*(KFFinalValue-KFInitValue)/(N-1);
	return ivalue;
}

GLfloat EvaluateLinearAt(GLfloat *KeyFrameValues, GLint *KeyFramePositions, GLint NumOfKeyFrames, GLint f)
{
	int i;
	GLint N, InitF;
	GLfloat value;

	// Find the keyframes which this frame interpolates
	for (i=0;i<NumOfKeyFrames;i++){
		if (f < KeyFramePositions[i])
			break;
	}
	i--;
	if (i<0) return (KeyFrameValues[0]); // should not happen
	if (i == (NumOfKeyFrames-1)) return (KeyFrameValues[i]);

	// interpolate between KeyFramePositions[i] and KeyFramePositions[i+1]
	N = KeyFramePositions[i+1]-KeyFramePositions[i]+1;
	InitF = KeyFramePositions[i];

	value = LinearValue(KeyFrameValues[i],  KeyFrameValues[i+1], N, (f-InitF));
	return value;

}


