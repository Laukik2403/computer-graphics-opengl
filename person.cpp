#include<iostream>
#include<GL/glut.h>
using namespace std;

int x1,y1,limit,d1,r,s,s1;
int m,n,x,y;

void init()
{
    glClearColor(0,0,0,0);
    gluOrtho2D(-320,320,-240,240);
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

void mh(int x1,int y1,int d1)
{
    x1=x1+1;
    d1=d1+2*x1+1;
}

void md(int x1,int y1,int d1)
{
    x1=x1+1;
    y1=y1-1;
    d1=d1+2*x1-2*y1+2;
}

void mv(int x1,int y1,int d1)
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
                mh(x1,y1,d1);
            }
            else
            {
                md(x1,y1,d1);
            }
        }
        else if(d1>0)
        {
            s1=2*d1-2*x1-1;
            if(s1<=0)
            {
                md(x1,y1,d1);
            }
            else
            {
                mv(x1,y1,d1);
            }
        }
        else if(d1==0)
        {
            md(x1,y1,d1);
        }
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawquadrant();
    bresenham_circle();
    glFlush();

    glBegin(GL_POINTS);
        glVertex2i(m,n-r);
        glVertex2i(m,10);
    glEnd();
     glFlush();

    glBegin(GL_POINTS);
        glVertex2i(m,n-(r+10));
        glVertex2i(m+10,n-(r+20));
    glEnd();
     glFlush();

    glBegin(GL_POINTS);
        glVertex2i(m,n-(r+10));
        glVertex2i(m-10,n-(r+20));
    glEnd();
     glFlush();
}


int main(int argc,char **argv)
{
    cout<<"ENTER M COORDINATES"<<endl;
    cin>>m;
    cout<<"ENTER N COORDINATES"<<endl;
    cin>>n;
    cout<<"ENTER RADIUS "<<endl;
    cin>>r;

    glutInit(&argc,argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow("BRESENHAM CIRCLE");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
