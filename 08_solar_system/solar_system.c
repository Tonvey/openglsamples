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

typedef struct Point
{
    float x;
    float y;
    float z;
} Point;
void init(int argc , char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(512,512);
    glutCreateWindow(argv[0]);
    glEnable(GL_DEPTH_TEST);
    glutTimerFunc(1000/60,timeFunc,10);
}

void timeFunc(int value)
{
    ++frame;
    days++;
    glutTimerFunc(100,timeFunc,10);
    render();
}

void drawBall(float radius,float r,float g,float b)
{
    const int count = 20;
    Point ps[count][count];
    const double PI = atan(1.)*4;
    glColor3f(r, g, b);
    for(int i=0;i <count; i++)
    {
        float theta = (2*PI) / count * i;
        float r1 = sin(theta) * radius;
        float y = cos(theta) * radius;
        for(int j=0; j<count; ++j)
        {
            float theta = (2*PI) /count * j;
            float x = cos(theta) * r1;
            float z = sin(theta) * r1;
            // 得到了一个点
            ps[i][j].x = x;
            ps[i][j].y = y;
            ps[i][j].z = z;
        }
    }

    // 第一行的点和第二行的点，组成一个GL_QUAD_STRIP
    // 第二行点和第三行点，组成一个GL_QUAD_STRIP
    for(int i=0; i<count-1; ++i)
    {
        glBegin(GL_QUAD_STRIP);
        for(int j=0; j<count; ++j)
        {
            glVertex3f(ps[i][j].x, ps[i][j].y, ps[i][j].z);
            glVertex3f(ps[i+1][j].x, ps[i+1][j].y, ps[i+1][j].z);
        }
        glEnd();
    }

}
void render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.1f, 10.f);
    gluLookAt(0.0f, 1.0f,1.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    //sun static
    glTranslatef(0,0,0);
    glPushMatrix();
    drawBall(0.2,1,0,0);

    //earth 
    glRotatef(10*days,0,1,0);
    glTranslatef(0.5,0,0);
    glPushMatrix();
    drawBall(0.1,0,0,1);

    //moon
    glRotatef(20*days,0,1,0);
    glTranslatef(0.2,0,0);
    drawBall(0.05,0,1,0);


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
