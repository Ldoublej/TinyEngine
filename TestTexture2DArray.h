//
// Created by ldoublej on 18-11-26.
//

#include "Application.h"

#include "../graph/Program.h"
#include "../graph/VertexArray.h"
#include "../graph/Texture2D.h"
#include "resource/Image2D.h"
#include "resource/Image2DArray.h"
#include "../graph/Texture2DArray.h"
#include "../graph/Helper.h"

#include <iostream>

class TestTexture2DArray : public BaseApp
{
public:
    using BaseApp::BaseApp;
private:
    graph::VertexArray * _vao;
private:
    bool Init()
    {
        glViewport(0, 0, 800, 600);
        using namespace graph;
        using namespace resource;
        
        //Shader
        Shader * vs = Shader::Creat(GL_VERTEX_SHADER, "shaders/mod.vert");
        Shader * fs = Shader::Creat(GL_FRAGMENT_SHADER, "shaders/mod.frag");
        Program * pro = Program::Creat(vs, fs);
        pro->Compile();
        glUseProgram(pro->GetBufferID());



        const char * filenames[] = {
                "textures/Texture2DArray1.jpg",
                "textures/Texture2DArray2.jpg",
                "textures/Texture2DArray3.jpg"
        };

        Image2DArray * image = new Image2DArray(filenames,3);
        image->Load();
        Texture2DArray * tex = Texture2DArray::Create(GL_RGB);
        helper::SetImageData(image,tex);

        pro->Unifrom1i("mainTex",1);

        //vertex data
        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.0f,0.0f,
                0.5f, -0.5f, 0.0f,
                1.0f,0.0f,
                0.0f,  0.5f, 0.0f,
                0.5f,1.0f
        };

        VertexBuffer * vertexdata = VertexBuffer::Create();
        vertexdata->SetData(sizeof(vertices), vertices, GL_STATIC_DRAW);
        vertexdata->AddAttribute( 0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
        vertexdata->AddAttribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

        _vao = VertexArray::Create(GL_LINE, nullptr);
        _vao->AddVertexBuffer(vertexdata);

        _vao->ApplyVertexAttributes();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D_ARRAY,tex->GetBufferID());
        return true;
    }
    void RenderLoop() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.3, 1.0);
        glBindVertexArray(_vao->GetBufferID());
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};