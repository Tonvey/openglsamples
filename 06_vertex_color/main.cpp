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
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
