#include "MyStudyHeaders.h"
#include <math.h>
#include <time.h>
typedef float mytime_t;
static mytime_t last_time;
static mytime_t elapse;
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

mytime_t updateElapse()
{
    clock_t this_time;
    this_time=clock();
    elapse = (mytime_t)(this_time-last_time)/CLOCKS_PER_SEC;
    last_time=this_time;
    return elapse;
}

void init(int argc , char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(512,512);
    glutCreateWindow(argv[0]);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glBlendFunc(GL_ONE,GL_DST_ALPHA);
    glutTimerFunc(1000/60,timeFunc,10);
}

void timeFunc(int value)
{
    //垂直同步
    glutTimerFunc(1000/60,timeFunc,10);
    updateElapse();
    render();
}

void render()
{
    //背景颜色灰色
    //glClearColor(0.5,0.5,0.5,1.0);
    glClearColor(0,0,0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // 设置光源 0.9, 0.9
    {
        GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 1.0f};
        // 设置光源位置
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

        GLfloat light_ambient[] = {0.0f, 1, 0, 1.0f};
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

        GLfloat light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

        GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    // 画个球
    {
        GLfloat light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT,    light_ambient);

        GLfloat light_diffuse[]   = {1.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    light_diffuse);

        GLfloat light_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR,   light_specular);

        GLfloat light_emission[] = {0.0f, 0.0f, 0.2f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION,   light_emission);

        GLfloat light_shininess   = 0.0f;
        glMaterialf (GL_FRONT, GL_SHININESS,  light_shininess);


        glColor3f(0.0f, 0.0f, 0.0f);
        glutSolidSphere(0.5, 200, 100);
    }

    glFlush();
    glutSwapBuffers();
}
void reshape(int width,int height)
{
}
void display()
{
}
void idle()
{
}
