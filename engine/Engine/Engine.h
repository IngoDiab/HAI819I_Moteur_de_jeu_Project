#pragma once
#include <string>
using namespace std;

#include "engine/Camera/EditorCamera/EditorCamera.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/Inputs/MouseManager/MouseManager.h"
#include "engine/Objects/ObjectManager/ObjectManager.h"
#include "engine/Renderer/Renderer.h"
#include "engine/ShaderHandlers/ShaderManager/ShaderManager.h"
#include "engine/Scenes/SceneManager/SceneManager.h"
#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Buffers/VAO/VAO.h"

class Window;
class Camera;

class Engine final : public Singleton<Engine>
{
    float mDeltaTime = 0.0f;	// time between current frame and last frame
    float mLastFrame = 0.0f;

    Window* mMainWindow = nullptr;
    Camera* mActiveCamera = nullptr;

    VAO mMainVAO;

    EditorCamera* mEditorCamera = nullptr;
    Skybox* mSkybox = nullptr;
    InputManager mInputManager;
    MouseManager mMouseManager;
    ObjectManager mObjectManager;
    Renderer mRenderer;
    ShaderManager mShaderManager;
    SceneManager mSceneManager;

public:
    float DeltaTime() const {return mDeltaTime;}

    Window* GetWindow() const {return mMainWindow;};
    void SetWindow(Window* const _window) {mMainWindow = _window;};

    Camera* GetViewportCamera() const {return mActiveCamera;};

public:
    Engine();

public:
    void Initialize(const int _widthWindow, const int _heightWindow, const string& _nameWindow);
    void Run();
    void CalculateDeltaTime();

    void SetViewportCamera(Camera* const _camera);
    void ResetCameraToEditor();
};