#include<iostream>
#include<GL/glut.h>
#include<cmath>
#define PIE 3.14159
using namespace std;

int n;
float x1,Y1,x2,y2;
int x[4],y[4];

void init()
{
	glClearColor(0,0,0,0);
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

void koch(float xa,float ya,float xd,float yd,int n)
{
	float xc,yc,xb,yb,midx,midy;
	
	xb=(2*xa+xd)/3;
	yb=(2*ya+yd)/3;
	
	xc=(2*xd+xa)/3;
	yc=(2*yd+ya)/3;
	
	double angle=(-60*PIE)/180;
	
	midx=xb+((xc-xb)*cos(angle))+((yc-yb)*sin(angle));
	midy=yb-((xc-xb)*sin(angle))+((yc-yb)*cos(angle));
	
	if(n>0)
	{
		koch(xa,ya,xb,yb,n-1);
		koch(xb,yb,midx,midy,n-1);
		koch(midx,midy,xc,yc,n-1);
		koch(xc,yc,xd,yd,n-1);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
			glVertex2f(xa,ya);
			glVertex2f(xb,yb);
			glVertex2f(midx,midy);
			glVertex2f(xc,yc);
			glVertex2f(xd,yd);
		glEnd();	
	}	
}

void drawcurve(float a,float b)
{
	glBegin(GL_POINTS);
		glVertex2f(a,b);
	glEnd();
}

void bezier()
{
	double xt,yt;
	cout<<"ENTER NO. OF COORDINATES :"<<endl;
	cin>>n;
	
	for(int i=0;i<n;i++)
	{
	cout<<"ENTER THE X COORDINATES :"<<i+1<<endl;
	cin>>x[i];
	cout<<"ENTER THE Y COORDINATES :"<<i+1<<endl;
	cin>>y[i];
    }
    
	for(double u=0.0;u<1.0;u+=0.005)
	{
		xt=(x[3]*pow(u,3))+(3*x[2]*pow(u,2)*(1-u))+(3*x[1]*pow(1-u,2)*u)+(x[0]+pow(1-u,3));
		yt=(y[3]*pow(u,3))+(3*y[2]*pow(u,2)*(1-u))+(3*y[1]*pow(1-u,2)*u)+(y[0]+pow(1-u,3));
		drawcurve(xt,yt);
	}
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
	glMatrixMode(GL_MODELVIEW);
}

void draw()
{
	int ch;
	cout<<"1.BEZIER \n2. KOCH \n WHICH CURVE DO YOUO WANT TO DRAW :"<<endl;
	cin>>ch;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	switch(ch)
	{
		case 1: drawquadrant();
				bezier();
				break;
		
		case 2:
			cout<<"ENTER THE NO. OF ITERATIONS :"<<endl;
			cin>>n;
			
			cout<<"ENTER THE COORDINATES"<<endl;
			cin>>x1>>Y1;
			
			cout<<"ENTER THE COORDINATES :"<<endl;
			cin>>x2>>y2;
			
			koch(x1,Y1,x2,y2,n);
			break;
	}
	glFlush();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(300,50);
	glutCreateWindow("curve drawing");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
