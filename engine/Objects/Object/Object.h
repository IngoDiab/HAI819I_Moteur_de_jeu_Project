#pragma once

enum class DURABILITY
{
    SCENE,
    PERSISTENT
};

class Object
{
protected:
    DURABILITY mDurability = DURABILITY::SCENE;

public:
    virtual DURABILITY GetDurability() {return mDurability;}
    virtual void SetDurability(const DURABILITY _durability) {mDurability = _durability;}
};