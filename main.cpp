#include "../graph/Program.h"
#include "../graph/VertexArray.h"
#include "../graph/Texture2D.h"
#include "../resource/TextureResource.h"
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

    auto * image1 = new  TextureResource("Textures/1.jpg");
    image1->Load();
    auto * image2 = new  TextureResource("Textures/2.jpg");
    image2->Load();
    auto * image3 = new  TextureResource("Textures/3.jpg");
    image3->Load();
    auto * image4 = new  TextureResource("Textures/4.jpg");
    image4->Load();
    auto * image5 = new  TextureResource("Textures/5.jpg");
    image5->Load();
    auto * image6 = new  TextureResource("Textures/6.jpg");
    image6->Load();

    //Shader
    Shader * vs = Shader::Creat(GL_VERTEX_SHADER, "Shader/mod.vert");
    Shader * fs = Shader::Creat(GL_FRAGMENT_SHADER, "Shader/mod.frag");
    Program * pro = Program::Creat(vs, fs);
    pro->Compile();
    glUseProgram(pro->GetBufferID());

    //texture
    GLint i = glGetUniformLocation(pro->GetBufferID(), "mainTex");
    glUniform1i(i, 1);

    GLint s = glGetUniformLocation(pro->GetBufferID(), "scale");


    Texture2D * tex = Texture2D::Create(GL_RGB,GL_LINEAR_MIPMAP_LINEAR);
    tex->TexParameter(GL_TEXTURE_MAX_LEVEL,5);
    tex->TexImage(0,image1->GetWidth(),image1->GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,image1->GetData());
    tex->TexImage(1,image2->GetWidth(),image2->GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,image2->GetData());
    tex->TexImage(2,image3->GetWidth(),image3->GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,image3->GetData());
    tex->TexImage(3,image4->GetWidth(),image4->GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,image4->GetData());
    tex->TexImage(4,image5->GetWidth(),image5->GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,image5->GetData());
    tex->TexImage(5,image6->GetWidth(),image6->GetHeight(),GL_RGB,GL_UNSIGNED_BYTE,image6->GetData());
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
    glBindTexture(GL_TEXTURE_2D, tex->GetBufferID());
    float a = 1.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.3, 1.0);
        /* Swap front and back buffers */
        glUniform1f(s, a);
        glBindVertexArray(vao->GetBufferID());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        a -= 0.003;

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}