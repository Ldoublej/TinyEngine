//
// Created by ldoublej on 18-11-10.
//

#ifndef SIMPLEOGL_HELPER_H
#define SIMPLEOGL_HELPER_H

#include "Texture2DArray.h"
#include "Texture2D.h"
#include "CubeMap.h"

#include "../resource/Image2D.h"

namespace graph
{
    namespace helper
    {
        using namespace resource;

        void SetImageData(Image2D * res,Texture2D * texture2d);
        void SetImageData(Image2D ** images ,CubeMap * cubeMap);
    }
}

#endif //SIMPLEOGL_HELPER_H
