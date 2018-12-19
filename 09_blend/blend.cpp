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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_COLOR,GL_DST_COLOR);
    }

    void render(double elapse)override
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
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}

