#include "MyStudyHeaders.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define BMP_HEADER_LENGTH 54
typedef float mytime_t;
static mytime_t last_time;
static mytime_t elapse;
void render();
void reshape(int width,int height);
void display();
void idle();
void init(int argc,char **argv);
void timeFunc(int value);

void (*init_func)(int argc , char **argv)=init;
void (*display_func)()=display;
void (*reshape_func)(int,int)=reshape;
void (*idle_func)()=idle;

typedef struct _MyTexture
{
    GLuint name;
    GLuint width;
    GLuint height;
}MyTexture;

static MyTexture texture;

MyTexture loadBMPTexture(const char *fileName);

mytime_t updateElapse()
{
    clock_t this_time;
    this_time=clock();
    elapse = (mytime_t)(this_time-last_time)/CLOCKS_PER_SEC;
    last_time=this_time;
    return elapse;
}

void init(int argc , char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(512,512);
    glutCreateWindow(argv[0]);
    glEnable(GL_TEXTURE_2D);
    glutTimerFunc(1000/60,timeFunc,10);

    texture = loadBMPTexture("./11_texture/panda.bmp");

}

void timeFunc(int value)
{
    //垂直同步
    glutTimerFunc(1000/60,timeFunc,10);
    updateElapse();
    render();
}

MyTexture loadBMPTexture(const char *fileName)
{
    MyTexture t;
    FILE *fp = fopen(fileName ,"rb");
    if(!fp)
    {
        perror("fopen");
        exit(1);
    }

    //跳过前面bmp文件头部
    char header[54];
    fread(header,54,1,fp);
    // 数据格式
    // 宽度和高度
    t.width = *(int*)(header + 0x12);
    t.height = *(int*)(header + 0x16);
    int bytes = (t.width) * (t.height) * 3;
    char* data = (char*)malloc(bytes);
    fread(data, bytes, 1, fp);
    fclose(fp);

    glGenTextures(1,&t.name);
    glBindTexture(GL_TEXTURE_2D,t.name);

    // 纹理设置
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // 把内存中的图像信息，发送给显卡
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        t.width,
        t.height,
        0,
        GL_BGR,
        GL_UNSIGNED_BYTE,
        data);

    free(data);
    return t;
}

void render()
{
    //背景颜色灰色
    //glClearColor(0.5,0.5,0.5,1.0);
    glClearColor(0,0,0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D,texture.name);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0,0.0);
        glVertex2f(0,0);

        glTexCoord2f(1.0,0.0);
        glVertex2f(1,0);

        glTexCoord2f(1.0,1.0);
        glVertex2f(1,1);

        glTexCoord2f(0.0,1.0);
        glVertex2f(0,1);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width,int height)
{
}
void display()
{
}
void idle()
{
}
