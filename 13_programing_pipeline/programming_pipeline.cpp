#include "ApplicationBase.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
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
    GLuint vertexbuffer;
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

        const GLfloat g_vertex_buffer_data[]={
            -1.0f,-1.0f,0.0f,
            1.0f,-1.0f,0.0f,
            0.0f,1.0f,0.0f
        };
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
        return 0;
    }
    GLuint loadShader(string vertShaderFile,string fragShaderFile)
    {
        //创建顶点shader
        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

        //创建片段shader
        GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        string vertexShaderCode;
        ifstream vertexShaderStream(vertShaderFile,std::ios::in);
        if(vertexShaderStream.is_open())
        {
            char buf[1024];
            memset(buf,0,sizeof(buf));
            while(!vertexShaderStream.eof())
            {
                vertexShaderStream.read(buf,sizeof(buf)-1);
                vertexShaderCode += buf;
            }
            vertexShaderStream.close();
        }
        else
        {
            cerr<<"Can not open shader file "<<endl;
            return 0;
        }

        //编译vertex shader
        const char *vertexShaderPointer = vertexShaderCode.c_str();
        glShaderSource(vertexShaderId, 1, &vertexShaderPointer, NULL);
        glCompileShader(vertexShaderId);

        //检查编译结果
        GLint result = GL_FALSE;
        glGetShaderiv(vertexShaderId,GL_COMPILE_STATUS,&result);
        if(result!=GL_TRUE)//编译出错
        {
            int infoLogLength;
            glGetShaderiv(vertexShaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
            if(infoLogLength>0)
            {
                char *infoLogBuf = new char[infoLogLength+1];
                unique_ptr<char[]> u(infoLogBuf);
                infoLogBuf[infoLogLength] = '\0';
                glGetShaderInfoLog(vertexShaderId,infoLogLength,NULL,infoLogBuf);
                cerr<<infoLogBuf<<endl;
            }
        }

        string fragShaderCode;
        ifstream fragShaderStream(fragShaderFile,std::ios::in);
        if(fragShaderStream.is_open())
        {
            char buf[1024];
            memset(buf,0,sizeof(buf));
            while(!fragShaderStream.eof())
            {
                fragShaderStream.read(buf,sizeof(buf)-1);
                fragShaderCode += buf;
            }
            fragShaderStream.close();
        }
        else
        {
            cerr<<"Can not open shader file "<<endl;
            return 0;
        }


        //编译frag shader
        const char *fragShaderPointer = fragShaderCode.c_str();
        glShaderSource(fragShaderId, 1, &fragShaderPointer, NULL);
        glCompileShader(fragShaderId);

        //检查编译结果
        glGetShaderiv(fragShaderId,GL_COMPILE_STATUS,&result);
        if(result!=GL_TRUE)//编译出错
        {
            int infoLogLength;
            glGetShaderiv(fragShaderId,GL_INFO_LOG_LENGTH,&infoLogLength);
            if(infoLogLength>0)
            {
                char *infoLogBuf = new char[infoLogLength+1];
                unique_ptr<char[]> u(infoLogBuf);
                infoLogBuf[infoLogLength] = '\0';
                glGetShaderInfoLog(fragShaderId,infoLogLength,NULL,infoLogBuf);
                cerr<<infoLogBuf<<endl;
            }
        }

        //创建程序连接两个shader，得到程序id
        GLuint programId = glCreateProgram();
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragShaderId);
        glLinkProgram(programId);

        //检查结果
        glGetProgramiv(programId,GL_LINK_STATUS,&result);
        if(result!=GL_TRUE)//编译出错
        {
            int infoLogLength;
            glGetProgramiv(programId,GL_INFO_LOG_LENGTH,&infoLogLength);
            if(infoLogLength>0)
            {
                char *infoLogBuf = new char[infoLogLength+1];
                unique_ptr<char[]> u(infoLogBuf);
                infoLogBuf[infoLogLength] = '\0';
                glGetProgramInfoLog(programId,infoLogLength,NULL,infoLogBuf);
                cerr<<infoLogBuf<<endl;
            }
        }

        //删除两个shader
        glDetachShader(programId,vertexShaderId);
        glDetachShader(programId,fragShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragShaderId);
        return programId;
    }
    void render(double elapse) override
    {
        glClearColor(0,0,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        //使用shader程序
        glUseProgram(myProgramId);
        //启用顶点属性
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        //指定渲染时候，怎么对属性进行设置
        glVertexAttribPointer(
            vertexPosition_modelspaceID,
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

        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
