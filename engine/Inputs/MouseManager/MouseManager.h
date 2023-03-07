#pragma once

#include "engine/Utils/Singleton/Singleton.h"

class GLFWwindow;
class GLFWcursor;

class MouseManager final : public Singleton<MouseManager>
{
    GLFWcursor* mCursor = nullptr;

    double mXPosition;
    double mYPosition;

    bool mXInverted = true;
    bool mYInverted = true;

    double mXMovement = 0;
    double mYMovement = 0;

public : 
    double GetXMouse() {return mXPosition;}
    double GetYMouse() {return mYPosition;}

    double GetXMouseMovement() {return mXInverted ? -mXMovement : mXMovement;}
    double GetYMouseMovement() {return mYInverted ? -mYMovement : mYMovement;}

    void RefreshMousePosition(GLFWwindow* _window);

    void UseStandardCursor(GLFWwindow* _window, int _cursorID);
};