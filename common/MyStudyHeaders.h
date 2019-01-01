#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#   include <GLUT/glut.h>
#else
#define GL_GLEXT_PROTOTYPES
#   include <GL/gl.h>
#   include <GL/glut.h>
#   include <GL/glu.h>
#   include <GL/glext.h>
#endif

#define MY_LOG_DEBUG(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
