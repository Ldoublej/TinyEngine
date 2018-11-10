#include "../graph/Program.h"
#include "../graph/VertexArray.h"
#include "../graph/Texture2D.h"
#include "resource/Texture2DResource.h"
#include "resource/Texture2DArrayResource.h"
#include "../graph/Texture2DArray.h"
#include "../graph/Helper.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>


int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    glfwSetWindowPos(window,300,150);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    using namespace graph;
    using namespace resource;

    //Shader
    Shader * vs = Shader::Creat(GL_VERTEX_SHADER, "Shader/mod.vert");
    Shader * fs = Shader::Creat(GL_FRAGMENT_SHADER, "Shader/mod.frag");
    Program * pro = Program::Creat(vs, fs);
    pro->Compile();
    glUseProgram(pro->GetBufferID());



    const char * filenames[] = {
            "Textures/Texture2DArray1.jpg",
            "Textures/Texture2DArray2.jpg",
            "Textures/Texture2DArray3.jpg"
    };

    Texture2DArrayResource * image = new Texture2DArrayResource(filenames,3);
    image->Load();

    Texture2DArray * tex =  texhelper::CreatTex2DArrayByRes(image,256,256,GL_RGB);

    GLint i = glGetUniformLocation(pro->GetBufferID(), "mainTex");
    glUniform1i(i, 1);

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

    VertexArray * vao = VertexArray::Create(GL_LINE, nullptr);
    vao->AddVertexBuffer(vertexdata);

    vao->ApplyVertexAttributes();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY,tex->GetBufferID());

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.3, 1.0);

        glBindVertexArray(vao->GetBufferID());
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}