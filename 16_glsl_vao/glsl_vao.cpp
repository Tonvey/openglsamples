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
    GLuint myProgramId;
    GLuint vertexPosition;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
public:

    Application(int argc , char **argv)
        :ApplicationCoreProfile(argc,argv)
    {
    }
    ~Application()
    {
        if(glIsBuffer(vbo))
        {
            cout<<"Delete vbo buffer"<<endl;
            glDeleteBuffers(1,&vbo);
        }
        if(glIsBuffer(ebo))
        {
            cout<<"Delete ebo buffer"<<endl;
            glDeleteBuffers(1,&ebo);
        }
        if(glIsVertexArray(vao))
        {
            cout<<"Delete vao buffer"<<endl;
            glDeleteVertexArrays(1,&vao);
        }
        if(glIsProgram(myProgramId))
        {
            cout<<"Delete program"<<endl;
            glDeleteProgram(myProgramId);
        }
    }
    void init()override
    {
        ApplicationCoreProfile::init();
        //加载shader
        myProgramId = loadShader(
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + VERTEX_FILE_NAME,
            FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + FRAG_FILE_NAME
            );

        vertexPosition= 
            glGetAttribLocation(myProgramId,"vertexPosition");
        cout<<vertexPosition<<endl;

        const GLfloat g_vertex_buffer_data[]={
            0.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f
        };
        GLuint indices[] = {
            0, 1, 2
        };
        //在显卡中申请内存，内存句柄是vertexbuffer
        //VAO创建
        glGenVertexArrays(1,&vao);
        if(glIsVertexArray(vao)!=GL_TRUE)
        {
            cerr<<"genVertexArrays fail"<<endl;
        }
        glBindVertexArray(vao);

        //VBO创建
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        //EBO创建
        glGenBuffers(1, &ebo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(vertexPosition);

        //注意：这里是可以的，因为glVertexAttribPointer将注册eboID作为它的VBO，因此这里可以安全的解绑
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArrayAPPLE(0);
    }

    void render(double elapse) override
    {
        glClearColor(0,0,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(this->myProgramId);
        glEnableVertexAttribArray(vertexPosition);
        glBindBuffer(GL_ARRAY_BUFFER, vertexPosition);
        glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(vertexPosition);

        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
