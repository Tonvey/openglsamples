#include "ApplicationBase.h"
#include <iostream>
#include <cmath>
using namespace std;

class Application: public ApplicationBase
{
public:
    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
    }
    void init()override
    {
        ApplicationBase::init();
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

    void render(double elapse)override
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
        glfwSwapBuffers(this->mWindow);

    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}

