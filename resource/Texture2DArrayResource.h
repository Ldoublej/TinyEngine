//
// Created by ldoublej on 18-11-10.
//

#ifndef TINYENGINE_TEXTURE2DARRAYRESOURCE_H
#define TINYENGINE_TEXTURE2DARRAYRESOURCE_H

#include "Texture2DResource.h"
#include <vector>

namespace resource
{

    class Texture2DArrayResource:public Resource
    {
    private:
        std::vector<Texture2DResource *> _texture2d_list;
    public:
        Texture2DArrayResource(const char ** filenames,int count);
        bool Load() override;
        void Release() override;
        unsigned char * GetData(int index);
        int GetWidth(int index);
        int GetHeight(int index);
        int GetChannelCount(int index);
        int GetTexture2DCount(){return _texture2d_list.size();}
        std::string GetFileName(int index);
        bool IsLoad(){return _loaded;}

        ~Texture2DArrayResource();
    };

}

#endif //TINYENGINE_TEXTURE2DARRAYRESOURCE_H
