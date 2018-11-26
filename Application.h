//
// Created by ldoublej on 18-11-26.
//

#ifndef SIMPLE_OGL_APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class BaseApp
{
protected:
    int _height;
    int _width;
    const char * _title;
    GLFWwindow * _window;

private:
    bool InitOglContent()
    {
        /* Initialize the library */
        if (!glfwInit())
            return false;

        /* Create a windowed mode window and its OpenGL context */
        _window = glfwCreateWindow(_height, _width, _title, nullptr, nullptr);
        glfwSetWindowPos(_window,300,150);
        if (!_window)
        {
            glfwTerminate();
            return false;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(_window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        return true;
    }
    virtual bool Init() = 0;
    virtual void RenderLoop() = 0;

public:
    BaseApp(int height,int width,const char * title):_height(height),_width(width),_title(title){};
    bool Run()
    {
        if(!InitOglContent())
        {
            return false;
        }
        if(!Init())
        {
            return false;
        }
        while (!glfwWindowShouldClose(_window))
        {
            RenderLoop();
            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
        glfwTerminate();
    }


    virtual ~BaseApp() = default;
};

#define SIMPLE_OGL_APPLICATION_H

#endif //SIMPLE_OGL_APPLICATION_H
