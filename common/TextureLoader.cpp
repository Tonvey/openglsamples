#include "MyStudyHeaders.h"
#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
using namespace std;

TextureLoader::TextureLoader(string fileName)
{
    unsigned char *data = stbi_load(fileName.c_str(),&mWidth,&mHeight,&mChannelsCount,0);
    if(!data)
    {
        throw runtime_error(stbi_failure_reason());
    }
    //transform image data to normal
    mData = new unsigned char[mWidth*mHeight*mChannelsCount];
    for(int row = 0 ; row < mHeight ; ++ row)
    {
        for(int col = 0 ; col < mWidth ; ++col)
        {
            for(int n = 0 ; n < mChannelsCount;++n)
            {
                mData[(row*mWidth + col)*mChannelsCount + n] = data[((mHeight-row)*mWidth + col)*mChannelsCount + n];
            }
        }
    }
    stbi_image_free(data);
}
int TextureLoader::mode()const
{
    //TODO : channel count equal 1 or 2 has not implemented
    switch(mChannelsCount)
    {
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        return GL_RGB;
    }
}

TextureLoader::~TextureLoader()
{
    if(mData)
    {
        delete [] mData;
    }
}
