#pragma once

class TextureData {

public:

    int type;
    int width;
    int height;
    unsigned char* data;

    TextureData(int type, int width, int height, unsigned char * data) :
            type(type),
            width(width),
            height(height),
            data(data)
    {}

    ~TextureData() = default;

};
