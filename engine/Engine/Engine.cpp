#include "Engine.h"

#include<iostream>
using namespace std;

#include <GLFW/glfw3.h>
#include "engine/Windows/Window.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Scenes/Scene/Scene.h"

Engine::Engine()
{}

void Engine::Initialize(const int _widthWindow, const int _heightWindow, const string& _nameWindow)
{
    const vector<float> _colorBackground = vector<float>{0.8f, 0.8f, 0.8f, 1.0f};
    mMainWindow = new Window(_widthWindow, _heightWindow, _nameWindow.c_str(), NULL, NULL, _colorBackground);
    mMainWindow->ActivateInput(GLFW_STICKY_KEYS, GL_TRUE);
    mMainWindow->EnableDepth(true);

    mEditorCamera.Initialize();
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
        try
        {
            if(!mCurrentScene) throw CustomException("No current Scene.");
            mCurrentScene->Update(mDeltaTime);
        }
        catch(const CustomException& e)
        {
            cerr << e.what() << '\n';
        }
        
        try
        {
            if(!mActiveCamera) throw CustomException("No active Camera.");
            mActiveCamera->RefreshCamera();
        }
        catch(const CustomException& e)
        {
            cerr << e.what() << '\n';
        }

        try
        {
            if(!mCurrentScene) throw CustomException("No current Scene.");
            mMainWindow->EnableDepth(false);
            mCurrentScene->DrawSkybox(mActiveCamera);
            mMainWindow->EnableDepth(true);
            // mMainWindow->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            mCurrentScene->DrawScene(mActiveCamera);
            // mMainWindow->PolygonMode(GL_FRONT_AND_BACK,  GL_FILL);
        }
        catch(const CustomException& e)
        {
            cerr << e.what() << '\n';
        }

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

void Engine::AddSceneToMap(const string& _name, Scene* const _scene)
{
    if(mScenes[_name]) throw CustomException("Name : " + _name + " is already taken for another registered Scene.");
    mScenes[_name] = _scene;
}

void Engine::AddScene(const string& _name, Scene* const _scene)
{
    try
    {
        AddSceneToMap(_name, _scene);
    }
    catch(const CustomException& e)
    {
        cerr << e.what() << '\n';
    }
}

void Engine::LoadScene(const string& _name)
{
    if(mCurrentScene) mCurrentScene->UnloadScene();
    try
    {
        mCurrentScene = mScenes[_name];
        if(!mCurrentScene) throw CustomException("Can't load scene " + _name + " because scene is not registered.");
        mCurrentScene->LoadScene();
    }
    catch(const CustomException& e)
    {
        cerr << e.what() << '\n';
    }
}

void Engine::UnloadCurrentScene()
{
    try
    {
        if(!mCurrentScene) throw CustomException("Can't unload current because there's no current scene.");
        mCurrentScene->LoadScene();
    }
    catch(const CustomException& e)
    {
        cerr << e.what() << '\n';
    }
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
    SetViewportCamera(&mEditorCamera);
}