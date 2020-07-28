#include "ApplicationBase.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include "FileUtil.h"
#include "Texture.h"
using namespace std;

#define VERTEX_FILE_NAME "shader.vert"
#define FRAG_FILE_NAME "shader.frag"

class Application: public ApplicationBase
{
private:
    ShaderProgram program;
    GLuint vertexPosition_modelspaceID;
    GLuint coord_modelspaceID;
    GLuint vertexbuffer;
    GLuint uvBuffer;
    GLuint textureId;
    Texture texture;
public:

    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
        this->mGLMajorVersion=4;
        this->mGLMajorVersion=1;
    }
    void init()override
    {
        ApplicationBase::init();

        //加载shader
        program = loadShader(
                             FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + VERTEX_FILE_NAME,
                             FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + FRAG_FILE_NAME);

        //加载纹理图片
        glEnable(GL_TEXTURE_2D);
        texture = move(Texture(
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + "panda.bmp"));
        glEnable(texture.id());


        vertexPosition_modelspaceID =
            program.getAttr("vertexPosition");
        coord_modelspaceID =
            program.getAttr("coord");
        textureId =
            program.getAttr("myTextureSampler");

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
    }
    void render(double elapse) override
    {
        glClearColor(0,0,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        //使用shader程序
        program.use();

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


        glBindTexture(GL_TEXTURE_2D,texture.id());
        glUniform1i(textureId,texture.id());

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
