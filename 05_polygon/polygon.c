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


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1,1);


    glBegin(GL_TRIANGLES);
    //顺时针方向画图形
    {
        glVertex2f(0,0);
        glVertex2f(0.3,0.8);
        glVertex2f(0.5,0.5);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    //逆时针
    {
        glVertex2f(0,0);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.3,-0.8);
    }
    glEnd();

    glPolygonMode(GL_FRONT,GL_LINE); //正面使用线条
    glPolygonMode(GL_BACK,GL_FILL);//背面使用填充模式

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
