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
    //const double pi = atan(1.)*4;
    //const float r = 0.5;
    glClearColor(0.2,0.2,0.2,0.2);
    glClear(GL_COLOR_BUFFER_BIT);

    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1,0,0);
        glVertex2f(-0.5,-0.3);
        glColor3f(0,1,0);
        glVertex2f(0.5,-0.3);
        glColor3f(0,0,1);
        glVertex2f(0,0.3);
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
