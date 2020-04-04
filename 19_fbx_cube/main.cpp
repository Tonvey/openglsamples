#include "ApplicationCoreProfile.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include "FileUtil.h"
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <Mesh.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

#define VERTEX_FILE_NAME "shader.vert"
#define FRAG_FILE_NAME "shader.frag"

class Application: public ApplicationCoreProfile
{
public:
private:
    ShaderProgram program;
    GLuint vertexPosition;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint idMVP;
    vector<Mesh<ai_real>> mVecMeshes;
    struct aiLogStream stream;
    const struct aiScene* scene = nullptr;
    mat4x4 mvp;
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
        //加载shader
        program = loadShader(
                             FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + VERTEX_FILE_NAME,
                             FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + FRAG_FILE_NAME);

        //加载纹理图片
        glEnable(GL_TEXTURE_2D);

        //在显卡中申请内存，内存句柄是vertexbuffer
        //VAO创建
        glGenVertexArrays(1,&vao);


        string fbxFile = FileUtil::getFileDirName(__FILE__)+FileUtil::pathChar + "cube.fbx";
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(fbxFile,aiProcess_Triangulate|
                                                 aiProcess_JoinIdenticalVertices);
        if(!scene)
        {
            MY_LOG_DEBUG("Error in import scene\n");
        }
        else
        {
            MY_LOG_DEBUG("meshes num:\t%u\n",scene->mNumMeshes);
            MY_LOG_DEBUG("martiril num:\t%u\n",scene->mNumMaterials);
            MY_LOG_DEBUG("lights num:\t%u\n",scene->mNumLights);
            MY_LOG_DEBUG("cameras num:\t%u\n",scene->mNumCameras);
            MY_LOG_DEBUG("textures num:\t%u\n",scene->mNumTextures);
            MY_LOG_DEBUG("animations num:\t%u\n",scene->mNumAnimations);
            aiNode *node = scene->mRootNode;
            for (unsigned int i = 0; i < node->mNumMeshes; ++i)
            {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                mVecMeshes.push_back(this->processMesh(mesh, scene));
            }

            for (unsigned int i = 0; i < node->mNumChildren; ++i)
            {
                this->processNode(node->mChildren[i], scene);
            }
            for(auto m : this->mVecMeshes)
            {
                MY_LOG_DEBUG("vertex count : %lu\n",m.vertices.size());
                for(auto v : m.vertices)
                {
                    MY_LOG_DEBUG("vertex : %f %f %f\n",v.x,v.y,v.z);
                }

                MY_LOG_DEBUG("face count : %lu\n",m.faces.size()/3);
                for(auto f : m.faces)
                {
                    MY_LOG_DEBUG("face : %u\n",f);
                }

                MY_LOG_DEBUG("textureCoords count : %lu\n",m.textureCoords.size());
                for(auto t : m.textureCoords)
                {
                    MY_LOG_DEBUG("tex : %f %f\n",t.u,t.v);
                }
            }
        }

        vertexPosition=
            program.getUniform("vertexPosition");

        //VBO创建
        glGenBuffers(1, &vbo);
        //此时的绑定只是为了传入数据，没有其他太多的作用
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
                     GL_ARRAY_BUFFER,
                     this->mVecMeshes[0].vertices.size()*sizeof(this->mVecMeshes[0].vertices[0]),
                     this->mVecMeshes[0].vertices.data(),
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
                     this->mVecMeshes[0].faces.size()*sizeof(this->mVecMeshes[0].faces[0]),
                     this->mVecMeshes[0].faces.data(),
                     GL_STATIC_DRAW);
        //习惯性的解绑
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        this->idMVP = program.getUniform("mvp");
    }

    void render(double elapse) override
    {
        this->computeMatrixesFromInput(elapse);
        mat4 matModel(1.0);
        mat4 mvp = this->mMatProjection * this->mMatView * matModel;

        glUniformMatrix4fv(this->idMVP,1,GL_FALSE,&mvp[0][0]);

        glClearColor(0,0,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();
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
        glDrawElements(
                       GL_TRIANGLES,
                       this->mVecMeshes[0].faces.size(),
                       GL_UNSIGNED_INT,
                       (void*)0);
        glDisableVertexAttribArray(vertexPosition);
        glfwSwapBuffers(this->mWindow);
    }
    void processNode(aiNode * node, const aiScene * scene)
    {
        for (uint i = 0; i < node->mNumMeshes; i++)
        {
            MY_LOG_DEBUG("meshes 0 : %d \n",node->mMeshes[0]);
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            this->mVecMeshes.push_back(this->processMesh(mesh, scene));
        }

        for (uint i = 0; i < node->mNumChildren; i++)
        {
            this->processNode(node->mChildren[i], scene);
        }
    }

    Mesh<ai_real> processMesh(aiMesh * mesh, const aiScene * scene)
    {
        // Data to fill
        //        vector<Vertex> vertices;
        //        vector<uint> indices;

        // vector<Texture> textures;
        // if (mesh->mMaterialIndex >= 0)
        // {
        //     aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

        //     if (textype.empty()) textype = determineTextureType(scene, mat);
        // }

        // Walk through each of the mesh's vertices
        Mesh<ai_real> myMesh;
        myMesh.vertices.reserve(mesh->mNumVertices);
        for (uint i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex3D<ai_real> vertex;
            TextureUVCoord2D<ai_real> uv;

            vertex.x = mesh->mVertices[i].x;
            vertex.y = mesh->mVertices[i].y;
            vertex.z = mesh->mVertices[i].z;

            if (mesh->mTextureCoords[0])
            {
                uv.u = (float)mesh->mTextureCoords[0][i].x;
                uv.v = (float)mesh->mTextureCoords[0][i].y;
                myMesh.textureCoords.push_back(uv);
            }

            myMesh.vertices.push_back(vertex);
        }

        myMesh.faces.reserve(mesh->mNumFaces);
        for (uint i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for (uint j = 0; j < face.mNumIndices; j++)
                myMesh.faces.push_back(face.mIndices[j]);
        }

        //        if (mesh->mMaterialIndex >= 0)
        //        {
        //            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //
        //            vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
        //            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        //        }

        return myMesh;
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
