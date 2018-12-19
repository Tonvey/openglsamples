#include "FileUtil.h"
using namespace std;

#ifdef _WIN32
#define PATH_CHAR '\\'
#else
#define PATH_CHAR '/'
#endif

const char FileUtil::pathChar = PATH_CHAR;

string FileUtil::getFileDirName(string file)
{
    auto pos = file.rfind(PATH_CHAR);
    string curPath = file.substr(0,pos);
    return curPath;
}
