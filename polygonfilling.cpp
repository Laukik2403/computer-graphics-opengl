#include<iostream>
#include<GL/glut.h>
using namespace std;

int fillflag=0;
float bgcolor[3]={0.0,1.0,1.0};
float bdcolor[3]={0.0,0.0,1.0};
float fillclr[3]={1.0,0.0,0.0};

void setpixel(int x,int y,float f[3])
{
	glBegin(GL_POINTS);
		glColor3fv(f);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void getpixel(int x,int y,float pixel[3])
{
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixel);
}

void drawpolygon(int x1,int x2,int y1,int y2)
{
	glColor3fv(bdcolor);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1,y1);
		glVertex2i(x1,y2);
		glVertex2i(x2,y2);
		glVertex2i(x2,y1);
	glEnd();
	glFlush();
}

void display()
{
	glClearColor(0.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawpolygon(150,200,200,250);
	glFlush();
}
void floodfill(int x,int y,float fillcolor[3],float oldcolor[3])
{
	float color[3];
	getpixel(x,y,color);
	if(color[0]==oldcolor[0] && color[1]==oldcolor[1]  && color[2]==oldcolor[2])
	{
		setpixel(x,y,fillcolor);
		floodfill(x,y-1,fillcolor,oldcolor);
		floodfill(x,y+1,fillcolor,oldcolor);
		floodfill(x+1,y,fillcolor,oldcolor);
		floodfill(x-1,y,fillcolor,oldcolor);
	}	
}

void boundaryfill(int x,int y, float fillcolor[3],float bdcolor[3])
{
	float color[3];
	getpixel(x,y,color);
	if(((color[0] != fillcolor[0]) || (color[1] != fillcolor[1]) || (color[2] != fillcolor[2])) && ((color[0] != bdcolor[0]) || (color[1] != bdcolor[1]) || (color[2] != bdcolor[2])))
	{
		setpixel(x,y,fillcolor);
		boundaryfill(x,y-1,fillcolor,bdcolor);
		boundaryfill(x,y+1,fillcolor,bdcolor);
		boundaryfill(x+1,y,fillcolor,bdcolor);
		boundaryfill(x-1,y,fillcolor,bdcolor);
		boundaryfill(x+1,y-1,fillcolor,bdcolor);
		boundaryfill(x-1,y-1,fillcolor,bdcolor);
		boundaryfill(x+1,y+1,fillcolor,bdcolor);
		boundaryfill(x-1,y-1,fillcolor,bdcolor);		
	} 
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		int xi=x;
		int yi=480-y;
		if(fillflag==1)
			floodfill(xi,yi,fillclr,bgcolor);
		else if(fillflag==2)
			boundaryfill(xi,yi,fillclr,bdcolor);
	}
}

void fillmenu(int option)
{
	if(option==1)
		fillflag=1;
	else if(option==2)
		fillflag=2;
}

void init()
{
	gluOrtho2D(0,640,0,480);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(200,200);
	glutCreateWindow("POLYGON FILLING");
	init();
	glutDisplayFunc(display);
	
	glutCreateMenu(fillmenu);
	glutAddMenuEntry("floodfill",1);
	glutAddMenuEntry("boundaryfill",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}


