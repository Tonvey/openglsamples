#include "MyStudyHeaders.h"
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
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0,0);
    glBegin(GL_TRIANGLES);
    {
        glVertex2f(-0.5,0);
        glVertex2f(0.5,0);
        glVertex2f(0,0.5);
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
