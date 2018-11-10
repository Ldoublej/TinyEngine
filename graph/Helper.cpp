//
// Created by ldoublej on 18-11-10.
//

#include "Helper.h"

namespace graph
{
    namespace texhelper
    {
        Texture2D * CreatTex2DByRes(Texture2DResource * res,GLenum internal_format,GLenum filter = GL_LINEAR, GLenum wrap = GL_REPEAT)
        {
            if(!res->IsLoad())
                return nullptr;
            Texture2D * texture2d = Texture2D::Create(internal_format,filter,wrap);
            texture2d->TexImage(0,res->GetWidth(),res->GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,res->GetData());
            return texture2d;

        }
        Texture2DArray * CreatTex2DArrayByRes(Texture2DArrayResource * res,int width,int height,GLenum internal_format,GLenum filter, GLenum wrap )
        {
            if(!res->IsLoad())
                return nullptr;
            Texture2DArray * texture2d_array = Texture2DArray::Create(internal_format,filter,wrap);
            texture2d_array->TexImage(0,width,height,res->GetTexture2DCount(),GL_RGB,GL_UNSIGNED_BYTE, nullptr);

            for(int i = 0;i < res->GetTexture2DCount();++i)
            {
                texture2d_array->TexSubImage(0,0,0,i,res->GetWidth(0),res->GetHeight(0),1,GL_RGB,GL_UNSIGNED_BYTE,res->GetData(i));
            }
            return texture2d_array;
        }
    }
}