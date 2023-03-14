#pragma once

class ITickable
{
protected:
    float mTickSpeed = 1;
    bool mCanTick = true;

public:
    float GetTickSpeed() const {return mTickSpeed;}
    void SetTickSpeed(const float _speed) {mTickSpeed = _speed;}

    bool CanTick() const {return mCanTick;}
    void SetTick(const bool _canTick) {mCanTick = _canTick;}

public:
    virtual void Update(const float _tickSpeed) = 0;
    virtual void LateUpdate(const float _tickSpeed) = 0;
};