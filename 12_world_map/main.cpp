#include "ApplicationBase.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <string>
#include "FileUtil.h"
#include "Texture.h"

#define WORLD_MAP_IMAG "world_map.bmp"
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

    void init() override
    {
        ApplicationBase::init();
        glEnable(GL_TEXTURE_2D);
        //开启剔除，如果不开剔除，将会导致图片错乱
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        texture = move(Texture(
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + WORLD_MAP_IMAG));
        this->earth_rot=0.;
    }

    void coordUV(int i , int j,  int slice)
    {
        glTexCoord2f(1.0*i/slice,1.0*j/slice);
    }

    void drawBall(float radius)
    {
        const int slice = 50;
        const float PI = atan(1.)*4;
        Point vertexes[slice+1][slice+1];
        int i,j;
        for(j=0;j<=slice;++j)
        {
            float theta = PI / slice * j;
            float y =  -cos(theta)*radius;
            float radius2 = radius * sin(theta);

            //画圆
            for(i = 0 ; i<= slice ; ++i)
            {
                float theta2 = 2*PI/slice*i;
                float x = radius2 * cos(theta2);
                float z = radius2 * sin(theta2);
                vertexes[i][j].x=x;
                vertexes[i][j].y=y;
                vertexes[i][j].z=z;
            }
        }

        glBegin(GL_QUADS);
        {
            for(i=0;i<slice;++i)
            {
                for(j=0;j<slice;++j)
                {
                    glBindTexture(GL_TEXTURE_2D,texture.id());
                    coordUV(i,j,slice);
                    glVertex3f(
                               vertexes[i][j].x,
                               vertexes[i][j].y,
                               vertexes[i][j].z
                               );
                    coordUV(i+1,j,slice);
                    glVertex3f(
                               vertexes[i+1][j].x,
                               vertexes[i+1][j].y,
                               vertexes[i+1][j].z
                               );
                    coordUV(i+1,j+1,slice);
                    glVertex3f(
                               vertexes[i+1][j+1].x,
                               vertexes[i+1][j+1].y,
                               vertexes[i+1][j+1].z
                               );
                    coordUV(i,j+1,slice);
                    glVertex3f(
                               vertexes[i][j+1].x,
                               vertexes[i][j+1].y,
                               vertexes[i][j+1].z
                               );
                }
            }
        }
        glEnd();
    }
    void render(double elapse)override
    {
        glClearColor(0,0,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        earth_rot += 10*elapse;
        glRotatef(earth_rot,0,1,0);

        glColor4f(1,1,1,1);

        drawBall(0.5);

        glfwSwapBuffers(this->mWindow);
    }
private:
    Texture texture;
    float earth_rot;
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
