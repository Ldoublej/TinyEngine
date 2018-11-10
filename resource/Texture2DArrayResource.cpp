//
// Created by ldoublej on 18-11-10.
//

#include "Texture2DArrayResource.h"

namespace resource
{
    Texture2DArrayResource::Texture2DArrayResource( const char **  filenames, int count) {
        for(int i = 0;i < count; ++i)
        {
            const char * filename = filenames[i];
            Texture2DResource * texture2d = new Texture2DResource(filename);
            _texture2d_list.push_back(texture2d);
        }
    }

    bool Texture2DArrayResource::Load()
    {
        bool is_laod_success = true;
        for(int i =0;i < _texture2d_list.size();++i)
        {
            Texture2DResource * texture2d = _texture2d_list.at(i);
            is_laod_success = is_laod_success && texture2d->Load();
            if(!is_laod_success)
                return false;
        }
        _loaded = true;
        return true;
    }

    void Texture2DArrayResource::Release() {
        if(!_loaded)
            return;
        for(int i = 0;i < _texture2d_list.size();++i)
        {
            Texture2DResource * texture2d = _texture2d_list.at(i);
            texture2d->Release();
        }
    }

    unsigned char *Texture2DArrayResource::GetData(int index) {
        if(index >= _texture2d_list.size() || !_loaded)
            return nullptr;
        Texture2DResource * texture2d = _texture2d_list.at(index);
        return texture2d->GetData();
    }

    int Texture2DArrayResource::GetWidth(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return 0;
        Texture2DResource * texture2d = _texture2d_list.at(index);
        return texture2d->GetWidth();
    }

    int Texture2DArrayResource::GetHeight(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return 0;
        Texture2DResource * texture2d = _texture2d_list.at(index);
        return texture2d->GetHeight();
    }

    int Texture2DArrayResource::GetChannelCount(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return 0;
        Texture2DResource * texture2d = _texture2d_list.at(index);
        return texture2d->GetChannelCount();
    }

    std::string Texture2DArrayResource::GetFileName(int index) {
        if(index >= _texture2d_list.size()|| !_loaded)
            return "";
        Texture2DResource * texture2d = _texture2d_list.at(index);
        return texture2d->GetFileName();
    }

    Texture2DArrayResource::~Texture2DArrayResource() {
        if(!_loaded)
            return;
        for(int i = 0;i < _texture2d_list.size();++i)
        {
            Texture2DResource * texture2d = _texture2d_list.at(i);
            texture2d->Release();
        }
    }
}


