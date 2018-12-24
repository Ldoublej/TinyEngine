//
// Created by ldoublej on 18-12-23.
//

#ifndef SIMPLE_OGL_SKYBOX_H

#include "../graph/CubeMap.h"
#include "../graph/Helper.h"
#include "../graph/Program.h"
#include "../scene/Model.h"

namespace scene
{
    using namespace graph;
    using namespace resource;

    class SkyBox
    {
    private:
        CubeMap * _cubeMap;
        Program * _program;
        Model * _model;
    public:
        SkyBox(Image2D * images[6],Program * program);

        CubeMap * GetCubeMap() const;
        Program * GetProgram() const;
        void SetProgram(Program * program);

        void Draw();

        ~SkyBox()
        {
            delete _cubeMap;
        }

    };
}

#define SIMPLE_OGL_SKYBOX_H

#endif //SIMPLE_OGL_SKYBOX_H
