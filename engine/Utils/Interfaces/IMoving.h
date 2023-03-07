#pragma once

class IMoving
{
protected:
    float mMovementSpeed = 10;
    bool mCanMove = true;

public:
    float GetMovementSpeed() const {return mMovementSpeed;}
    void SetMovementSpeed(const float _speed) {mMovementSpeed = _speed;}

    bool CanMove() const {return mCanMove;}
    void SetCanMove(const bool _canMove) {mCanMove = _canMove;}

public:
    virtual void MoveLateral(const float _move) = 0;
    virtual void MoveForwardBackward(const float _move) = 0;
    virtual void MoveUpDown(const float _move) = 0;
};