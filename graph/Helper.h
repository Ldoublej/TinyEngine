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

        void SetImageData(Texture2DResource * res,Texture2D * texture2d);
        void SetImageData(Texture2DArrayResource * res,Texture2DArray * texture2d_array);
    }
}

#endif //SIMPLEOGL_HELPER_H
