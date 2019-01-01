#pragma once

#include "ApplicationBase.h"

class ApplicationCoreProfile : public ApplicationBase
{
public:
    ApplicationCoreProfile(int argc,char **argv);
    virtual void versionSelect()override;
};
