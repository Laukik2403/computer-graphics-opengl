#include<iostream>
#include<GL/glut.h>
using namespace std;

float x1,x2,y1,y2,dx,dy,e;
int m,x,y;

void init()
{
	glClearColor(0,0,0,0);
	gluOrtho2D(-320,320,-240,240);
}

void drawquadrants()
{
	glBegin(GL_LINES);
		glVertex2i(320,0);
		glVertex2i(-320,0);
		glVertex2i(0,240);
		glVertex2i(0,-240);
	glEnd();
}

void bresenham()
{
	x=x1;
	y=y1;
	
	dx=x2-x1;
	dy=y2-y1;
	m=dy/dx;
	
	e=m-(1/2);
	
	for(int i=1;i<dx;i++)
	{
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		while(e>0)
		{
			y=y+1;
			e=e-1;
		}
		x=x+1;
		e=e+m;
	}
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawquadrants();
	bresenham();
}

int main(int argc,char **argv)
{
	cout<<"ENTER THE COORDINATES"<<endl;
	cin>>x1>>x2>>y1>>y2;
	
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("bresenham");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
