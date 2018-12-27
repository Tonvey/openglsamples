#include "redtriangle.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>

static const float sg_vertexes[] = {
    -1.0f,-1.0f,0.0f,
    1.0f,-1.0f,0.0f,
    0.0f,1.0f,0.0f
};
RedTriangle::RedTriangle(QWidget *parent) : GLBaseWidget(parent)
{
}

void RedTriangle::initializeGL()
{
    //加载shader
    QOpenGLShader vs(QOpenGLShader::Vertex ,this);
    if(vs.compileSourceFile(":/red_triangle/shader.vert"))
    {
        qCritical()<<"Vertex shader compile error : "<<vs.log();
        this->close();
        return ;
    }

    QOpenGLShader fs(QOpenGLShader::Vertex ,this);
    if(fs.compileSourceFile(":/red_triangle/shader.vert"))
    {
        qCritical()<<"Fragment shader compile error : "<<fs.log();
        this->close();
        return ;
    }

    QOpenGLShaderProgram *p = new QOpenGLShaderProgram(this);
    p->addShader(&vs);
    p->addShader(&fs);
    if(p->link())
    {
        qCritical()<<"Program link error : "<<p->log();
        this->close();
        return ;
    }

    QOpenGLBuffer vbo;
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(sg_vertexes, sizeof(sg_vertexes));

    GLuint vertexPosition_modelspaceID = p->attributeLocation("vertexPosition_modelspace");

//    p->
//
//    //在显卡中申请内存，内存句柄是vertexbuffer
//    glGenBuffers(1,&vertexbuffer);
//    //对vertexbuffer进行操作
//    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
//    //把顶点坐标g_vertex_buffer_data传递到显卡，保存到vertexbuffer中
//    glBufferData(
//                GL_ARRAY_BUFFER,
//                sizeof(g_vertex_buffer_data),
//                g_vertex_buffer_data,
//                GL_STATIC_DRAW
//                );
}
