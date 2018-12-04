#include "MyStudyHeaders.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
typedef float mytime_t;

using namespace std;
namespace tonvey
{
    extern bool quit;
    extern void (*init_func)(int,char**);
    extern void (*display_func)(GLFWwindow *);
    extern void (*key_func)(GLFWwindow *,int,int,int,int);
    extern void (*error_func)(int error , const char *description);
    //打印opengl的版本信息
    void printOpenGLInfo()
    {
        MY_LOG_DEBUG("OpenGL version: %s\n", glGetString(GL_VERSION));
        MY_LOG_DEBUG("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        MY_LOG_DEBUG("Vendor: %s\n", glGetString(GL_VENDOR));
        MY_LOG_DEBUG("Renderer: %s\n", glGetString(GL_RENDERER));
    }

}

static void errorCallback(int error ,const char *description)
{
    cerr<<"Error : "<< error << " " << description << endl;
}

static void keyCallback(GLFWwindow *window,int key ,int scancode , int action , int mods)
{
    if (key == GLFW_KEY_ESCAPE)
        //if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc,char **argv)
{
    GLFWwindow *window = nullptr;
    if(true)
    {
        //初始化glfw
        if (!glfwInit())
            exit(EXIT_FAILURE);
        //设置OpenGL的版本
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
        //创建窗口
        window = glfwCreateWindow(
            640,
            480,
            argv[0],
            NULL,
            NULL
            );

        if(!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        //绘制对象
        glfwMakeContextCurrent(window);
        if(tonvey::error_func)
        {
            glfwSetErrorCallback(tonvey::error_func);
        }
        if(tonvey::key_func)
        {
            glfwSetKeyCallback(window,tonvey::key_func);
        }
        glfwSwapInterval(1);
    }
    tonvey::printOpenGLInfo();
    clock_t last_time = clock();
    mytime_t elapse;
    while (!glfwWindowShouldClose(window))
    {
        clock_t this_time = clock();
        elapse = (mytime_t)(this_time-last_time)/CLOCKS_PER_SEC;
        //垂直同步
        if(elapse >= 1.0/60)
        {
            last_time=this_time;
            //绘制窗口
            if(tonvey::display_func)
                tonvey::display_func(window);
            glfwPollEvents();
        }
    }
    return 0;
}
