//
// Created by ldoublej on 18-11-10.
//

#include "Image2DArray.h"

namespace resource
{
    Image2DArray::Image2DArray( const char **  filenames, int count) {
        for(int i = 0;i < count; ++i)
        {
            const char * filename = filenames[i];
            Image2D * texture2d = new Image2D(filename);
            _texture2d_list.push_back(texture2d);
        }
    }

    bool Image2DArray::Load()
    {
        bool is_laod_success = true;
        for(int i =0;i < _texture2d_list.size();++i)
        {
            Image2D * texture2d = _texture2d_list.at(i);
            is_laod_success = is_laod_success && texture2d->Load();
            if(!is_laod_success)
                return false;
        }
        _loaded = true;
        return true;
    }

    void Image2DArray::Release() {
        if(!_loaded)
            return;
        for(int i = 0;i < _texture2d_list.size();++i)
        {
            Image2D * texture2d = _texture2d_list.at(i);
            texture2d->Release();
        }
    }

    unsigned char *Image2DArray::GetData(int index) {
        if(index >= _texture2d_list.size() || !_loaded)
            return nullptr;
        Image2D * texture2d = _texture2d_list.at(index);
        return texture2d->GetData();
    }

    int Image2DArray::GetWidth(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return 0;
        Image2D * texture2d = _texture2d_list.at(index);
        return texture2d->GetWidth();
    }

    int Image2DArray::GetHeight(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return 0;
        Image2D * texture2d = _texture2d_list.at(index);
        return texture2d->GetHeight();
    }

    int Image2DArray::GetChannelCount(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return 0;
        Image2D * texture2d = _texture2d_list.at(index);
        return texture2d->GetChannelCount();
    }

    std::string Image2DArray::GetFileName(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return "";
        Image2D * texture2d = _texture2d_list.at(index);
        return texture2d->GetFileName();
    }

    Image2DArray::~Image2DArray() {
        if(!_loaded)
            return;
        for(int i = 0;i < _texture2d_list.size();++i)
        {
            Image2D * texture2d = _texture2d_list.at(i);
            texture2d->Release();
        }
    }
}


