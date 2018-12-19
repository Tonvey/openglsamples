#include "ApplicationBase.h"
#include <iostream>
#include <ctime>
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
{
    this->init(argc,argv);
}

int ApplicationBase::init(int argc ,char **argv)
{
    glfwSetErrorCallback([](int error , const char *description){
                             //this->openGLErrorCallBack(error,description);
        cerr<<"Error : "<< error << " " << description << endl;
    });

    //初始化glfw
    if (!glfwInit())
        exit(EXIT_FAILURE);
    //设置OpenGL的版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);

    //创建窗口
    this->mWindow = glfwCreateWindow(
        640,
        480,
        argv[0],
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
    return 0;
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
