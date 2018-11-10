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
    const int count = 5;
    const double pi = atan(1.)*4;
    const float r = 0.5;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0,0);
    glBegin(GL_LINE_LOOP);
    {
        for(int i = 0; i < count ;++i)
        {
            int v = i*2%5;
            float theta = (2*pi)/count*v + pi/2;
            float x = cos(theta)*r;
            float y = sin(theta)*r;
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
