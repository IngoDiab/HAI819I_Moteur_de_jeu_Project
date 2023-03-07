#pragma once
#include <map>
#include <string>
#include <exception>

#include "engine/Camera/EditorCamera/EditorCamera.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/Inputs/MouseManager/MouseManager.h"
#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Buffers/VAO/VAO.h"

class Window;
class Camera;
class Scene;

class CustomException: public exception
{
    string mErrorException = "";

public:
    CustomException(const string& _msg) : mErrorException(_msg){}
    virtual const char* what() const throw()
    {
        return mErrorException.c_str();
    }
};

class Engine final : public Singleton<Engine>
{
    float mDeltaTime = 0.0f;	// time between current frame and last frame
    float mLastFrame = 0.0f;

    Window* mMainWindow = nullptr;
    Camera* mActiveCamera = nullptr;
    
    Scene* mCurrentScene = nullptr;
    map<string, Scene*> mScenes = map<string, Scene*>();

    VAO mMainVAO;

    EditorCamera mEditorCamera;
    InputManager mInputManager;
    MouseManager mMouseManager;

public:
    float DeltaTime() const {return mDeltaTime;}

    Window* GetWindow() const {return mMainWindow;};
    void SetWindow(Window* const _window) {mMainWindow = _window;};

    Camera* GetViewportCamera() const {return mActiveCamera;};

    Scene* GetCurrentScene() {return mCurrentScene;}

public:
    Engine();

public:
    void Initialize(const int _widthWindow, const int _heightWindow, const string& _nameWindow);
    void Run();
    void CalculateDeltaTime();

    void AddScene(const string& _name, Scene* const _scene);
    void LoadScene(const string& _name);
    void UnloadCurrentScene();

    void SetViewportCamera(Camera* const _camera);
    void ResetCameraToEditor();

private:
    void AddSceneToMap(const string& _name, Scene* const _scene);
};