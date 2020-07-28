#include "ApplicationBase.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include "Texture.h"
#include "FileUtil.h"
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
        glEnable(GL_TEXTURE_2D);
        texture = move(Texture(
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + "panda.bmp"));
    }

    void render(double elapse)override
    {
        //背景颜色灰色
        //glClearColor(0.5,0.5,0.5,1.0);
        glClearColor(0,0,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D,texture.id());

        glBegin(GL_QUADS);
        {
            glTexCoord2f(0.0,0.0);
            glVertex2f(0,0);

            glTexCoord2f(1.0,0.0);
            glVertex2f(1,0);

            glTexCoord2f(1.0,1.0);
            glVertex2f(1,1);

            glTexCoord2f(0.0,1.0);
            glVertex2f(0,1);
        }
        glEnd();

        glfwSwapBuffers(this->mWindow);
    }
private:
    Texture texture;
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
	return app.run();
}
