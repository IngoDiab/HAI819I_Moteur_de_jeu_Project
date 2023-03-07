#pragma once

class IRotating
{
protected:
    float mRotationSpeed = 10;
    bool mCanRotate = false;

public:
    float GetRotationSpeed() const {return mRotationSpeed;}
    void SetRotationSpeed(const float _speed){mRotationSpeed = _speed;}

    bool CanMove() const {return mCanRotate;}
    void SetCanRotate(const bool _canRotate) {mCanRotate = _canRotate;}

public:
    virtual void RotateX(const float _rotation) = 0;
    virtual void RotateY(const float _rotation) = 0;
    virtual void RotateZ(const float _rotation) = 0;
};