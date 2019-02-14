#pragma once

#include "ApplicationBase.h"
#include <glm/glm.hpp>

class ApplicationCoreProfile : public ApplicationBase
{
public:
    ApplicationCoreProfile(int argc,char **argv);
    virtual void versionSelect()override;
    void computeMatrixesFromInput(double elapse);
protected:
    glm::mat4x4 mMatView;
    glm::mat4x4 mMatProjection;
    glm::vec3 mEyePos;
    float mEyeHorizontalAngle;
    float mEyeVerticalAngle;
    float mInitialFoV;
    float mSpeed;
    float mMouseSpeed;
};
