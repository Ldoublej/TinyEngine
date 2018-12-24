#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../graph/Program.h"
#include "../graph/VertexArray.h"
#include "../graph/Texture2D.h"
#include "resource/Image2D.h"
#include "../graph/Texture2DArray.h"
#include "../graph/Helper.h"
#include "scene/Camera.h"
#include "scene/Model.h"
#include "scene/SkyBox.h"

scene::Camera * camera = new scene::Camera();
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
void processInput(GLFWwindow *window)
{
    glm::vec3 loc = camera->GetWorld();
    glm::vec3 up = camera->GetUp();
    glm::vec3 right = glm::cross(camera->GetTarget(),up);
    right = glm::normalize(right);

    float cameraSpeed = 0.1f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed = 0.05;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        loc += cameraSpeed * camera->GetTarget() ;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        loc -= cameraSpeed * camera->GetTarget() ;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        loc -= right * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        loc += right * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwTerminate();
        exit(0);
    }

    camera->SetWorld(loc);
}
int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return 1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow * _window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
    glfwSetWindowPos(_window,300,150);
    glfwSetCursorPosCallback(_window, mouse_button_callback);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    //Shader
    Shader * skyboxVs = Shader::Creat(GL_VERTEX_SHADER, "shaders/skybox.vert");
    Shader * skyboxFs = Shader::Creat(GL_FRAGMENT_SHADER, "shaders/skybox.frag");
    Program * skyboxShader = Program::Creat(skyboxVs, skyboxFs);
    skyboxShader->Compile();
    Shader * baseVs = Shader::Creat(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader * baseFs = Shader::Creat(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    Program * baseShader = Program::Creat(baseVs, baseFs);
    skyboxShader->Compile();
    baseShader->Compile();


    Image2D * iamges[] = {
            new Image2D("textures/skybox/Right.jpg",GL_RGB,GL_UNSIGNED_BYTE),
            new Image2D("textures/skybox/Left.jpg",GL_RGB,GL_UNSIGNED_BYTE),
            new Image2D("textures/skybox/Top.jpg",GL_RGB,GL_UNSIGNED_BYTE),
            new Image2D("textures/skybox/Bottom.jpg",GL_RGB,GL_UNSIGNED_BYTE),
            new Image2D("textures/skybox/Back.jpg",GL_RGB,GL_UNSIGNED_BYTE),
            new Image2D("textures/skybox/Front.jpg",GL_RGB,GL_UNSIGNED_BYTE),
    };

    auto * skybox = new SkyBox(iamges,skyboxShader);
    auto * mod = new Model("models/sponza/sponza.obj",baseShader);

    glm::mat4 projection;
    glm::mat4 scale;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    baseShader->Unifrom4fv("P",&projection[0][0]);
    baseShader->Unifrom1i("_DiffuseMap",1);
    skyboxShader->Unifrom4fv("P",&projection[0][0]);
    scale = glm::scale(glm::mat4(1.0),glm::vec3(0.01));
    baseShader->Unifrom4fv("M",&scale[0][0]);


    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(_window))
    {
        processInput(_window);
        glClearColor(0.2, 0.2, 0.3, 1.0);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


        glm::mat4 skyboxView = camera->GetViewMatrixWithoutLocation();
        skyboxShader->Unifrom4fv("V",&skyboxView[0][0]);
        glm::mat4 baseView = camera->GetViewMatrix();
        baseShader->Unifrom4fv("V",&baseView[0][0]);

        skybox->Draw();
        mod->Draw();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    glfwTerminate();


}