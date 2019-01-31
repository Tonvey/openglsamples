#include "ApplicationCoreProfile.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include "FileUtil.h"
using namespace std;
#define VERTEX_FILE_NAME "shader.vert"
#define FRAG_FILE_NAME "shader.frag"

const GLfloat vertex_buffer_data[]={
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};
//只要跟上面坐标对上就行
const GLfloat uvBufferData[]={
    1.0f,1.0f,
    1.0f,0.0f,
    0.0f,0.0f,
    0.0f,1.0f,
};
const GLuint vertex_indices_data[]={
    // 起始于0!
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

class Application: public ApplicationCoreProfile
{
public:
    struct MyTexture
    {
        GLuint name;
        GLuint width;
        GLuint height;
    };
private:
    GLuint myProgramId;
    GLuint vertexPosition;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint uvbo;
    GLuint uvId;
    GLuint textureId;
    MyTexture texture;
public:

    Application(int argc , char **argv)
        :ApplicationCoreProfile(argc,argv)
    {
    }
    MyTexture loadBMPTexture(string fileName)
    {
        MyTexture t;
        FILE *fp = fopen(fileName.c_str(),"rb");
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
        char* data = new char[bytes];
        unique_ptr<char[]> dataGuard(data);
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
        glGenerateMipmap(t.name);
        return t;
    }
    ~Application()
    {
        if(glIsBuffer(ebo)==GL_TRUE)
        {
            cout<<"Delete ebo buffer"<<endl;
            glDeleteBuffers(1,&ebo);
        }
        if(glIsBuffer(vbo)==GL_TRUE)
        {
            cout<<"Delete vbo buffer"<<endl;
            glDeleteBuffers(1,&vbo);
        }
        if(glIsBuffer(uvbo)==GL_TRUE)
        {
            cout<<"Delete uvbo buffer"<<endl;
            glDeleteBuffers(1,&uvbo);
        }
        if(glIsTexture(this->texture.name))
        {
            cout<<"Delete texture sample"<<endl;
            glDeleteTextures(1,&this->texture.name);
        }
        if(glIsVertexArray(vao)==GL_TRUE)
        {
            cout<<"Delete vao buffer"<<endl;
            glDeleteVertexArrays(1,&vao);
        }
        if(glIsProgram(myProgramId)==GL_TRUE)
        {
            cout<<"Delete program"<<endl;
            glDeleteProgram(myProgramId);
        }
    }

    void init()override
    {
        ApplicationCoreProfile::init();
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS); 
        //加载shader
        myProgramId = loadShader(
            FileUtil::getFileDirName(__FILE__)+FileUtil::pathChar+VERTEX_FILE_NAME,
            FileUtil::getFileDirName(__FILE__)+FileUtil::pathChar+FRAG_FILE_NAME
            );

        //加载纹理图片
        glEnable(GL_TEXTURE_2D);
        texture = loadBMPTexture(
                                 FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + "panda.bmp");

        textureId = 
            glGetUniformLocation(myProgramId,"myTextureSampler");

        vertexPosition= 
            glGetAttribLocation(myProgramId,"vertexPosition");
        uvId= 
            glGetAttribLocation(myProgramId,"uv");

        //在显卡中申请内存，内存句柄是vertexbuffer
        //VAO创建
        glGenVertexArrays(1,&vao);

        //VBO创建
        glGenBuffers(1, &vbo);
        //此时的绑定只是为了传入数据，没有其他太多的作用
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertex_buffer_data),
            vertex_buffer_data,
            GL_STATIC_DRAW);
        //解绑
        glBindBuffer(GL_ARRAY_BUFFER,0);

        //EBO创建
        glGenBuffers(1, &ebo);
        //此时的绑定只是为了传入数据，没有其他太多的作用
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //解绑
        glBufferData(
                     GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(vertex_indices_data),
                     vertex_indices_data,
                     GL_STATIC_DRAW);

        //UVBO创建
        glGenBuffers(1,&uvbo);
        glBindBuffer(GL_ARRAY_BUFFER,uvbo);
        glBufferData(
                     GL_ARRAY_BUFFER,
                     sizeof(uvBufferData),
                     uvBufferData,
                     GL_STATIC_DRAW
                     );
        glBindBuffer(GL_ARRAY_BUFFER,0);


        //习惯性的解绑
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    }

    void render(double elapse) override
    {
        glClearColor(0,0,0.4,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(this->myProgramId);
        glEnableVertexAttribArray(vertexPosition);
        glEnableVertexAttribArray(uvId);


        //在draw之前一定要绑定好vao以及GL_ARRAY_BUFFER和GL_ELEMENT_ARRAY_BUFFER
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,this->vbo);
        glVertexAttribPointer(
                               vertexPosition,
                               3,
                               GL_FLOAT,
                               GL_FALSE,
                               0,
                               (void*)0
                               );

        glBindBuffer(GL_ARRAY_BUFFER,this->uvbo);
        glVertexAttribPointer(
                              uvId,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0
                              );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ebo);
        //最后通过glDrawElements的方式来绘制
        glDrawElements(
                       GL_TRIANGLES,
                       sizeof(vertex_indices_data)/sizeof(vertex_indices_data[0]),
                       GL_UNSIGNED_INT,
                       (void*)0);
        glDisableVertexAttribArray(vertexPosition);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
