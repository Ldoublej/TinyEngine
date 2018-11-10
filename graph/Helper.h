//
// Created by ldoublej on 18-11-10.
//

#ifndef SIMPLEOGL_HELPER_H
#define SIMPLEOGL_HELPER_H

#include "Texture2DArray.h"
#include "../resource/Texture2DArrayResource.h"

#include "Texture2D.h"
#include "../resource/Texture2DResource.h"

namespace graph
{
    namespace texhelper
    {
        using namespace resource;

        Texture2D * CreatTex2DByRes(Texture2DResource * res);
        Texture2DArray * CreatTex2DArrayByRes(Texture2DArrayResource * res,int width,int height,GLenum internal_format,GLenum filter = GL_LINEAR, GLenum wrap = GL_REPEAT);
    }
}

#endif //SIMPLEOGL_HELPER_H
