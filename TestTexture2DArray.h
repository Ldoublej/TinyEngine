//
// Created by ldoublej on 18-11-26.
//

#include "Application.h"

#include "../graph/Program.h"
#include "../graph/VertexArray.h"
#include "../graph/Texture2D.h"
#include "resource/Texture2DResource.h"
#include "resource/Texture2DArrayResource.h"
#include "../graph/Texture2DArray.h"
#include "../graph/Helper.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

        Texture2DArrayResource * image = new Texture2DArrayResource(filenames,3);
        image->Load();
        Texture2DArray * tex = Texture2DArray::Create(GL_RGB);
        texhelper::SetImageData(image,tex);

        GLint i = glGetUniformLocation(pro->GetBufferID(), "mainTex");
        glUniform1i(i, 1);

        GLint u = glGetUniformLocation(pro->GetBufferID(), "M");

        glm::mat4 trans  = glm::translate(glm::mat4(1.0f),glm::vec3(0.0,0.0,0.0));
        glUniformMatrix4fv(u,1,GL_FALSE,glm::value_ptr(trans));
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