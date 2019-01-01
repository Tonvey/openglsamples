#include "ApplicationBase.h"
#include <cmath>
class Application: public ApplicationBase
{
public:
    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
    }

    void render(double elapse)override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glShadeModel(GL_SMOOTH);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, 1, 0.1f, 10.f);
        gluLookAt(0.0f, 0.0f,1.0f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, -1.0f);
        //glViewport(0, 0, 400, 400);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(0,0,-0.5);
        glBegin(GL_TRIANGLES);
        {
            glColor3f(1,0,0);
            glVertex3f(-0.5,-0.3,0);
            glVertex3f(0.5,-0.3,0);
            glVertex3f(0,0.3,0);
        }
        glEnd();
        glPopMatrix();

        //右手坐标系的旋转
        glPushMatrix();
        glLoadIdentity();
        glRotatef(30,0,0,1);
        glBegin(GL_TRIANGLES);
        {
            glColor3f(0,1,0);
            glVertex3f(-0.5,-0.3,0);
            glVertex3f(0.5,-0.3,0);
            glVertex3f(0,0.3,0);
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glLoadIdentity();
        glTranslatef(-0.5,0,0);
        glScalef(1,0.5,0.5);
        glRotatef(30,0,0,1);
        glBegin(GL_TRIANGLES);
        {
            glColor3f(0,0,1);
            glVertex3f(-0.5,-0.3,0);
            glVertex3f(0.5,-0.3,0);
            glVertex3f(0,0.3,0);
        }
        glEnd();
        glPopMatrix();
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
