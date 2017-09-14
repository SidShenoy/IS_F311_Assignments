/*This program draws a tree
using the following graftal :
	1. 0->1[0]1[0]0
	2. 1->11
	3. [->[
	4. ]->]
the axiom for this graftal is 0 
compile using : gcc fifth.c -lglut -lGLU -lGL -lm
*/

// This program uses the formula,
// T(n+1) = 1^(2^n).[T(n)].1^(2^n).[T(n)].T(n)

#include<GL/glut.h>
#include<math.h>
#include<string.h>
#define PI 3.1416

int pos;

void draw(int gen, char *arr)
{
	int i;

	int ones = pow(2,gen-1);	//Computes the number of 1s to be added = 1^(2^n)

	int len = strlen(arr);		//Computes the length of T(n-1)

	int count = ones * 2 + 5 + 3 * len; //one extra for terminating null character

	char arr2[len];

	if(len==0)
	{
		arr[0] = '0';		//arr is now equal to axiom
		arr[1] = '\0';		//null termination
	}

	if(gen==0)
	return;	

	else
	{
		for(i=0;i<len;i++)
		{
			arr2[i] = arr[i];				//before T(n-1) is modified into T(n), we make a copy of T(n-1)
		}

		for(i=0;i<count-1;i++)
		{	
			if((i>=0 && i<ones) || (i>=ones+len+2 && i<ones*2+len+2))	//Add 1s according to formula
			arr[i] = '1';
			else if((i == ones) || (i == ones*2+len+2))			//Add [s according to formula
			arr[i] = '[';
			else if((i == ones + len + 1)||(i == ones*2+len*2+3))		//Add ]s according to formula
			arr[i] = ']';
			else if((i >= ones + 1 && i <= ones + len))			//Add T(n-1), first occurrence
			{
				arr[i] = arr2[i-ones-1];
			}
			else if((i >= ones*2+len+3) && (i<=ones*2+len*2+2))		//Add T(n-1), second occurrence
			{
				arr[i] = arr2[i-ones*2-len-3];
			}
			else								//Add T(n-1), third occurrence
			{
				arr[i] = arr2[i-ones*2-len*2-4];
			}
		}

		arr[count-1] = '\0';							//null termination of T(n)

	}
}

// Recursive function that actually draws the tree from output of 'draw' function 
// level = depth of the current branch
// angle = angle of the current branch
// currX = x-coordinate of the tip of the current branch
// currY = y-coordinate of the tip of the current branch
// arr = output string of 'draw' function 

void Display2(int level,float angle,float currX,float currY,char *arr)		
{
	int count = 1;					//needed to alternate between left and right branch drawings

	int size = 10/level;				//length of the stem to be drawn in the current branch

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
					Display2(level+1,angle+45,currX,currY,arr);
					count++;
				}
				else			// if current angle is 180 degrees, new branch must be right branch
				{
					pos++;					
					Display2(level+1,angle-45,currX,currY,arr);
					count++;
				}
			}
			else				// for new right branches
			{
				if(angle!=0)		
				{
					pos++;					
					Display2(level+1,angle-45,currX,currY,arr);
					count++;
				}
				else			// if current angle is 0 degrees, new branch must be left branch
				{
					pos++;					
					Display2(level+1,angle+45,currX,currY,arr);
					count++;
				}
			}			
		}
		else if(arr[pos]==']')			// indicates the end of the current branch
		{	
			glPointSize(5.0);		// sets square fruit size to be = 5 pixels
			
			glColor3f(1.0,0.0,0.0);		// with RED color

			glBegin(GL_POINTS);			
				glVertex2f(currX,currY);	// draws the fruit				
			glEnd();

			glPointSize(1.0);		// switches point size back to 1 pixel
			glColor3f(0.0,1.0,0.0);		// switches color back to green	

			return;
		}
	}
}

void Display(void)
{
	int i;
	float x = 80.0, y = 60.0;	

	glClear(GL_COLOR_BUFFER_BIT);			

	glColor3f(0.0,1.0,0.0);

	char arr[10000];		// array to store string representing the tree
	
	arr[0] = '\0';			// null termination

	int gen = 4;			// setting the generation of the tree to be drawn
	
	for(i=0;i<=gen;i++)
	draw(i,arr);

	pos = 0;			// pos attribute to store how much of the tree has been traversed till now

	Display2(1,90.0,250.0,50.0,arr); // Initial call to recursive function 'Display2'	
		
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








