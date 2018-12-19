//
// Created by ldoublej on 18-11-10.
//

#ifndef SIMPLEOGL_IMAGE2DARRAY_H
#define SIMPLEOGL_IMAGE2DARRAY_H

#include "Image2D.h"
#include <vector>

namespace resource
{

    class Image2DArray:public Resource
    {
    private:
        std::vector<Image2D *> _texture2d_list;
    public:
        Image2DArray(const char ** filenames,int count);
        bool Load() override;
        void Release() override;
        unsigned char * GetData(int index);
        int GetWidth(int index);
        int GetHeight(int index);
        int GetChannelCount(int index);
        int GetTexture2DCount(){return _texture2d_list.size();}
        std::string GetFileName(int index);
        bool IsLoad(){return _loaded;}

        ~Image2DArray();
    };

}

#endif //SIMPLEOGL_IMAGE2DARRAY_H
