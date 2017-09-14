/*This program draws a tree
using the following graftal :
	1. 0->1[0]1[0]0
	2. 1->11
	3. [->[
	4. ]->]
the axiom for this graftal is 0 
compile using : gcc fifth.c -lglut -lGLU -lGL -lm
*/

#include<GL/glut.h>
#include<math.h>
#include<string.h>
#define PI 3.1416

int pos;

void draw(int gen, char *arr)
{
	int i;

	int ones = pow(2,gen-1);	

	int len = strlen(arr);

	int count = ones * 2 + 5 + 3 * len; //one extra for terminating null character

	char arr2[len];

	if(len==0)
	{
		arr[0] = '0';
		arr[1] = '\0';
	}

	if(gen==0)
	return;	

	else
	{
		for(i=0;i<len;i++)
		{
			arr2[i] = arr[i];
		}

		for(i=0;i<count-1;i++)
		{	
			if((i>=0 && i<ones) || (i>=ones+len+2 && i<ones*2+len+2))
			arr[i] = '1';
			else if((i == ones) || (i == ones*2+len+2))
			arr[i] = '[';
			else if((i == ones + len + 1)||(i == ones*2+len*2+3))
			arr[i] = ']';
			else if((i >= ones + 1 && i <= ones + len))
			{
				arr[i] = arr2[i-ones-1];
			}
			else if((i >= ones*2+len+3) && (i<=ones*2+len*2+2))
			{
				arr[i] = arr2[i-ones*2-len-3];
			}
			else
			{
				arr[i] = arr2[i-ones*2-len*2-4];
			}
		}

		arr[count-1] = '\0';

	}
}

void Display2(int level,float angle,float currX,float currY,char *arr)
{
	int count = 1;

	int size = 10/level;	

	for(;pos<strlen(arr);pos++)
	{
		if(arr[pos] == '1')
		{
			glBegin(GL_LINES);				
				glVertex2f(currX,currY);
				glVertex2f(currX + size*cos((angle)*PI/180),currY + size*sin((angle)*PI/180));
				currX = currX + size*cos((angle)*PI/180);
				currY = currY + size*sin((angle)*PI/180);
			glEnd();
		}
		else if(arr[pos]=='[')
		{
			if(count%2==1)
			{
				if(angle!=180)
				{
					pos++;					
					Display2(level+1,angle+45,currX,currY,arr);
					count++;
				}
				else
				{
					pos++;					
					Display2(level+1,angle-45,currX,currY,arr);
					count++;
				}
			}
			else
			{
				if(angle!=0)
				{
					pos++;					
					Display2(level+1,angle-45,currX,currY,arr);
					count++;
				}
				else
				{
					pos++;					
					Display2(level+1,angle+45,currX,currY,arr);
					count++;
				}
			}			
		}
		else if(arr[pos]==']')
		{	
			glPointSize(5.0);
			
			glColor3f(1.0,0.0,0.0);

			glBegin(GL_POINTS);			
				glVertex2f(currX,currY);				
			glEnd();

			glPointSize(1.0);
			glColor3f(0.0,1.0,0.0);			

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

	char arr[10000];
	
	arr[0] = '\0';

	int gen = 4;
	
	for(i=0;i<=gen;i++)
	draw(i,arr);

	pos = 0;

	Display2(1,90.0,250.0,50.0,arr);
		
	glFlush();
}

void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500,0.0,500);
}

void init(void)
{
	glClearColor(0.0,0.0,0.5,1.0);
	glPointSize(5.0);
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
	glutMainLoop();
}








