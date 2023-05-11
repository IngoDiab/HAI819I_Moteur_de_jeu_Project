#include "MouseManager.h"
#include <GLFW/glfw3.h>

#include "engine/Engine/Engine.h"
#include "engine/Windows/Window.h"

void MouseManager::RefreshMousePosition(GLFWwindow* _window)
{
    if(mIsCursorEnabled)
    {
        double _newXPos, _newYPos;
        glfwGetCursorPos(_window, &_newXPos, &_newYPos);
        mXMovement = _newXPos - mXPosition;
        mYMovement = _newYPos - mYPosition;

        mXPosition = _newXPos;
        mYPosition = _newYPos;
    }
    else
    {
        double _newXPos, _newYPos;
        glfwGetCursorPos(_window, &_newXPos, &_newYPos);

        int _width, _height;
        glfwGetWindowSize(_window, &_width, &_height);

        mXMovement = _newXPos;
        mYMovement = _newYPos;

        glfwSetCursorPos(_window, 0, 0);
    }
}

void MouseManager::UseStandardCursor(GLFWwindow* _window, int _cursorID)
{
    if(mCursor) glfwDestroyCursor(mCursor);
    mCursor = glfwCreateStandardCursor(_cursorID);
    glfwSetCursor(_window, mCursor);
}

void MouseManager::EnableCursor(GLFWwindow* _window, bool _enable) 
{ 
    glfwSetInputMode(_window, GLFW_CURSOR, _enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED); 
    mIsCursorEnabled = _enable;
}