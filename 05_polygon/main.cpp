#include "ApplicationBase.h"
#include <cmath>

using namespace std;

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


        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,1,1);

        //开启剔除
        glEnable(GL_CULL_FACE);
        //剔除正面
        //glCullFace(GL_FRONT);
        //剔除反面 
        //glCullFace(GL_BACK);

        glBegin(GL_TRIANGLES);
        //顺时针方向画图形
        {
            glVertex2f(0,0);
            glVertex2f(0.3,0.8);
            glVertex2f(0.5,0.5);
        }
        glEnd();

        glBegin(GL_TRIANGLES);
        //逆时针
        {
            glVertex2f(0,0);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.3,-0.8);
        }
        glEnd();

        //设置正反面
        //glFrontFace(GL_CCW);//逆时针counter clock wise
        //glFrontFace(GL_CW);//顺时针

        //    glPolygonMode(GL_FRONT,GL_LINE); //正面使用线条
        //    glPolygonMode(GL_BACK,GL_FILL);//背面使用填充模式

        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
