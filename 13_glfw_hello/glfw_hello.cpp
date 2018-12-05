#include "MyStudyHeaders.h"
#include <cmath>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
namespace tonvey {
    void display(GLFWwindow *window)
    {
        glClearColor(0,0,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    void (*init_func)(int argc , char **argv)=nullptr;
    void (*display_func)(GLFWwindow *)=display;
    void (*key_func)(GLFWwindow *,int,int,int,int)=nullptr;
    void (*error_func)(int error , const char *description)=nullptr;
}
