#pragma once

#include "MyStudyHeaders.h"

class ApplicationBase
{
public:
    ApplicationBase(int argc,char **argv);
    virtual int init(int argc,char **argv);
    virtual int run();
    virtual void render(double elapse);
    virtual void openGLErrorCallBack(int err,const char *description);
    static void printOpenGLInfo();
protected:
    GLFWwindow *mWindow;
};
