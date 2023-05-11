#include "Window.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Window::Window(const int _width, const int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share, const vector<float>& _backgroundColor)
{
    InitializeGLFW();
    WindowHint();
    CreateWindow(_width, _height, _title, _monitor, _share);
    InitializeGLEW();
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(mWindow, _width/2, _height/2);
    auto _resizeCallback =[](GLFWwindow* _window, int _width, int _height)
                            {
                                glViewport(0, 0, _width, _height);
                            };
    glfwSetFramebufferSizeCallback(mWindow, _resizeCallback);
    mBackgroundColor = _backgroundColor;
    RefreshBackgroundColor();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::InitializeGLFW()
{
    const bool _success = glfwInit(); 
    if(_success) return;
    fprintf( stderr, "Failed to initialize GLFW\n" );
    getchar();
}

void Window::InitializeGLEW()
{
    glewExperimental = true; // Needed _planeIDfor core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return;
    }
}

void Window::WindowHint()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::CreateWindow(const int _width, const int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share)
{
    mWindow = glfwCreateWindow( _width, _height, _title, _monitor, _share);
    if( mWindow == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(mWindow);
}

void Window::RefreshBackgroundColor()
{
    glClearColor(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], mBackgroundColor[3]);
}

void Window::ActivateInput(const int _mode, const int _value)
{
    glfwSetInputMode(mWindow, _mode, _value);
}

void Window::PolygonMode(const GLenum _faces, const GLenum _mode)
{
    glPolygonMode(_faces, _mode);
}

void Window::EnableDepth(const bool _enable, const GLenum _depthFunction)
{
    if(_enable)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(_depthFunction);
    }
    else glDisable(GL_DEPTH_TEST);
    glDepthMask(_enable);
}

void Window::EnableCullFace(const bool _enable, const GLenum _cullFunction)
{
    if(_enable)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(_cullFunction);
    }
    else glDisable(GL_CULL_FACE);
}