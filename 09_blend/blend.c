#include "MyStudyHeaders.h"
#include <math.h>
static unsigned long frame=0;
static int days=0;


void render();
void reshape(int width,int height);
void display();
void idle();
void init(int argc,char **argv);
void timeFunc(int value);

void (*init_func)(int argc , char **argv)=init;
void (*display_func)()=display;
void (*reshape_func)(int,int)=reshape;
void (*idle_func)()=idle;

void init(int argc , char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(512,512);
    glutCreateWindow(argv[0]);
    //glEnable(GL_DEPTH_TEST);//深度测试会影响最后的绘图结果
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_DST_ALPHA);
    glutTimerFunc(1000/60,timeFunc,10);
}

void timeFunc(int value)
{
    ++frame;
    days++;
    glutTimerFunc(100,timeFunc,10);
    render();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glBegin(GL_QUADS);
    {
        //左下角四边形
        glColor4f(1.0,0,0,1.0);
        glVertex2f(-1.0,-1.0);
        glVertex2f(-1.0,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-1.0);

        //右上角四边形
        glColor4f(0.0,1,0,0.2);
        glVertex2f(-0.5,-0.5);
        glVertex2f(-0.5,1.0);
        glVertex2f(1.0,1.0);
        glVertex2f(1.0,-0.5);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}
void reshape(int width,int height)
{
//    MY_LOG_DEBUG("display:%ld\n",++frame);
    render();
}
void display()
{
//    MY_LOG_DEBUG("display:%ld\n",++frame);
    render();
}

void idle()
{
//    MY_LOG_DEBUG("idle:%ld\n",++frame);
    render();
}
