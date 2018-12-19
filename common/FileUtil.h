#pragma once
#include <string>

class FileUtil
{
public:
    static const char pathChar;
    static std::string getFileDirName(std::string file);
};
