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
#include "engine/Lights/LightManager/LightManager.h"
#include "engine/Physic/PhysicManager/PhysicManager.h"
#include "engine/Game/Manager/GameManager.h"
#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Buffers/VAO/VAO.h"

class Window;
class Camera;

enum class LAUNCH_MOD
{
    ENGINE = 0,
    GAME = 1
};

class Engine final : public Singleton<Engine>
{
    LAUNCH_MOD mLaunchMod;

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
    LightManager mLightManager;
    PhysicManager mPhysicManager;
    GameManager mGameManager;

public:
    float DeltaTime() const {return mDeltaTime;}

    Window* GetWindow() const {return mMainWindow;};
    void SetWindow(Window* const _window) {mMainWindow = _window;};

    Camera* GetViewportCamera() const {return mActiveCamera;};
    LAUNCH_MOD GetLaunchMod() const {return mLaunchMod;}

public:
    Engine(LAUNCH_MOD _launchMod, const int _widthWindow, const int _heightWindow, const string& _nameWindow);
    ~Engine();

public:
    void CreateWindow(const int _widthWindow, const int _heightWindow, const string& _nameWindow);
    void CreateSkybox();
    void CreateEditorCamera();
    void GenerateVAO();
    void InitializeMouseManager();

    void Run();
    void CalculateDeltaTime();

    void SetViewportCamera(Camera* const _camera);
    void ResetCameraToEditor();
};