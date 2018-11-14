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
    glClear(GL_COLOR_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0.2,-0.5);
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
    glPopMatrix();


    //右手坐标系的旋转
    glPushMatrix();
    glRotatef(30,0,0,1);
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
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,0,0);
    glScalef(1,0.5,0.5);
    glRotatef(30,0,0,1);
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
    glPopMatrix();

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
