#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

void init()
{
	glClearColor(0,0,0,0);
	gluOrtho2D(0,640,0,480);
}

void drawquadrant()
{
	glBegin(GL_LINES);
		glVertex2i(320,0);
		glVertex2i(-320,0);
		glVertex2i(0,-240);
		glVertex2i(0,240);
	glEnd();
}

void bezier()
{
	double x1,x2,x3,x4;
	double y1,y2,y3,y4;
	double xt,yt;
	
	cout<<"ENTER THE FOUR COORDINATES"<<endl;
	cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
	
	for(int u=0.0;u<1.0;u+=0.005)
	{
		xt=pow(u,3)*x4+(3*x3*pow(u,3)*(1-u))+(3*x2*pow(u,2)*pow(1-u,2))+(x1*u*pow(1-u,3));
		yt=pow(u,3)*y4+(3*y3*pow(u,3)*(1-u))+(3*y2*pow(u,2)*pow(1-u,2))+(y1*u*pow(1-u,3));
		
		glBegin(GL_POINTS);
			glVertex2f(xt,yt);
		glEnd();	
	}
	
	glBegin(GL_LINES);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
		glVertex2i(x3,y3);
		glVertex2i(x4,y4);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawquadrant();
	bezier();
	glFlush();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("bezier");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
