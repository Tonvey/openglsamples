#include "ApplicationBase.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include "TextureLoader.h"
#include "FileUtil.h"
using namespace std;

class Application: public ApplicationBase
{
public:
    struct MyTexture
    {
        GLuint name;
        GLuint width;
        GLuint height;
        ~MyTexture()
        {
            if(glIsTexture(this->name)==GL_TRUE)
            {
                cout<<"Delete texture"<<endl;
                glDeleteTextures(1,&this->name);
            }
        }
    };
    typedef unique_ptr<MyTexture> TexturePtr ;

    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
    }

    void init()override
    {
        ApplicationBase::init();
        glEnable(GL_TEXTURE_2D);
        texture = loadBMPTexture(
        FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + "panda.bmp");
    }

    TexturePtr loadBMPTexture(string fileName)
    {
        TextureLoader loader(fileName);
        TexturePtr t(new MyTexture);
        t->width = loader.width();
        t->height = loader.height();

        glGenTextures(1,&t->name);
        glBindTexture(GL_TEXTURE_2D,t->name);
        MY_LOG_DEBUG("%d %d %d \n",loader.width(),loader.height(),loader.channelCount());

        // 纹理设置
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        // 把内存中的图像信息，发送给显卡
        glTexImage2D(
                     GL_TEXTURE_2D,
                     0,
                     loader.mode(),
                     t->width,
                     t->height,
                     0,
                     loader.mode(),
                     GL_UNSIGNED_BYTE,
                     loader.data());

        return t;
    }
    void render(double elapse)override
    {
        //背景颜色灰色
        //glClearColor(0.5,0.5,0.5,1.0);
        glClearColor(0,0,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D,texture->name);

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
    TexturePtr texture;
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
	return app.run();
}
