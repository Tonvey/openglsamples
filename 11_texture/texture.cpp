#include "ApplicationBase.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>
using namespace std;

class Application: public ApplicationBase
{
public:
    struct MyTexture
    {
        GLuint name;
        GLuint width;
        GLuint height;
    };

    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
        glEnable(GL_TEXTURE_2D);
        texture = loadBMPTexture("./11_texture/panda.bmp");
    }

    MyTexture loadBMPTexture(const char *fileName)
    {
        MyTexture t;
        FILE *fp = fopen(fileName ,"rb");
        if(!fp)
        {
            perror("fopen");
            exit(1);
        }

        //跳过前面bmp文件头部
        char header[54];
        fread(header,54,1,fp);
        // 数据格式
        // 宽度和高度
        t.width = *(int*)(header + 0x12);
        t.height = *(int*)(header + 0x16);
        int bytes = (t.width) * (t.height) * 3;
        char* data = new char[bytes];
        unique_ptr<char[]> dataGuard(data);
        fread(data, bytes, 1, fp);
        fclose(fp);

        glGenTextures(1,&t.name);
        glBindTexture(GL_TEXTURE_2D,t.name);

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
                     GL_RGB,
                     t.width,
                     t.height,
                     0,
                     GL_BGR,
                     GL_UNSIGNED_BYTE,
                     data);

        return t;
    }
    void render(double elapse)override
    {
        //背景颜色灰色
        //glClearColor(0.5,0.5,0.5,1.0);
        glClearColor(0,0,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D,texture.name);

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
    MyTexture texture;
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
	return app.run();
}
