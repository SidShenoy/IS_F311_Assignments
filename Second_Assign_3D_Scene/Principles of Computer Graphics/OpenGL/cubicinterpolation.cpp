#include "cubicinterpolation.h"

GLfloat tension = 0.3;
GLfloat CardinalValue(GLfloat KFValuem1, GLfloat KFValue1, GLfloat KFValue2, GLfloat KFValuep2, int N, int f)
{

	GLfloat F = 1.0*f/(N-1);
	
	GLfloat tangent1 = (1.-tension)*(KFValue2-KFValuem1)/2.;
	GLfloat tangent2 = (1.-tension)*(KFValuep2-KFValue1)/2.;

	GLfloat hvalue = F*F*F*(2.*KFValue1-2.*KFValue2+tangent1 + tangent2) +
					 F*F*(-3.*KFValue1+3.*KFValue2 -2.*tangent1 - tangent2) +
					 F*(tangent1)+
					 KFValue1;
	return hvalue;
}

GLfloat EvaluateCubicAt(GLfloat *KeyFrameValues, GLint *KeyFramePositions, GLint NumOfKeyFrames, GLint f)
{
	int i;
	GLint N, InitF;
	GLfloat value;

	// Find the keyframes which this frame interpolates
	if (NumOfKeyFrames <2)
		return -1;

	for (i=0;i<NumOfKeyFrames;i++){
		if (f <= KeyFramePositions[i])
			break;
	}
	i--;
	if (i<0) return (KeyFrameValues[0]); // should not happen

	// interpolate between KeyFramePositions[i, i+1] , KeyFramePositions[i+2] and [i+3] contribute to the equation as well
	
	InitF = KeyFramePositions[i];
	N = ( KeyFramePositions[i+1]-KeyFramePositions[i]+1);
	if (i == 0)		
		value = CardinalValue(KeyFrameValues[i],  KeyFrameValues[i], KeyFrameValues[i+1], KeyFrameValues[i+2], N, (f-InitF));
	else if (i == (NumOfKeyFrames -2))
		value = CardinalValue(KeyFrameValues[i-1],  KeyFrameValues[i], KeyFrameValues[i+1], KeyFrameValues[i+1], N, (f-InitF));
	else
		value = CardinalValue(KeyFrameValues[i-1],  KeyFrameValues[i], KeyFrameValues[i+1], KeyFrameValues[i+2], N, (f-InitF));

	return value;

}