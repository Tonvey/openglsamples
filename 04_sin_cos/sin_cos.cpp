#include "ApplicationBase.h"
#include <cmath>
void render()
{
    glutSwapBuffers();
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
        const int count = 100;
        const double pi = atan(1.)*4;
        const float r = 0.5;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,1,1);
        glBegin(GL_LINES);
        {
            glVertex2f(-1,0);
            glVertex2f(1,0);

            glVertex2f(0,-1);
            glVertex2f(0,1);
        }
        glEnd();

        //sin
        glColor3f(1.0,0,0);
        glBegin(GL_LINE_STRIP);
        {
            for(int i = 0; i < count ;++i)
            {
                float x = i*2.0/count-1.0;
                float y = sin(x*pi);
                MY_LOG_DEBUG("x:%f y:%f\n",x,y);
                glVertex2f(x,y);
            }
        }
        glEnd();
        //cos

        glColor3f(0.0,1,0);
        glBegin(GL_LINE_STRIP);
        {
            for(int i = 0; i < count ;++i)
            {
                float x = i*2.0/count-1.0;
                float y = cos(x*pi);
                MY_LOG_DEBUG("x:%f y:%f\n",x,y);
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
