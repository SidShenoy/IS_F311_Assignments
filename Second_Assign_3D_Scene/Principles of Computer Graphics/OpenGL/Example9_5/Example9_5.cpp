#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls

#include "..\linearinterpolation.h"
#include "Snowman.h"

GLint SPEED = 100;






GLfloat snomanXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat botXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat tumXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat headXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat lEyeXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat rEyeXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat noseXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat lHandXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};
GLfloat rHandXforms[9] = {0.,0.,0.,0.,0.,0.,1.,1.,1.};

GLfloat smKeyFrameValues[15][9];
GLint smKeyFramePositions[15];
GLint smNumOfKeyFrames;

GLfloat sheadKeyFrameValues[15][9];
GLint sheadKeyFramePositions[15];
GLint sheadNumOfKeyFrames;

GLfloat seyeKeyFrameValues[15][9];
GLint seyeKeyFramePositions[15];
GLint seyeNumOfKeyFrames;


GLfloat slHandKeyFrameValues[15][9];
GLint slHandKeyFramePositions[15];
GLint slHandNumOfKeyFrames;

GLfloat srHandKeyFrameValues[15][9];
GLint srHandKeyFramePositions[15];
GLint srHandNumOfKeyFrames;


int currentFrame;
int MAXFRAMES = 71;


void timer(int value)
{
  
  glutPostRedisplay();         
  currentFrame++;
  if (currentFrame == MAXFRAMES)
	  currentFrame = 0;

  glutTimerFunc(SPEED, timer, 0);
}

void SetKeyFrame(int kf, GLfloat keyframevalues[15][9], GLint *keyframepositions, GLint *numKF,
				 GLfloat Tx, GLfloat Ty, GLfloat Tz,  GLfloat Rx, GLfloat Ry, GLfloat Rz, GLfloat Sx, GLfloat Sy, GLfloat Sz)
{
	keyframepositions[*numKF] = kf;
	
	keyframevalues[*numKF][0] = Tx;
	keyframevalues[*numKF][1] = Ty;
	keyframevalues[*numKF][2] = Tz;
	keyframevalues[*numKF][3] = Rx;
	keyframevalues[*numKF][4] = Ry;
	keyframevalues[*numKF][5] = Rz;
	keyframevalues[*numKF][6] = Sx;
	keyframevalues[*numKF][7] = Sy;
	keyframevalues[*numKF][8] = Sz;
	*numKF = *numKF+1;
}

void EvaluateXformsAt(GLfloat KeyFrameValues[15][9], GLint *KeyFramePositions, GLint NumOfKeyFrames, GLint f, GLfloat *xforms)
{
	int i;
	GLint N, InitF;
	// Find the keyframes which this frame interpolates
	for (i=0;i<NumOfKeyFrames;i++){
		if (f < KeyFramePositions[i])
			break;
	}
	i--;
	if (i<0){
		xforms[0] = KeyFrameValues[0][0];
		xforms[1] = KeyFrameValues[0][1];
		xforms[2] = KeyFrameValues[0][2];
		xforms[3] = KeyFrameValues[0][3];
		xforms[4] = KeyFrameValues[0][4];
		xforms[5] = KeyFrameValues[0][5];
		xforms[6] = KeyFrameValues[0][6];
		xforms[7] = KeyFrameValues[0][7];
		xforms[8] = KeyFrameValues[0][8];
	} // should not happen

	if (i== (NumOfKeyFrames-1)){
		xforms[0] = KeyFrameValues[i][0];
		xforms[1] = KeyFrameValues[i][1];
		xforms[2] = KeyFrameValues[i][2];
		xforms[3] = KeyFrameValues[i][3];
		xforms[4] = KeyFrameValues[i][4];
		xforms[5] = KeyFrameValues[i][5];
		xforms[6] = KeyFrameValues[i][6];
		xforms[7] = KeyFrameValues[i][7];
		xforms[8] = KeyFrameValues[i][8];
	}
	// interpolate between KeyFramePositions[i] and KeyFramePositions[i+1]
	N = KeyFramePositions[i+1]-KeyFramePositions[i]+1;
	InitF = KeyFramePositions[i];

	xforms[0] = LinearValue(KeyFrameValues[i][0],  KeyFrameValues[i+1][0], N, (f-InitF));
	xforms[1] = LinearValue(KeyFrameValues[i][1],  KeyFrameValues[i+1][1], N, (f-InitF));
	xforms[2] = LinearValue(KeyFrameValues[i][2],  KeyFrameValues[i+1][2], N, (f-InitF));
	xforms[3] = LinearValue(KeyFrameValues[i][3],  KeyFrameValues[i+1][3], N, (f-InitF));
	xforms[4] = LinearValue(KeyFrameValues[i][4],  KeyFrameValues[i+1][4], N, (f-InitF));
	xforms[5] = LinearValue(KeyFrameValues[i][5],  KeyFrameValues[i+1][5], N, (f-InitF));
	xforms[6] = LinearValue(KeyFrameValues[i][6],  KeyFrameValues[i+1][6], N, (f-InitF));
	xforms[7] = LinearValue(KeyFrameValues[i][7],  KeyFrameValues[i+1][7], N, (f-InitF));
	xforms[8] = LinearValue(KeyFrameValues[i][8],  KeyFrameValues[i+1][8], N, (f-InitF));

}



void draw_Ground(){
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glColor3f(0.8,0.8,0.8);
	glPushMatrix();
	glTranslatef(0.,-5.5,0.);
	glScalef(25.,10.,10.);
	glutSolidCube(1.);
	glPopMatrix();

	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
}
void Display(void)
{
	GLfloat ypos, xpos;
	glutSwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
	if (currentFrame == 41) { // cut
		glLoadIdentity();
		gluLookAt(16,5.,12, 0,0,-100,0.,1.,0.);
	}
	else if (currentFrame == 0) {
		glLoadIdentity();
		gluLookAt(8,7.,17, 0,0,-100,0.,1.,0.);
	}

	EvaluateXformsAt(smKeyFrameValues, smKeyFramePositions, smNumOfKeyFrames, currentFrame, snomanXforms);
    EvaluateXformsAt(sheadKeyFrameValues, sheadKeyFramePositions, sheadNumOfKeyFrames, currentFrame, headXforms);
	EvaluateXformsAt(seyeKeyFrameValues, seyeKeyFramePositions, seyeNumOfKeyFrames, currentFrame, lEyeXforms);
	EvaluateXformsAt(slHandKeyFrameValues, slHandKeyFramePositions, slHandNumOfKeyFrames, currentFrame, lHandXforms);
	EvaluateXformsAt(srHandKeyFrameValues, srHandKeyFramePositions, srHandNumOfKeyFrames, currentFrame, rHandXforms);


	draw_SnowMan(snomanXforms, botXforms, tumXforms, headXforms, lEyeXforms, lEyeXforms, noseXforms, lHandXforms, rHandXforms);

	draw_Ground();

	glFlush();
}

void reshape (int w, int h)
{
   	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (45., (GLfloat)w/h,1., 50.0);
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt(8,7.,17, 0,0,-100,0.,1.,0.);
}


void init(void){

	currentFrame = 0;

  //set the clear color to be aqua-blue
  glClearColor(0.,1.,1.0,1.0);
	glColor3f(1.,1.,1.);
  //  glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);


  
	smNumOfKeyFrames = 0;
	// Bouncing Snowy
	SetKeyFrame(0,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, -5.,7.,0.,0.,40.,20.,1.,1.,1.);
	SetKeyFrame(10,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 4.,0.,0.,0.,40.,20.,0.8,1.2,1.);
	SetKeyFrame(13,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 4.,0.,0.,0.,40.,0.,1.2,0.8,1.);
	SetKeyFrame(16,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 4.,0.,0.,0.,40.,-20.,0.8,1.2,1.);
	SetKeyFrame(26,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 8.,7.,0.,0.,40.,-20.,1.,1.,1.);
	SetKeyFrame(30,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 10.,7.,0.,0.,40.,20.,1.,1.,1.);
	SetKeyFrame(40,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 15.,0.,0.,0.,40.,20.,0.8,1.2,1.);
	
	//Cut, shot2
	SetKeyFrame(41,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 12.5,3.5,0.,0.,40.,20.,0.9,1.1,1.);
	SetKeyFrame(47,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 15.,0.,0.,0.,40.,20.,0.8,1.2,1.);
	SetKeyFrame(50,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 15.,0.,0.,0.,40.,0.,1.,1.,1.);
	SetKeyFrame(62,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 15.,0.,0.,0.,40.,0.,1.,1.,1.);

	// Snowy in free fall
	SetKeyFrame(70,smKeyFrameValues, smKeyFramePositions, &smNumOfKeyFrames, 15.,-10.,0.,0.,40.,0.,1,1.,1.);

	// keyframes for the head
	SetKeyFrame(0,sheadKeyFrameValues, sheadKeyFramePositions, &sheadNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.,1.,1.);
	SetKeyFrame(47,sheadKeyFrameValues, sheadKeyFramePositions, &sheadNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.,1.,1.);
	SetKeyFrame(55,sheadKeyFrameValues, sheadKeyFramePositions, &sheadNumOfKeyFrames, 0.,0.,0.,40.,-20.,0.,1.,1.,1.);
	SetKeyFrame(57,sheadKeyFrameValues, sheadKeyFramePositions, &sheadNumOfKeyFrames, 0.,0.,0.,0.,-20.,0.,1.,1.,1.);
	SetKeyFrame(70,sheadKeyFrameValues, sheadKeyFramePositions, &sheadNumOfKeyFrames, 0.,0.,0.,0.,-20.,0.,1.,1.,1.);

	//keyframes for the eyes
	SetKeyFrame(0,seyeKeyFrameValues, seyeKeyFramePositions, &seyeNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.,1.,1.);
	SetKeyFrame(55,seyeKeyFrameValues, seyeKeyFramePositions, &seyeNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.,1.,1.);
	SetKeyFrame(57,seyeKeyFrameValues, seyeKeyFramePositions, &seyeNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.4,1.4,1.2);
	SetKeyFrame(70,seyeKeyFrameValues, seyeKeyFramePositions, &seyeNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.4,1.4,1.2);

	// keyframes for the hands
	SetKeyFrame(62,slHandKeyFrameValues, slHandKeyFramePositions, &slHandNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.,1.,1.);
	SetKeyFrame(65,slHandKeyFrameValues, slHandKeyFramePositions, &slHandNumOfKeyFrames, 0.,0.,0.,0.,0.,-90.,1.,1.,1.);
	SetKeyFrame(70,slHandKeyFrameValues, slHandKeyFramePositions, &slHandNumOfKeyFrames, 0.,0.,0.,0.,0.,-90.,1.,1.,1.);

	// keyframes for the hands
	SetKeyFrame(62,srHandKeyFrameValues, srHandKeyFramePositions, &srHandNumOfKeyFrames, 0.,0.,0.,0.,0.,0.,1.,1.,1.);
	SetKeyFrame(65,srHandKeyFrameValues, srHandKeyFramePositions, &srHandNumOfKeyFrames, 0.,0.,0.,0.,0.,90.,1.,1.,1.);
	SetKeyFrame(70,srHandKeyFrameValues, srHandKeyFramePositions, &srHandNumOfKeyFrames, 0.,0.,0.,0.,0.,90.,1.,1.,1.);

	
  glutTimerFunc(SPEED, timer, 0);
  glColor3f(0.6,0.3,0.);
  glEnable(GL_DEPTH_TEST);
  
}


void main(int argc, char* argv[])
{

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Snowman - Take 2");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}