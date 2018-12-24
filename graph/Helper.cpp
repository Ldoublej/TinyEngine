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
            texture2d->TexImage(0,res->GetWidth(),res->GetHeight(),res->GetFormat(),res->GetType(),res->GetData());
        }
        void SetImageData(Image2D ** images ,CubeMap * cubeMap)
        {
            for(unsigned int i = 0; i < 6; i++)
            {
                Image2D * image = images[i];
                image->Load();
                cubeMap->TexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,image->GetWidth(),image->GetHeight(),image->GetFormat(),image->GetType(),image->GetData());
            }
        }
    }
}