#pragma once
#ifdef __APPLE__
#   include <GLUT/glut.h>
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#else
#   include <GL/glut.h>
#endif
#include <stdio.h>



#define MY_LOG_DEBUG(...) do{printf(__VA_ARGS__);fflush(stdout);}while(0)
