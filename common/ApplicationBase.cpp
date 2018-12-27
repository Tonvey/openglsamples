#include "ApplicationBase.h"
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

void ApplicationBase::printOpenGLInfo()
{
    MY_LOG_DEBUG("OpenGL version: %s\n", glGetString(GL_VERSION));
    MY_LOG_DEBUG("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    MY_LOG_DEBUG("Vendor: %s\n", glGetString(GL_VENDOR));
    MY_LOG_DEBUG("Renderer: %s\n", glGetString(GL_RENDERER));
}

ApplicationBase::ApplicationBase(int argc,char **argv)
    :mWindow(nullptr)
    ,mGLMajorVersion(2)
    ,mGLMinorVersion(1)
{
    for(int i = 0 ; i< argc ; ++i)
    {
        this->mArgvs.push_back(argv[i]);
    }
}

void ApplicationBase::init()
{
    glfwSetErrorCallback([](int error , const char *description){
                             //this->openGLErrorCallBack(error,description);
        cerr<<"Error : "<< error << " " << description << endl;
    });

    //初始化glfw
    if (!glfwInit())
        exit(EXIT_FAILURE);
    //设置OpenGL的版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,this->mGLMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,this->mGLMinorVersion);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    //创建窗口
    this->mWindow = glfwCreateWindow(
        640,
        480,
        this->mArgvs[0].c_str(),
        NULL,
        NULL
        );
    if(!this->mWindow)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //绘制对象
    glfwMakeContextCurrent(this->mWindow);

    //垂直同步
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->mWindow,[](GLFWwindow *window,int key,int scancode ,int action ,int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    });
}
void ApplicationBase::render(double elapse)
{
}

void ApplicationBase::openGLErrorCallBack(int error, const char *description)
{
    cerr<<"Error : "<< error << " " << description << endl;
}

int ApplicationBase::run()
{
    this->init();
    printOpenGLInfo();
    clock_t last_time = clock();
    while (!glfwWindowShouldClose(this->mWindow))
    {
        //计算与上一帧时间差（秒）
        clock_t this_time=clock();
        double elapse = (double)(this_time-last_time)/CLOCKS_PER_SEC;
        last_time=this_time;
        //绘制窗口
        this->render(elapse);
        glfwPollEvents();
    }
    return 0;
}
GLuint ApplicationBase::loadShader(string vertShaderFile,string fragShaderFile)
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
        exit(-1);
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
            cerr<<"Vertex shader info : "<<infoLogBuf<<endl;
            exit(-1);
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
        exit(-1);
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
            cerr<<"Frag shader info : "<<infoLogBuf<<endl;
            exit(-1);
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
            cerr<<"Program info : "<<infoLogBuf<<endl;
            exit(-1);
        }
    }

    //删除两个shader
    glDetachShader(programId,vertexShaderId);
    glDetachShader(programId,fragShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragShaderId);
    return programId;
}
