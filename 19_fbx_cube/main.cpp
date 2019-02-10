#include "ApplicationCoreProfile.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include "FileUtil.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

#define VERTEX_FILE_NAME "shader.vert"
#define FRAG_FILE_NAME "shader.frag"

class Application: public ApplicationCoreProfile
{
public:
private:
    GLuint myProgramId;
    GLuint vertexPosition;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
	struct aiLogStream stream;
    const struct aiScene* scene = nullptr;
public:

    Application(int argc , char **argv)
        :ApplicationCoreProfile(argc,argv)
    {
        //log for assimp
        stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
        aiAttachLogStream(&stream);
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
        if(this->scene)
        {
            aiReleaseImport(scene);
        }

        aiDetachAllLogStreams();
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

        string fbxFile = FileUtil::getFileDirName(__FILE__)+FileUtil::pathChar + "cube.fbx";
        auto scene = aiImportFile(fbxFile.c_str(),aiProcessPreset_TargetRealtime_MaxQuality);

        vertexPosition= 
            glGetAttribLocation(myProgramId,"vertexPosition");

        //在显卡中申请内存，内存句柄是vertexbuffer
        //VAO创建
        glGenVertexArrays(1,&vao);

        //VBO创建
        glGenBuffers(1, &vbo);
        //此时的绑定只是为了传入数据，没有其他太多的作用
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //        glBufferData(
        //            GL_ARRAY_BUFFER,
        //            sizeof(vertex_buffer_data),
        //            vertex_buffer_data,
        //            GL_STATIC_DRAW);
        //        //解绑
        //        glBindBuffer(GL_ARRAY_BUFFER,0);
        //
        //        //EBO创建
        //        glGenBuffers(1, &ebo);
        //        //此时的绑定只是为了传入数据，没有其他太多的作用
        //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //        //解绑
        //        glBufferData(
        //                     GL_ELEMENT_ARRAY_BUFFER,
        //                     sizeof(vertex_indices_data),
        //                     vertex_indices_data,
        //                     GL_STATIC_DRAW);
        //

        //习惯性的解绑
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    }

    void render(double elapse) override
    {
        glClearColor(0,0,0.4,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(this->myProgramId);
        glEnableVertexAttribArray(vertexPosition);


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

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ebo);
        //最后通过glDrawElements的方式来绘制
        //        glDrawElements(
        //                       GL_TRIANGLES,
        //                       sizeof(vertex_indices_data)/sizeof(vertex_indices_data[0]),
        //                       GL_UNSIGNED_INT,
        //                       (void*)0);
        glDisableVertexAttribArray(vertexPosition);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
