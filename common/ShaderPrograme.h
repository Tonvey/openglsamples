#pragma once

#include "MyStudyHeaders.h"
#include <memory>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    bool reset(std::string vertFile, std::string fragFile);
    void clear();
    bool IsValid()const;
private:
    GLuint mProgrameId = 0;
};
