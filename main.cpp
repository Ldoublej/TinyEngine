#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../graph/Program.h"
#include "../graph/VertexArray.h"
#include "../graph/Texture2D.h"
#include "resource/Image2D.h"
#include "resource/Image2DArray.h"
#include "../graph/Texture2DArray.h"
#include "../graph/Helper.h"
#include "scene/Camera.h"
#include "scene/Model.h"

scene::Camera * camera;
float lastX = 400, lastY = 300;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
void mouse_button_callback(GLFWwindow* window, double xpos,double ypos)
{
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    camera->SetYaw(camera->GetYaw() + xoffset);
    camera->SetPitch(camera->GetPitch() + yoffset);
    if(camera->GetPitch() > 89.0f)
        camera->SetPitch(89.0);
    if(camera->GetPitch() < -89.0f)
        camera->SetPitch(-89.0);

    camera->UpdateVector();
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_REPEAT)
        return;
    glm::vec3 loc = camera->GetWorld();
    glm::vec3 up = camera->GetUp();
    glm::vec3 right = glm::cross(camera->GetTarget(),up);
    right = glm::normalize(right);
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_W:
            loc += camera->GetTarget() * 2.0f *deltaTime;
            camera->SetWorld(loc);
            break;
        case GLFW_KEY_S:
            loc -= camera->GetTarget() * 2.0f *deltaTime;
            camera->SetWorld(loc);
            break;
        case GLFW_KEY_A:
            loc -= right * 2.0f *deltaTime;
            camera->SetWorld(loc);
            break;
        case GLFW_KEY_D:
            loc += right * 2.0f *deltaTime;
            camera->SetWorld(loc);
            break;
    }
}
int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return 1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow * _window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
    glfwSetWindowPos(_window,300,150);
    glfwSetKeyCallback(_window, key_callback);
    glfwSetCursorPosCallback(_window, mouse_button_callback);
    //glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!_window)
    {
        glfwTerminate();
        return 1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);
    GLenum err = glewInit();
    if (err != GLEW_OK )
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit (-2);

    }

    glViewport(0, 0, 800, 600);
    using namespace graph;
    using namespace resource;
    using namespace scene;

    camera = new Camera();
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

    //Shader
    Shader * vs = Shader::Creat(GL_VERTEX_SHADER, "shaders/mod.vert");
    Shader * fs = Shader::Creat(GL_FRAGMENT_SHADER, "shaders/mod.frag");
    Program * pro = Program::Creat(vs, fs);
    pro->Compile();
    glUseProgram(pro->GetBufferID());
    Model * mod = new Model("models/JT.obj");



    Image2D * image = new Image2D("textures/JT.tga");
    image->Load();
    Texture2D * tex = Texture2D::Create(GL_RGB);
    helper::SetImageData(image,tex);

    pro->Unifrom1i("mainTex",1);
    pro->Unifrom4fv("P",&projection[0][0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,tex->GetBufferID());
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(_window))
    {
        glm::mat4 view = camera->GetViewMatrix();
        pro->Unifrom4fv("V",&view[0][0]);
        glClearColor(0.2, 0.2, 0.3, 1.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        mod->Draw();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    glfwTerminate();


}