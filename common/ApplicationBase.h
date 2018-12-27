#pragma once

#include "MyStudyHeaders.h"
#include <vector>
#include <string>

class ApplicationBase
{
public:
    ApplicationBase(int argc,char **argv);
    virtual void init();
    virtual int run();
    virtual void render(double elapse);
    virtual void openGLErrorCallBack(int err,const char *description);
    virtual GLuint loadShader(std::string vertShaderFile,std::string fragShaderFile);
    static void printOpenGLInfo();
    virtual ~ApplicationBase()=default;
protected:
    std::vector<std::string> mArgvs;
    GLFWwindow *mWindow;
    int mGLMajorVersion;
    int mGLMinorVersion;
};
