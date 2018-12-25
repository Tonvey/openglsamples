#include "ApplicationBase.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include "FileUtil.h"
using namespace std;

#define VERTEX_FILE_NAME "shader.vert"
#define FRAG_FILE_NAME "shader.frag"

class Application: public ApplicationBase
{
public:
    struct MyTexture
    {
        GLuint name;
        GLuint width;
        GLuint height;
    };
private:
    GLuint myProgramId;
    GLuint vertexPosition_modelspaceID;
    GLuint coord_modelspaceID;
    GLuint vertexbuffer;
    GLuint uvBuffer;
    GLuint textureId;
    MyTexture texture;
public:

    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
        this->mGLMajorVersion=4;
        this->mGLMajorVersion=1;
    }
    int init()override
    {
        ApplicationBase::init();

        //加载shader
        myProgramId = loadShader(
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + VERTEX_FILE_NAME,
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + FRAG_FILE_NAME
        );

        //加载纹理图片
        glEnable(GL_TEXTURE_2D);
        texture = loadBMPTexture(
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + "panda.bmp");
        glEnable(texture.name);


        vertexPosition_modelspaceID = 
            glGetAttribLocation(myProgramId,"vertexPosition");
        coord_modelspaceID = 
            glGetAttribLocation(myProgramId,"coord");
        textureId = 
            glGetAttribLocation(myProgramId,"myTextureSampler");

        const GLfloat vertexBufferData[]={
            0.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,1.0f,0.0f,
            0.0f,1.0f,0.0f,
        };
        const GLfloat uvBufferData[]={
            0.0f,0.0f,
            1.0f,0.0f,
            1.0f,1.0f,
            0.0f,1.0f,
        };

        //------------------------------------------------------------------
        //在显卡中申请内存，内存句柄是vertexbuffer
        glGenBuffers(1,&vertexbuffer);
        //对vertexbuffer进行操作
        glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
        //把顶点坐标g_vertex_buffer_data传递到显卡，保存到vertexbuffer中
        glBufferData(
                     GL_ARRAY_BUFFER,
                     sizeof(vertexBufferData),
                     vertexBufferData,
                     GL_STATIC_DRAW
                     );

        //------------------------------------------------------------------
        glGenBuffers(1,&uvBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,uvBuffer);
        glBufferData(
                     GL_ARRAY_BUFFER,
                     sizeof(uvBufferData),
                     uvBufferData,
                     GL_STATIC_DRAW
                     );
        return 0;
    }
    MyTexture loadBMPTexture(string fileName)
    {
        MyTexture t;
        FILE *fp = fopen(fileName.c_str(),"rb");
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
        //glActiveTexture(t.name);

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
        glGenerateMipmap(t.name);
        return t;
    }
    void render(double elapse) override
    {
        glClearColor(0,0,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        //使用shader程序
        glUseProgram(myProgramId);

        //启用顶点属性
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);

        //指定渲染时候，怎么对属性进行设置
        glVertexAttribPointer(
            vertexPosition_modelspaceID,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        //启用顶点坐标属性
        glEnableVertexAttribArray(coord_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER,uvBuffer);
        //指定渲染时候，怎么对属性进行设置
        glVertexAttribPointer(
                              coord_modelspaceID,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0
                              );


        glBindTexture(GL_TEXTURE_2D,texture.name);
        glUniform1i(textureId,texture.name);

        //绘制顶点数组，绘制三个顶点
        glDrawArrays(GL_QUADS,0,4);
        //关闭顶点属性变量
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        //关闭顶点属性变量
        glDisableVertexAttribArray(coord_modelspaceID);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
