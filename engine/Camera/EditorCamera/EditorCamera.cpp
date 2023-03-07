#include "EditorCamera.h"

#include "engine/Engine/Engine.h"
#include "engine/Windows/Window.h"
#include "engine/Inputs/InputManager/InputManager.h"

EditorCamera::EditorCamera(){};

EditorCamera::EditorCamera(const vec3& _position, const vec3& _rotation) : Camera(_position, _rotation)
{
};

void EditorCamera::Initialize()
{
    //Rotation
    InputManager::Instance()->BindKey(GLFW_MOUSE_BUTTON_RIGHT, ACTION_TYPE::HOLD, this, (void* (Object::*)(bool))&EditorCamera::BeginRotate);
    InputManager::Instance()->BindAxis({{MOUSE_Y, MOUSE_Y}}, this, (void* (Object::*)(float))&EditorCamera::RotateX);
    InputManager::Instance()->BindAxis({{MOUSE_X, MOUSE_X}}, this, (void* (Object::*)(float))&EditorCamera::RotateY);

    //Move Camera
    InputManager::Instance()->BindAxis({{GLFW_KEY_W, GLFW_KEY_S}}, this, (void* (Object::*)(float))&EditorCamera::MoveForwardBackward);
    InputManager::Instance()->BindAxis({{GLFW_KEY_D, GLFW_KEY_A}}, this, (void* (Object::*)(float))&EditorCamera::MoveLateral);
    InputManager::Instance()->BindAxis({{GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT}}, this, (void* (Object::*)(float))&EditorCamera::MoveUpDown);
}

void EditorCamera::MoveLateral(float _move)
{
    if(!mIsActive) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetRightVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void EditorCamera::MoveForwardBackward(float _move)
{
    if(!mIsActive) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetForwardVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void EditorCamera::MoveUpDown(float _move)
{
    if(!mIsActive) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetUpVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void EditorCamera::BeginRotate(const bool _rotate)
{
    if(!mIsActive) return;
    if(_rotate && !mCanRotate)
    {
        mCanRotate = true;
        Window* _currentWindow = Engine::Instance()->GetWindow();
        MouseManager::Instance()->UseStandardCursor(_currentWindow->GetWindow(), GLFW_HAND_CURSOR);
    }
    else if(!_rotate && mCanRotate)
    {
        mCanRotate = false;
        Window* _currentWindow = Engine::Instance()->GetWindow();
        MouseManager::Instance()->UseStandardCursor(_currentWindow->GetWindow(), GLFW_ARROW_CURSOR);
    }
}

void EditorCamera::RotateX(float _rotate)
{
    if(!mCanRotate || !mIsActive)return;
    GameObject::RotateX(_rotate, mRotationSpeed);
}

void EditorCamera::RotateY(float _rotate)
{
    if(!mCanRotate || !mIsActive)return;
    GameObject::RotateY(_rotate, mRotationSpeed);
}

void EditorCamera::RotateZ(float _rotate)
{
    if(!mCanRotate || !mIsActive)return;
    GameObject::RotateZ(_rotate, mRotationSpeed);
}