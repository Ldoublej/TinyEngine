//
// Created by ldoublej on 18-12-23.
//

#include "SkyBox.h"

namespace scene
{

    SkyBox::SkyBox(Image2D **images, Program *program):_cubeMap(nullptr),_model(nullptr),_program(program)
    {
        _cubeMap = CubeMap::Create(GL_RGB);
        helper::SetImageData(images,_cubeMap);
        program->Unifrom1i("_SkyBox",10);
        _model = new Model("models/Cube.obj",_program);
    }

    void SkyBox::Draw()
    {
        glActiveTexture(GL_TEXTURE10);
        glBindTexture(GL_TEXTURE_CUBE_MAP,_cubeMap->GetBufferID());
        glDepthMask(GL_FALSE);
        _model->Draw();
        glBindTexture(GL_TEXTURE_CUBE_MAP,0);
        glDepthMask(GL_TRUE);
    }

    CubeMap *SkyBox::GetCubeMap() const
    {
        return _cubeMap;
    }

    Program *SkyBox::GetProgram() const
    {
        return _program;
    }

    void SkyBox::SetProgram(Program *program)
    {
        _program = program;;
    }
}

