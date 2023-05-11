#pragma once

#include <vector>
using namespace std;

class GLFWwindow;
class GLFWmonitor;

class Window final
{
    GLFWwindow* mWindow = nullptr;
    vector<float> mBackgroundColor = vector<float>(4); //RGBA

public:
    GLFWwindow* GetWindow() const { return mWindow; }
    void SetWindow(GLFWwindow* const _window) { mWindow = _window; }

    vector<float> GetBackgroundColor() const { return mBackgroundColor; }
    void SetBackgroundColor(const vector<float>& _color) { mBackgroundColor = _color; RefreshBackgroundColor(); }

public:
    Window(const int _width, const int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share, const vector<float>& _backgroundColor);
    ~Window();

private:
    void InitializeGLFW();
    void InitializeGLEW();
    void WindowHint();
    void CreateWindow(const int _width, const int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share);
    void RefreshBackgroundColor();

public:
    void ActivateInput(const int _mode, const int _value);
    void PolygonMode(const unsigned int _faces, const unsigned int _mode);
    void EnableDepth(const bool _enable, const unsigned int _depthFunction = 0x0201); //default GL_LESS
    void EnableCullFace(const bool _enable, const unsigned int _depthFunction = 0x0405); //default GL_BACK
};
