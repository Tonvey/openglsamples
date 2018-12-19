#pragma once

#include "MyStudyHeaders.h"
#include <vector>
#include <string>

class ApplicationBase
{
public:
    ApplicationBase(int argc,char **argv);
    virtual int init();
    virtual int run();
    virtual void render(double elapse);
    virtual void openGLErrorCallBack(int err,const char *description);
    static void printOpenGLInfo();
protected:
    std::vector<std::string> mArgvs;
    GLFWwindow *mWindow;
};
