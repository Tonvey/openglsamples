#include "ShaderPrograme.h"
#include "VertexShader.h"
#include "FragmentShader.h"
using namespace std;


ShaderProgram::ShaderProgram()
{
}
ShaderProgram::~ShaderProgram()
{
    clear();
}
void ShaderProgram::clear()
{
    if(mProgrameId!=0)
    {
        glDeleteProgram(mProgrameId);
        mProgrameId = 0;
    }
}
bool ShaderProgram::IsValid()const
{
    if(mProgrameId!=0)
    {
        return glIsProgram(mProgrameId) == GL_TRUE;
    }
    return false;
}
bool ShaderProgram::reset(std::string vertFile, std::string fragFile)
{
    clear();
    VertexShader vert;
    FragmentShader frag;
    if(!vert.resetByFileName(vertFile))
    {
        exit(-1);
    }
    if(!frag.resetByFileName(fragFile))
    {
        exit(-1);
    }
    //创建程序连接两个shader，得到程序id
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vert.getShaderID());
    glAttachShader(programId, frag.getShaderID());
    glLinkProgram(programId);

    //检查结果
    GLint result = GL_FALSE;
    glGetProgramiv(programId,GL_LINK_STATUS,&result);
    if(result!=GL_TRUE)//编译出错
    {
        int infoLogLength;
        glGetProgramiv(programId,GL_INFO_LOG_LENGTH,&infoLogLength);
        if(infoLogLength>0)
        {
            char *infoLogBuf = new char[infoLogLength+1];
            unique_ptr<char[]> u(infoLogBuf);
            infoLogBuf[infoLogLength] = '\0';
            glGetProgramInfoLog(programId,infoLogLength,NULL,infoLogBuf);
            MY_LOG_ERROR("Program info : %s",infoLogBuf);
            return false;
        }
    }

    //删除两个shader
    glDetachShader(programId,vert.getShaderID());
    glDetachShader(programId,frag.getShaderID());
    vert.clear();
    frag.clear();
    return true;
}
