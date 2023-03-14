#include "Engine.h"

#include <GLFW/glfw3.h>
#include "engine/Windows/Window.h"
#include "engine/Camera/Camera/Camera.h"

#include <iostream>

Engine::Engine()
{}

void Engine::Initialize(const int _widthWindow, const int _heightWindow, const string& _nameWindow)
{
    const vector<float> _colorBackground = vector<float>{0.8f, 0.8f, 0.8f, 1.0f};
    mMainWindow = new Window(_widthWindow, _heightWindow, _nameWindow.c_str(), NULL, NULL, _colorBackground);
    mMainWindow->ActivateInput(GLFW_STICKY_KEYS, GL_TRUE);
    mMainWindow->EnableDepth(true);

    mEditorCamera = mObjectManager.Create<EditorCamera>();
    mEditorCamera->Initialize();
    ResetCameraToEditor();

    mMainVAO.GenerateVAO();
    mMainVAO.BindVAO();
}

void Engine::Run()
{
    MouseManager::Instance()->RefreshMousePosition(mMainWindow->GetWindow());
    do{
        CalculateDeltaTime();
        MouseManager::Instance()->RefreshMousePosition(mMainWindow->GetWindow());
        mInputManager.CheckStateAllKeys(mMainWindow->GetWindow());
        mInputManager.CheckStateAllAxis(mMainWindow->GetWindow());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mSceneManager.ProcessCurrentScene(mActiveCamera, mMainWindow, mDeltaTime);

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