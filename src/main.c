#include "MyStudyHeaders.h"
extern void (*init_func)();
extern void (*display_func)();
extern void (*reshape_func)(int,int);
extern void (*idle_func)();

//打印opengl的版本信息
void printOpenGLInfo()
{
    MY_LOG_DEBUG("OpenGL version: %s\n", glGetString(GL_VERSION));
    MY_LOG_DEBUG("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    MY_LOG_DEBUG("Vendor: %s\n", glGetString(GL_VENDOR));
    MY_LOG_DEBUG("Renderer: %s\n", glGetString(GL_RENDERER));
}

int main(int argc,char **argv)
{
    if(init_func)
        init_func(argc,argv);
    else
    {
        glutInit(&argc,argv);
        //glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_3_2_CORE_PROFILE);
        glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
        glutInitWindowSize(512,512);
        glutCreateWindow(argv[0]);
    }
    if(display_func)
        glutDisplayFunc(display_func);
    if(idle_func)
        glutIdleFunc(idle_func);
    if(reshape_func)
        glutReshapeFunc(reshape_func);
    printOpenGLInfo();
    glutMainLoop();
    return 0;
}
