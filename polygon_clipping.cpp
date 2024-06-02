#include<iostream>
#include<GL/glut.h>
#include<unistd.h>
using namespace std;

int x[15],y[15],m[30],xx[25],yy[25];
int xmin,xmax,ymin,ymax;
int i,n;

void init()
{
	glClearColor(1,0,1,0);
	gluOrtho2D(-320,320,-240,240);
}

void getdata()
{
	cout<<"ENTER THE WINDOW COORDINATES"<<endl;
	cin>>xmin>>ymin>>xmax>>ymax;
	cout<<"ENTER THE NUMBER OF VERTICES"<<endl;
	cin>>n;
	
	if(n<2)
	{
		cout<<"ENTER THE VERTICES GREATER THAN 2...."<<endl;
		exit(0);
	}
	else
	{
	for(i=0;i<n;i++)
	{
		cout<<"ENTER VERTICES :"<<i+1<<endl;
		cin>>x[i]>>y[i];
	}
	x[i]=x[0];
	y[i]=y[0];
    }
}

void display1()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
		for(i=0;i<n;i++)
		{
			glVertex2i(x[i],y[i]);
		}
	glEnd();
	
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(xmin,ymin);
		glVertex2i(xmax,ymin);
		glVertex2i(xmax,ymax);
		glVertex2i(xmin,ymax);
	glEnd();
	glFlush();
}

void clearscreen()
{
	sleep(2);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void slope()
{
	for(i=0;i<n;i++)
	{
	if((x[i+1]-x[i])==0)
	{
		m[i]=0;
	}
	else
	{
	    m[i]=(y[i+1]-y[i])/(x[i+1]-x[i]);	
	}
	}
}

void lclip()
{
	int k=0;
	slope();
	for(i=0;i<n;i++)
	{
		if(x[i]>xmin && x[i+1]>xmin)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
		}
		else if(x[i]>xmin && x[i+1]<xmin)
		{
			xx[k]=xmin;
			yy[k]=y[i]+m[i]*(xmin-x[i]);
			k++;	
		}
		else if(x[i]<xmin && x[i+1]>xmin)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
			
			xx[k]=xmin;
			yy[k]=y[i]+m[i]*(xmin-x[i]);
			k++;
		}
	}
	n=k;
	for(i=0;i<n;i++)
	{
		x[i]=xx[i];
		y[i]=yy[i];
	}
	x[i]=x[0];
	y[i]=y[0];
}

void rclip()
{
	int k=0;
	slope();
	for(i=0;i<n;i++)
	{
		if(x[i]<xmax && x[i+1]<xmax)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
		}
		else if(x[i]<xmax && x[i+1]>xmax)
		{
			xx[k]=xmax;
			yy[k]=y[i]+m[i]*(xmax-x[i]);
			k++;	
		}
		else if(x[i]>xmax && x[i+1]<xmax)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
			
			xx[k]=xmax;
			yy[k]=y[i]+m[i]*(xmax-x[i]);
			k++;
		}
	}
	n=k;
	for(i=0;i<n;i++)
	{
		x[i]=xx[i];
		y[i]=yy[i];
	}
	x[i]=x[0];
	y[i]=y[0];
}

void tclip()
{
	int k=0;
	slope();
	for(i=0;i<n;i++)
	{
		if(y[i]<ymax && y[i+1]<ymax)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
		}
		else if(y[i]<ymax && y[i+1]>ymax)
		{
			yy[k]=ymax;
			xx[k]=x[i]+(ymax-y[i])/m[i];
			k++;	
		}
		else if(y[i]>ymax && y[i+1]<ymax)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
			
			yy[k]=ymax;
			xx[k]=x[i]+(ymax-y[i])/m[i];
			k++;
		}
	}
	n=k;
	for(i=0;i<n;i++)
	{
		x[i]=xx[i];
		y[i]=yy[i];
	}
	x[i]=x[0];
	y[i]=y[0];
}

void bclip()
{
	int k=0;
	slope();
	for(i=0;i<n;i++)
	{
		if(y[i]>ymin && y[i+1]>ymin)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
		}
		else if(y[i]>ymin && y[i+1]<ymin)
		{
			yy[k]=ymin;
			xx[k]=x[i]+(ymin-y[i])/m[i];
			k++;	
		}
		else if(y[i]<ymin && y[i+1]>ymin)
		{
			xx[k]=x[i+1];
			yy[k]=y[i+1];
			k++;
			
			yy[k]=ymin;
			xx[k]=x[i]+(ymin-y[i])/m[i];
			k++;
		}
	}
	n=k;
	for(i=0;i<n;i++)
	{
		x[i]=xx[i];
		y[i]=yy[i];
	}
	x[i]=x[0];
	y[i]=y[0];
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	display1();
	clearscreen();
	lclip();
	display1();
	clearscreen();
	rclip();
	display1();
	clearscreen();
	tclip();
	display1();
	clearscreen();
	bclip();
	display1();
	glFlush();
}

int main(int argc,char **argv)
{
	getdata();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("polygonclipping");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
