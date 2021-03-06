/*This program draws a tree
using the following graftal :
	1. 0->1[0]1[0]0
	2. 1->11
	3. [->[
	4. ]->]
the axiom for this graftal is 0 

and grass using the following graftal :
	1. 0->1]1[0
	2. 1->1
	3. [->[
	4. ]->]
the axiom for this graftal is 1[0] 

compile using : gcc fifth_edited.c -lglut -lGLU -lGL -lm
*/

// This program uses the formula,
// T(n+1) = 1^(2^n).[T(n)].1^(2^n).[T(n)].T(n)

#include<GL/glut.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#define PI 3.1416

int pos;

// This function generates the string used to represent and draw the tree
// treeString = stores the previous generation which is updated into the current generation
// ruleForOne = production rule to replace '1'
// ruleForZero = production rule to replace '0'
// Assumption : Opening '[' and closing ']' braces stay as it is.

int genNextObjectString(char* treeString, char* ruleForOne, char* ruleForZero){

	int prevLen = strlen(treeString);
	if(prevLen > 1000000){
		printf("Memory!!");
		return -1;
	}
	char buffer[prevLen*10];
	buffer[0]=0;
	int iter = 0;
	int index = 0;
	while(iter < prevLen){
		if(treeString[iter] == '1'){
			strncat(buffer,ruleForOne,2);
		}
		else if(treeString[iter] == '0'){
			strncat(buffer,ruleForZero,9);
		}
		else{
			strncat(buffer,treeString+iter,1);
		}
		iter++;
	}
	strcpy(treeString,buffer);
	//printf("%s",treeString);
	return 0;
}

// Recursive function that actually draws the tree from output of 'genNextObjectString' function 
// level = depth of the current branch
// angle = angle of the current branch
// currX = x-coordinate of the tip of the current branch
// currY = y-coordinate of the tip of the current branch
// arr = output string of 'draw' function
// object = used to discriminate between various objects e.g. for tree it is = 1, for grass it is = 2,etc. 

void Display2(int level,float angle,float currX,float currY,char *arr,int object)		
{
	int count = 1;					//needed to alternate between left and right branch drawings

	//int size = 10/level;				//length of the stem to be drawn in the current branch
	int size = 10;
	for(;pos<strlen(arr);pos++)
	{
		if(arr[pos] == '1')			// '1' indicates that a stem in the current branch is to be drawn
		{
			glBegin(GL_LINES);				
				glVertex2f(currX,currY);
				glVertex2f(currX + size*cos((angle)*PI/180),currY + size*sin((angle)*PI/180));
				currX = currX + size*cos((angle)*PI/180);
				currY = currY + size*sin((angle)*PI/180);
			glEnd();
		}
		else if(arr[pos]=='[')			// '[' indicates that a new branch is about to start
		{
			if(count%2==1)			// for new left branches
			{
				if(angle!=180)		 
				{
					pos++;					
					Display2(level+1,angle+45,currX,currY,arr,object);
					count++;
				}
				else			// if current angle is 180 degrees, new branch must be right branch
				{
					pos++;					
					Display2(level+1,angle-45,currX,currY,arr,object);
					count++;
				}
			}
			else				// for new right branches
			{
				if(angle!=0)		
				{
					pos++;					
					Display2(level+1,angle-45,currX,currY,arr,object);
					count++;
				}
				else			// if current angle is 0 degrees, new branch must be left branch
				{
					pos++;					
					Display2(level+1,angle+45,currX,currY,arr,object);
					count++;
				}
			}			
		}
		else if(arr[pos]==']')			// indicates the end of the current branch
		{	
			if(object==1)	
			{		
				glPointSize(5.0);		// sets square fruit size to be = 5 pixels
			
				glColor3f(1.0,0.0,0.0);		// with RED color

				glBegin(GL_POINTS);			
					glVertex2f(currX,currY);	// draws the fruit				
				glEnd();

				glPointSize(1.0);		// switches point size back to 1 pixel
				glColor3f(0.0,1.0,0.0);		// switches color back to green	
			}

			return;
		}
	}
}

// This function makes use of the 'genNextObjectString' and 'Display2' functions

void Display(void)
{
	int i,j;
	float x = 0.0, y = 50.0;	

	glClear(GL_COLOR_BUFFER_BIT);			

	glColor3f(0.0,1.0,0.0);

	char arr[10000];		// array to store string representing the tree
	
	arr[0] = '\0';			// null termination

	for(i=0;i<3;i++)
	{
		char mainString[1000000]="0";	//the string that draws the tree initialised with axiom

		int gen1 = random()%3 + 1; 	// setting the generation of the object to be drawn
	
		for(j=0;j<=gen1;j++)
			genNextObjectString(mainString,"11","1[0]1[0]0");		//generating the generations 

		x+=125;				// updating the position of the current tree

		pos = 0;			// pos attribute to store how much of the tree has been traversed till now

		Display2(1,90.0,x,50.0,mainString,1); 	// Initial call to recursive function 'Display2' to draw trees
	}	

	x = 0;

	for(i=0;i<32;i++)
	{
		char mainString2[1000000]="1[0]";	//the string that draws the grass initialised with axiom	

		int gen2 = random()%4;			// setting the generation of the object to be drawn
					
		for(j=0;j<=gen2;j++)
			genNextObjectString(mainString2,"1","1]1[0");		//generating the generations

		x+=15;					// updating the position of the current grass

		pos = 0;				// pos attribute to store how much of the grass has been traversed till now
		
		Display2(1,90.0,x,50.0,mainString2,2);	// Initial call to recursive function 'Display2' to draw grass
	}	
		
	glFlush();			// forcibly write contents of the buffer to the viewport
}

void reshape(int w,int h)		// when window is reshaped, draw the tree again by resizing viewport accordingly 
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500,0.0,500);
}

void init(void)
{
	glClearColor(0.0,0.0,0.5,1.0);	//background color		
}

void main(int argc, char* argv[])
{	
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("My first opengl window");
	init();
	glutDisplayFunc(Display);	
	glutReshapeFunc(reshape);
	glutMainLoop();			//keep looping until the user exits
}








