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

class Application: public ApplicationCoreProfile
{
private:
    ShaderProgram program;
    GLuint vertexPosition;
    GLuint vbo;
    GLuint vao;
public:

    Application(int argc , char **argv)
        :ApplicationCoreProfile(argc,argv)
    {
    }
    ~Application()
    {
        if(glIsBuffer(vbo)==GL_TRUE)
        {
            cout<<"Delete vbo buffer"<<endl;
            glDeleteBuffers(1,&vbo);
        }
        if(glIsVertexArray(vao)==GL_TRUE)
        {
            cout<<"Delete vao buffer"<<endl;
            glDeleteVertexArrays(1,&vao);
        }
    }
    void init()override
    {
        ApplicationCoreProfile::init();
        //加载shader
        program = loadShader(
                                 FileUtil::getFileDirName(__FILE__)+FileUtil::pathChar+VERTEX_FILE_NAME,
                                 FileUtil::getFileDirName(__FILE__)+FileUtil::pathChar+FRAG_FILE_NAME
                                 );

        vertexPosition= 
            program.getAttr("vertexPosition");

        const GLfloat g_vertex_buffer_data[]={
                                              -1.0,-1.0,0,
                                              1.0,-1.0,0,
                                              0.0,1.0,0,
        };
        //在显卡中申请内存，内存句柄是vertexbuffer
        //VAO创建
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);

        //VBO创建
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
                     GL_ARRAY_BUFFER,
                     sizeof(g_vertex_buffer_data),
                     g_vertex_buffer_data,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(
                              vertexPosition,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (GLvoid*)0);
    }

    void render(double elapse) override
    {
        glClearColor(0,0,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        //can take out of this
        glEnableVertexAttribArray(vertexPosition);
        glBindVertexArray(vao);
        program.use();
        glBindBuffer(GL_ARRAY_BUFFER, vertexPosition);
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(vertexPosition);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
