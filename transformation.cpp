#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

float A[3][3];
float B[3][3];
float C[3][3];

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
		glVertex2i(0,-240);
		glVertex2i(0,240);
	glEnd();
}

void input()
{
	cout<<"ENTER THE MATRIX A"<<endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>A[i][j];	
		}
	}		
}

void drawpolygon(float final[3][3])
{
	glBegin(GL_POLYGON);
	for(int i=0;i<3;i++)
	{
			glVertex2f(final[i][0],final[i][1]);
	}
	glEnd();		
}

void multiply()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			C[i][j]=0;
			for(int k=0;k<3;++k)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}	
		}
	}	    	    
}

void scaling()
{
	float sx,sy;
	cout<<"ENTER THE SCALING FACTOR"<<endl;
	cin>>sx>>sy;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			B[i][j]=0;
		}
	}
	B[0][0]=sx;
	B[1][1]=sy;
	B[2][2]=1;
	multiply();
	cout<<"FINAL MATRIX IS :"<<endl;
	for (int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<C[i][j]<<"\t";
		}
	}
}

void translation()
{
	float tx,ty;
	cout<<"ENTER TRANSLATING FACTOR"<<endl;
	cin>>tx>>ty;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i==j)
			{
				B[i][j]=1;
			}
			else
			{
				B[i][j]=0;
			}
		}
	}
	B[0][2]=tx;
	B[1][2]=ty;
	multiply();
	cout<<"FINAL MATRIX IS :"<<endl;
	for (int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<C[i][j]<<"\t";
		}
	}
}

void rotation()
{
	float a;
	cout<<"ENTER THE ROTATION ANGLE :"<<endl;
	cin>>a;
	float b=a*3.14/180;
	B[0][0]=cos(b);
	B[0][1]=-sin(b);
	B[1][0]=sin(b);
	B[1][1]=cos(b);
	B[2][2]=1;
	multiply();
	cout<<"FINAL MATRIX IS :"<<endl;
	for (int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<C[i][j]<<"\t";
		}
	}
}

void reflectionX()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i==j)
			{
				B[i][j]=1;
			}
			else
			{
				B[i][j]=0;
			}
		}
	}
	B[1][1]=-1;
	multiply();
	cout<<"FINAL MATRIX IS :"<<endl;
	for (int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<C[i][j]<<"\t";
		}
	}	
}

void reflectionY()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i==j)
			{
				B[i][j]=1;
			}
			else
			{
				B[i][j]=0;
			}
		}
	}
	B[0][0]=-1;
	multiply();
	cout<<"FINAL MATRIX IS :"<<endl;
	for (int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<C[i][j]<<"\t";
		}
	}	
}

void reflectionXY()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i==j)
			{
				B[i][j]=-1;
			}
			else
			{
				B[i][j]=0;
			}
		}
	}
	B[2][2]=1;
	multiply();
	cout<<"FINAL MATRIX IS :"<<endl;
	for (int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<C[i][j]<<"\t";
		}
	}	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawquadrants();
	glColor3f(1,1,0);
	drawpolygon(A);
	glColor3f(0,0,1);
	drawpolygon(C);
	glFlush();
}

int main(int argc,char **argv)
{
	input();
	int ch;
	cout<<"WHICH OPERATION DO YOU PERFORM ?"<<endl;
	cout<<"\n1. scaling \n2.translation \n3. rotation \n4. reflection about X \n5. reflection about Y \n6. reflection about XY \n7. exit "<<endl;
	cin>>ch;
	switch(ch)
	{
		case 1:scaling();
				break;
				
		case 2:translation();
				break;
				
		case 3:rotation();
				break;
				
		case 4:reflectionX();
				break;
				
		case 5:reflectionY();
				break;
				
		case 6:reflectionXY();
				break;
				
		case 7:exit(0);
	}
	
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("TRANSFORMATION");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

