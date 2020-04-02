#pragma once

#include "MyStudyHeaders.h"
#include <string>
enum ShaderType
{
 Vertex,
 Tesselation,
 Geometry,
 Fragment
};
class ShaderBase
{
public:
    ShaderBase();
    ~ShaderBase();
    void clear();
    bool isValid()const;
    virtual ShaderType getShaderType()const = 0;
    bool resetByFileName(std::string fileName);
    GLuint getShaderID()const{return mShaderId;}
protected:
    virtual bool resetByContent(const std::string &content) = 0;
    GLuint mShaderId = 0;
};
