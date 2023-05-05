#include "FBO.h"

#include <GL/glew.h>
#include "engine/Engine/Engine.h"
#include "engine/Windows/Window.h"

FBO::FBO()
{

}

void FBO::GenerateFBO()
{
    glGenFramebuffers(1, &mBufferHandle);
}

void FBO::DeleteFBO()
{
    glDeleteFramebuffers(1, &mBufferHandle);
}

void FBO::BindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mBufferHandle);
}

void FBO::GenerateTextures(unsigned int _nbTextures)
{
    BindFBO();
    DeleteTextures();

    Window* _window = Engine::Instance()->GetWindow();

    glGenTextures(_nbTextures, &mTexturesHandle[0]);

    for (unsigned int i = 0; i < _nbTextures; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, mTexturesHandle[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _window->GetWidth(), _window->GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mTexturesHandle[i], 0);
    } 
}

void FBO::DeleteTextures()
{
    glDeleteTextures(mTexturesHandle.size(), &mTexturesHandle[0]);
    mTexturesHandle.clear();
}