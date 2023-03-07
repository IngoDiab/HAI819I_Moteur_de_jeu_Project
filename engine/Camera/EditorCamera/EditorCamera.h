#pragma once

#include "engine/Camera/Camera/Camera.h"
#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Utils/Interfaces/IMoving.h"
#include "engine/Utils/Interfaces/IRotating.h"

class EditorCamera final : public Camera, public IMoving, public IRotating, public Singleton<EditorCamera>
{
public:
    EditorCamera();
    EditorCamera(const vec3& _position, const vec3& _rotation);

public:
    void Initialize();

    virtual void MoveLateral(const float _move) override;
    virtual void MoveForwardBackward(const float _move) override;
    virtual void MoveUpDown(const float _move) override;

    void BeginRotate(const bool _rotate);
    virtual void RotateX(float _rotation) override;
    virtual void RotateY(float _rotation) override;
    virtual void RotateZ(float _rotation) override;
};