#pragma once
#ifdef __APPLE__
#   include <GLUT/glut.h>
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   define glGenVertexArrays(...) glGenVertexArraysAPPLE(__VA_ARGS__)
#   define glDeleteVertexArrays(...) glDeleteFencesAPPLE(__VA_ARGS__)
#   define glBindVertexArray(...) glBindVertexArrayAPPLE(__VA_ARGS__)
#   define glIsVertexArray(...) glIsVertexArrayAPPLE(__VA_ARGS__)
#else
#define GL_GLEXT_PROTOTYPES
#   include <GL/gl.h>
#   include <GL/glut.h>
#   include <GL/glu.h>
#   include <GL/glext.h>
#endif
#include <stdio.h>
#include <GLFW/glfw3.h>

#define MY_LOG_DEBUG(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
