//
// Created by ldoublej on 18-11-26.
//

#ifndef SIMPLE_OGL_APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class BaseApp
{
protected:
    int _height;
    int _width;
    const char * _title;
    GLFWwindow * _window;



public:
    /// @brief 一个Demo实例
    /// @param height Demo窗口高度
    /// @param width Demo窗口宽度
    /// @param title Demo窗口标题
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
        GLenum err = glewInit();
        if (err != GLEW_OK )
        {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            exit (-2);

        }
        return true;
    }
    virtual bool Init() = 0;
    virtual void RenderLoop() = 0;
};

#define SIMPLE_OGL_APPLICATION_H

#endif //SIMPLE_OGL_APPLICATION_H
