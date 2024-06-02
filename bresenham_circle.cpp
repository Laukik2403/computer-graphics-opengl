#include<iostream>
#include<GL/glut.h>
using namespace std;

int x1,y1,r,limit,d1,s,s1,m,n;

void init()
{
	glClearColor(1,0,1,0);
	gluOrtho2D(-320,320,-240,240);
}

void drawquadrant()
{
	glBegin(GL_LINES);
		glVertex2i(-320,0);
		glVertex2i(320,0);
		glVertex2i(0,-240);
		glVertex2i(0,240);
	glEnd();
}

void submh(int& x1,int& y1,int& d1)
{
	x1=x1+1;
	d1=d1+2*x1+1;
}

void submd(int& x1,int& y1,int& d1)
{
	x1=x1+1;
	y1=y1-1;
	d1=d1+2*x1-2*y1+2;
}

void submv(int& x1,int& y1,int& d1)
{
	y1=y1-1;
	d1=d1-2*y1+1;
}

void bresenham_circle()
{
	x1=0;
	y1=r;
	d1=2*(1-r);
	limit=0;
	while(y1>=limit)
	{
		glBegin(GL_POINTS);
			glVertex2i(x1+m,y1+n);
			glVertex2i(-x1+m,y1+n);
			glVertex2i(x1+m,-y1+n);
			glVertex2i(-x1+m,-y1+n);
		glEnd();
		
		if(d1<0)
		{
			s=2*d1+2*y1-1;
			if(s<=0)
			{
				submh(x1,y1,d1);
			}
			else
			{
				submd(x1,y1,d1);
			}
		}
		else if(d1>0)
		{
			s1=2*d1-2*x1-1;
			if(s1<=0)
			{
				submd(x1,y1,d1);
			}
			else
			{
				submv(x1,y1,d1);
			}
		}
		else if(d1==0)
		{
			submd(x1,y1,d1);
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawquadrant();
	bresenham_circle();
	glFlush();
}

int main(int argc,char **argv)
{
	cout<<"ENTER X COORDINATES"<<endl;
	cin>>m;
	cout<<"ENTER Y COORDINATES"<<endl;
	cin>>n;
	cout<<"ENTER RADIUS:"<<endl;
	cin>>r;
	
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("bresenham circle");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
