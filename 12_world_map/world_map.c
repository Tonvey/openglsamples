#include "MyStudyHeaders.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
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

float earth_rot=0;

typedef struct _MyTexture
{
    GLuint name;
    GLuint width;
    GLuint height;
}MyTexture;
static MyTexture texture;

typedef struct _Point
{
    float x;
    float y;
    float z;
}Point;

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

    //开启剔除，如果不开剔除，将会导致图片错乱
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    texture = loadBMPTexture("./12_world_map/world_map.bmp");

}

void timeFunc(int value)
{
    //垂直同步
    glutTimerFunc(1000/60,timeFunc,10);
    updateElapse();
    render();
}


void coordUV(int i , int j,  int slice)
{
    glTexCoord2f(1.0*i/slice,1.0*j/slice);
}

void drawBall(float radius)
{
    const int slice = 50;
    const float PI = atan(1.)*4;
    Point vertexes[slice+1][slice+1];
    int i,j;
    for(j=0;j<=slice;++j)
    {
        float theta = PI / slice * j;
        float y =  -cos(theta)*radius;
        float radius2 = radius * sin(theta);

        //画圆
        for(i = 0 ; i<= slice ; ++i)
        {
            float theta2 = 2*PI/slice*i;
            float x = radius2 * cos(theta2);
            float z = radius2 * sin(theta2);
            vertexes[i][j].x=x;
            vertexes[i][j].y=y;
            vertexes[i][j].z=z;
        }
    }

    glBegin(GL_QUADS);
    {
        for(i=0;i<slice;++i)
        {
            for(j=0;j<slice;++j)
            {
                glBindTexture(GL_TEXTURE_2D,texture.name);
                coordUV(i,j,slice);
                glVertex3f(
                    vertexes[i][j].x,
                    vertexes[i][j].y,
                    vertexes[i][j].z
                    );
                coordUV(i+1,j,slice);
                glVertex3f(
                    vertexes[i+1][j].x,
                    vertexes[i+1][j].y,
                    vertexes[i+1][j].z
                    );
                coordUV(i+1,j+1,slice);
                glVertex3f(
                    vertexes[i+1][j+1].x,
                    vertexes[i+1][j+1].y,
                    vertexes[i+1][j+1].z
                    );
                coordUV(i,j+1,slice);
                glVertex3f(
                    vertexes[i][j+1].x,
                    vertexes[i][j+1].y,
                    vertexes[i][j+1].z
                    );
            }
        }
    }
    glEnd();
}

void render()
{
    glClearColor(0,0,0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    earth_rot += 10*elapse;
    glRotatef(earth_rot,0,1,0);

    glColor4f(1,1,1,1);

    drawBall(0.5);

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
