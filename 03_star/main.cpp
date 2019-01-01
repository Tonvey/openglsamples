#include "ApplicationBase.h"
#include <cmath>
void render()
{
}

class Application: public ApplicationBase
{
public:
    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
    }

    void render(double elapse)override
    {
        const int count = 5;
        const double pi = atan(1.)*4;
        const float r = 0.5;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,0,0);
        glBegin(GL_LINE_LOOP);
        {
            for(int i = 0; i < count ;++i)
            {
                int v = i*2%5;
                float theta = (2*pi)/count*v + pi/2;
                float x = cos(theta)*r;
                float y = sin(theta)*r;
                glVertex2f(x,y);
            }
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
