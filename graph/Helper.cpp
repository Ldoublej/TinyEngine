//
// Created by ldoublej on 18-11-10.
//

#include "Helper.h"

namespace graph
{
    namespace helper
    {
        void SetImageData(Image2D * res,Texture2D * texture2d)
        {
            if(!res->IsLoad())
                return;
            texture2d->TexImage(0,res->GetWidth(),res->GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,res->GetData());

        }
        void SetImageData(Image2DArray * res,Texture2DArray * texture2d_array)
        {
            if(!res->IsLoad())
                return;
            texture2d_array->TexImage(0,res->GetWidth(0),res->GetWidth(0),res->GetTexture2DCount(),GL_RGB,GL_UNSIGNED_BYTE, nullptr);

            for(int i = 0;i < res->GetTexture2DCount();++i)
            {
                texture2d_array->TexSubImage(0,0,0,i,res->GetWidth(0),res->GetHeight(0),1,GL_RGBA,GL_UNSIGNED_BYTE,res->GetData(i));
            }
        }
    }
}