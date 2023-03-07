#include "VAO.h"

#include <GL/glew.h>

VAO::VAO()
{

}

void VAO::GenerateVAO()
{
    glGenVertexArrays(1, &mBufferHandle);
}

void VAO::DeleteVAO()
{
    glDeleteVertexArrays(1, &mBufferHandle);
}

void VAO::BindVAO()
{
    glBindVertexArray(mBufferHandle);
}