#include "MyStudyHeaders.h"
#include <math.h>
static unsigned long frame=0;
void render();
void reshape(int width,int height);
void display();
void idle();

void (*init_func)(int argc , char **argv)=NULL;
void (*display_func)()=display;
void (*reshape_func)(int,int)=reshape;
void (*idle_func)()=idle;

void render()
{
    const int count = 100;
    const double pi = atan(1.)*4;
    const float r = 0.5;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1,1);
    glBegin(GL_LINES);
    {
        glVertex2f(-1,0);
        glVertex2f(1,0);

        glVertex2f(0,-1);
        glVertex2f(0,1);
    }
    glEnd();

    //sin
    glColor3f(1.0,0,0);
    glBegin(GL_LINE_STRIP);
    {
        for(int i = 0; i < count ;++i)
        {
            float x = i*2.0/count-1.0;
            float y = sin(x*pi);
            MY_LOG_DEBUG("x:%f y:%f\n",x,y);
            glVertex2f(x,y);
        }
    }
    glEnd();
    //cos

    glColor3f(0.0,1,0);
    glBegin(GL_LINE_STRIP);
    {
        for(int i = 0; i < count ;++i)
        {
            float x = i*2.0/count-1.0;
            float y = cos(x*pi);
            MY_LOG_DEBUG("x:%f y:%f\n",x,y);
            glVertex2f(x,y);
        }
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
}
void reshape(int width,int height)
{
    MY_LOG_DEBUG("display:%ld\n",++frame);
    render();
}
void display()
{
    MY_LOG_DEBUG("display:%ld\n",++frame);
    render();
}

void idle()
{
    MY_LOG_DEBUG("idle:%ld\n",++frame);
    render();
}
