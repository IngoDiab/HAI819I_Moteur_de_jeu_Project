#include "MouseManager.h"
#include <GLFW/glfw3.h>

void MouseManager::RefreshMousePosition(GLFWwindow* _window)
{
    double _newXPos, _newYPos;
    glfwGetCursorPos(_window, &_newXPos, &_newYPos);
    mXMovement = _newXPos - mXPosition;
    mYMovement = _newYPos - mYPosition;

    mXPosition = _newXPos;
    mYPosition = _newYPos;
}

void MouseManager::UseStandardCursor(GLFWwindow* _window, int _cursorID)
{
    if(mCursor) glfwDestroyCursor(mCursor);
    mCursor = glfwCreateStandardCursor(_cursorID);
    glfwSetCursor(_window, mCursor);
}