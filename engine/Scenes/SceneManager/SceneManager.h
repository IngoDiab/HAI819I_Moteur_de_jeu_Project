#pragma once

#include <string>
#include <map>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"

class Scene;
class Camera;
class Window;

#include <exception>
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

class SceneManager final : public Singleton<SceneManager>
{
    Scene* mCurrentScene = nullptr;
    map<string, Scene*> mScenes = map<string, Scene*>();

public:
    Scene* GetCurrentScene() {return mCurrentScene;}

public:
    void ProcessCurrentScene(Camera* _activeCamera, Window* _window, const float& _deltaTime);
    void AddScene(const string& _name, Scene* const _scene);
    void LoadScene(const string& _name);
    void UnloadCurrentScene();

private:
    void AddSceneToMap(const string& _name, Scene* const _scene);
};