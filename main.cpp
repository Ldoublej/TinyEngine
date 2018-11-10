#include "../graph/Program.h"
#include "../graph/VertexArray.h"
#include "../graph/Texture2D.h"
#include "../resource/TextureResource.h"
#include "../graph/Texture2DArray.h"
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


    //texture
    Texture2DArray * tex = Texture2DArray::Create(GL_RGB);
    tex->Storage(0,256,256,3);
    tex->TexImage(0,256,256,3,GL_RGB,GL_UNSIGNED_BYTE, nullptr);

    TextureResource * image1 = new TextureResource("Textures/Texture2DArray1.jpg");
    image1->Load();
    TextureResource * image2 = new TextureResource("Textures/Texture2DArray2.jpg");
    image2->Load();
    TextureResource * image3 = new TextureResource("Textures/Texture2DArray3.jpg");
    image3->Load();

    tex->TexSubImage(0,0,0,0,256,256,1,GL_RGB,GL_UNSIGNED_BYTE,image1->GetData());
    tex->TexSubImage(0,0,0,1,256,256,1,GL_RGB,GL_UNSIGNED_BYTE,image2->GetData());
    tex->TexSubImage(0,0,0,2,256,256,1,GL_RGB,GL_UNSIGNED_BYTE,image3->GetData());

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