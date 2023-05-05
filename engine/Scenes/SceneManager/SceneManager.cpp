#include "SceneManager.h"
#include <iostream>
#include "engine/Scenes/Scene/Scene.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Windows/Window.h"
#include <GL/glew.h>

void SceneManager::UpdateCurrentScene(const float& _deltaTime)
{
    try
    {
        if(!mCurrentScene) throw CustomException("No current Scene.");
        mCurrentScene->Update(_deltaTime);
    }
    catch(const CustomException& e)
    {
        cerr << e.what() << '\n';
    }
    try
    {
        if(!mCurrentScene) throw CustomException("No current Scene.");
        mCurrentScene->LateUpdate(_deltaTime);
    }
    catch(const CustomException& e)
    {
        cerr << e.what() << '\n';
    }
}

void SceneManager::DrawCurrentScene(Camera* _activeCamera, Window* _window)
{
    try
    {
        if(!mCurrentScene) throw CustomException("No current Scene.");
        _window->EnableDepth(false);
        ((Skybox*)Skybox::Instance())->Draw(_activeCamera);
        _window->EnableDepth(true);
        Renderer::Instance()->Draw3DAxis();
        // _window->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        Renderer::Instance()->DrawObjects(_activeCamera);
        // _window->PolygonMode(GL_FRONT_AND_BACK,  GL_FILL);
    }
    catch(const CustomException& e)
    {
        cerr << e.what() << '\n';
    }
}

void SceneManager::AddScene(const string& _name, Scene* const _scene)
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

void SceneManager::LoadScene(const string& _name)
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

void SceneManager::UnloadCurrentScene()
{
    try
    {
        if(!mCurrentScene) throw CustomException("Can't unload current because there's no current scene.");
        mCurrentScene->UnloadScene();
    }
    catch(const CustomException& e)
    {
        cerr << e.what() << '\n';
    }
}

void SceneManager::AddSceneToMap(const string& _name, Scene* const _scene)
{
    if(mScenes[_name]) throw CustomException("Name : " + _name + " is already taken for another registered Scene.");
    mScenes[_name] = _scene;
}