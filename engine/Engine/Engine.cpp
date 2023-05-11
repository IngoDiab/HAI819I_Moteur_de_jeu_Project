#include "Engine.h"

#include <GLFW/glfw3.h>
#include "engine/Windows/Window.h"
#include "engine/Camera/Camera/Camera.h"

#include <iostream>

Engine::Engine(LAUNCH_MOD _launchMod, const int _widthWindow, const int _heightWindow, const string& _nameWindow) : mLaunchMod(_launchMod)
{
    CreateWindow(_widthWindow, _heightWindow, _nameWindow);
    GenerateVAO();
    CreateSkybox();
    //if(_launchMode == LAUNCH_MOD::GAME) return;
    CreateEditorCamera();

    InitializeMouseManager();
}

Engine::~Engine()
{
    delete mSkybox;
    delete mMainWindow;
}

void Engine::CreateWindow(const int _widthWindow, const int _heightWindow, const string& _nameWindow)
{
    const vector<float> _colorBackground = vector<float>{0.8f, 0.8f, 0.8f, 1.0f};
    mMainWindow = new Window(_widthWindow, _heightWindow, _nameWindow.c_str(), NULL, NULL, _colorBackground);
    //mMainWindow->ActivateInput(GLFW_STICKY_KEYS, GL_TRUE);
    mMainWindow->EnableDepth(true);
    mMainWindow->EnableCullFace(true);
}

void Engine::CreateSkybox()
{
    mSkybox = new Skybox();
}

void Engine::CreateEditorCamera()
{
    mEditorCamera = mObjectManager.Create<EditorCamera>(vec3(0), vec3(0), vec3(1), nullptr, DURABILITY::PERSISTENT);
    mEditorCamera->Initialize();
    ResetCameraToEditor();
}

void Engine ::GenerateVAO()
{
    mMainVAO.GenerateVAO();
    mMainVAO.BindVAO();
}

void Engine::InitializeMouseManager()
{
    bool _isEngineMod = mLaunchMod == LAUNCH_MOD::ENGINE;
    mMouseManager.EnableCursor(mMainWindow->GetWindow(), _isEngineMod);
    mMouseManager.InvertOnX(_isEngineMod);
    mMouseManager.InvertOnY(_isEngineMod);
}

void Engine::Run()
{
    MouseManager::Instance()->RefreshMousePosition(mMainWindow->GetWindow());
    do{
        CalculateDeltaTime();
        mObjectManager.ProcessDestroy();

        MouseManager::Instance()->RefreshMousePosition(mMainWindow->GetWindow());
        mInputManager.CheckStateAllKeys(mMainWindow->GetWindow());
        mInputManager.CheckStateAllAxis(mMainWindow->GetWindow());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mSceneManager.UpdateCurrentScene(mDeltaTime);
        mPhysicManager.UpdatePhysic(mDeltaTime);
        mSceneManager.DrawCurrentScene(mActiveCamera, mMainWindow);

        // Swap buffers
        glfwSwapBuffers(mMainWindow->GetWindow());
        glfwPollEvents();
        

    } while( glfwGetKey(mMainWindow->GetWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(mMainWindow->GetWindow()) == 0 );
}

void Engine::CalculateDeltaTime()
{
    float _currentFrame = glfwGetTime();
    mDeltaTime = _currentFrame - mLastFrame;
    mLastFrame = _currentFrame;
}

void Engine::SetViewportCamera(Camera* const _camera)
{
    if(!_camera) return ResetCameraToEditor();
    if(mActiveCamera) mActiveCamera->Activate(false);
    mActiveCamera = _camera;
    _camera->Activate(true);
}

void Engine::ResetCameraToEditor()
{
    SetViewportCamera(mEditorCamera);
}