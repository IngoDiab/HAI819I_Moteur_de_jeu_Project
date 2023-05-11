#pragma once

#include "engine/Utils/Singleton/Singleton.h"

class GLFWwindow;
class GLFWcursor;

class MouseManager final : public Singleton<MouseManager>
{
    GLFWcursor* mCursor = nullptr;
    bool mIsCursorEnabled = false;

    double mXPosition = 0;
    double mYPosition = 0;

    bool mXInverted = false;
    bool mYInverted = false;

    double mXMovement = 0;
    double mYMovement = 0;

public : 
    double GetXMouse() {return mXPosition;}
    double GetYMouse() {return mYPosition;}

    double GetXMouseMovement() {return mXInverted ? -mXMovement : mXMovement;}
    double GetYMouseMovement() {return mYInverted ? -mYMovement : mYMovement;}

    void InvertOnX(bool _invert) {mXInverted = _invert;}
    void InvertOnY(bool _invert) {mYInverted = _invert;}

public:
    void RefreshMousePosition(GLFWwindow* _window);
    void Reset(GLFWwindow* _window);

    void UseStandardCursor(GLFWwindow* _window, int _cursorID);
    void EnableCursor(GLFWwindow* _window, bool _enable);
};