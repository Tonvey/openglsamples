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
private:
    GLuint myProgramId;
    GLuint vertexPosition_modelspaceID;
    GLuint vertexColor_modelspaceID;
    GLuint vertexbuffer;
    GLuint colorBuffer;
public:

    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
    }
    int init()override
    {
        ApplicationBase::init();
        //加载shader
        myProgramId = loadShader(
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + VERTEX_FILE_NAME,
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + FRAG_FILE_NAME
            );

        vertexPosition_modelspaceID = 
            glGetAttribLocation(myProgramId,"vertexPosition_modelspace");
        vertexColor_modelspaceID = 
            glGetAttribLocation(myProgramId,"vertexColor_modelspace");

        const GLfloat g_vertex_buffer_data[]={
            -1.0f,-1.0f,0.0f,
            1.0f,-1.0f,0.0f,
            0.0f,1.0f,0.0f
        };

        const GLfloat g_vertex_color_data[]={
                                             1.0f,0.0f,0.0f,
                                             0.0f,1.0f,0.0f,
                                             0.0f,0.0f,1.0f
        };

        //------------------------------------------------------------------
        //在显卡中申请内存，内存句柄是vertexbuffer
        glGenBuffers(1,&vertexbuffer);
        //对vertexbuffer进行操作
        glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
        //把顶点坐标g_vertex_buffer_data传递到显卡，保存到vertexbuffer中
        glBufferData(
                     GL_ARRAY_BUFFER,
                     sizeof(g_vertex_buffer_data),
                     g_vertex_buffer_data,
                     GL_STATIC_DRAW
                     );


        //------------------------------------------------------------------
        //在显卡中申请内存，内存句柄是colorBuffer
        glGenBuffers(1,&colorBuffer);
        //对vertexbuffer进行操作
        glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
        //把顶点坐标g_vertex_buffer_data传递到显卡，保存到vertexbuffer中
        glBufferData(
                     GL_ARRAY_BUFFER,
                     sizeof(g_vertex_color_data),
                     g_vertex_color_data,
                     GL_STATIC_DRAW
                     );
        return 0;
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
        //启用顶点颜色属性
        glEnableVertexAttribArray(vertexColor_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
        //指定渲染时候，怎么对属性进行设置
        glVertexAttribPointer(
                              vertexColor_modelspaceID,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0
                              );

        //绘制顶点数组，绘制三个顶点
        glDrawArrays(GL_TRIANGLES,0,3);
        //关闭顶点属性变量
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        //关闭顶点属性变量
        glDisableVertexAttribArray(vertexColor_modelspaceID);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
