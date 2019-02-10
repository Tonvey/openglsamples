#pragma once
#include <string>
using namespace std;

class TextureLoader
{
public:
    TextureLoader(string fileName);
    ~TextureLoader();
    void load();
    int width()const{return mWidth;}
    int height()const{return mHeight;}
    int channelCount()const{return mChannelsCount;}
    int mode()const;
    unsigned char *data()const{return mData;}
private:
    int mWidth;
    int mHeight;
    int mChannelsCount;
    unsigned char *mData;
};
