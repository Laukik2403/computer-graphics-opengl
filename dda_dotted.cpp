#include<iostream>
#include<GL/glut.h>
using namespace std;

float x1,x2,y1,y2,dx,dy,length;
int x,y;

 void init()
 {
 	glClearColor(0,0,0,0);
 	gluOrtho2D(-320,320,-240,240);
 }
 
 void drawquadrants()
 {
 	glBegin(GL_LINES);
 		glVertex2i(-320,0);
 		glVertex2i(320,0);
 		glVertex2i(0,240);
 		glVertex2i(0,-240);
 	glEnd();
 }
 
 void dda()
 {
 	if(abs(x2-x1)>abs(y2-y1))
 		length=abs(x2-x1);
 	else
 		length=abs(y2-y1);
 		
 	dx=(x2-x1)/length;
 	dy=(y2-y1)/length;
 	
 	x=x1+0.5;
 	y=y1+0.5;
 	
 	int i=0;
 	while(i<=length)
 		{
 			if(x%2==0)
 			{
 			glBegin(GL_POINTS);
 				glVertex2i(x,y);
			glEnd();
		    }
			y=y+dy;
			x=x+dx;
			i=i+1;		
		}
		glFlush();
 }
 
 void display()
 {
 	glClear(GL_COLOR_BUFFER_BIT);
 	drawquadrants();
 	dda();
 }
 
 int main(int argc,char **argv)
 {
 	
 	cout<<"ENTER COORDINATES"<<endl;
 	cin>>x1;
 	cin>>x2;
 	cin>>y1;
 	cin>>y2;
 	
 	glutInit(&argc,argv);
 	glutInitWindowSize(640,480);
 	glutInitWindowPosition(100,100);
 	glutCreateWindow("DDA");
	init();
 	glutDisplayFunc(display);
 	glutMainLoop();
 	return 0;
 }
