#include "ApplicationCoreProfile.h"

ApplicationCoreProfile::ApplicationCoreProfile(int argc, char **argv)
    :ApplicationBase(argc,argv)
{
    this->mGLMajorVersion=3;
    this->mGLMinorVersion=2;
}

void ApplicationCoreProfile::versionSelect()
{
    ApplicationBase::versionSelect();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
}
