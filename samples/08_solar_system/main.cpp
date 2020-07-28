#include "ApplicationBase.h"
#include <cmath>
using namespace std;

class Application: public ApplicationBase
{
public:
    struct Point
    {
        float x;
        float y;
        float z;
    };

    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
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
    void render(double elapse)override
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
        static float earth_rot=0;
        earth_rot += 40*elapse;
        glRotatef(earth_rot,0,1,0);
        glTranslatef(0.5,0,0);
        glPushMatrix();
        drawBall(0.1,0,0,1);

        //moon
        static float moon_rot=0;
        moon_rot += 80*elapse;
        glRotatef(moon_rot,0,1,0);
        glTranslatef(0.2,0,0);
        drawBall(0.05,0,1,0);

        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
