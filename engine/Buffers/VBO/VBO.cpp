#include "VBO.h"

VBO::VBO()
{

}

VBO::VBO(const GLenum _bufferType) : mBufferType(_bufferType)
{
    GenerateVBO();
}

VBO::VBO(VBO& _vbo) : mBufferType(_vbo.GetBufferType()), mBufferHandle(_vbo.GetBufferHandle())
{

}

VBO::~VBO()
{
    DeleteVBO();
}

void VBO::GenerateVBO()
{
    glGenBuffers(1, &mBufferHandle);
}

void VBO::DeleteVBO()
{
    glDeleteBuffers(1, &mBufferHandle);
}

void VBO::BindVBO()
{
    glBindBuffer(mBufferType, mBufferHandle);
}

void VBO::DrawVBO(const GLuint _attribute, const GLint _size, const GLenum _type, const GLboolean _normalized, const GLsizei _stride, const int _offsetBegin)
{
    glEnableVertexAttribArray(_attribute);
    BindVBO();
    glVertexAttribPointer(_attribute, _size, _type, _normalized, _stride, (void*)_offsetBegin);
}

void VBO::DrawVBOIndices(const GLenum _mode, const GLsizei _size, const int _offsetBegin)
{
    BindVBO();
    glDrawElements(_mode, _size, GL_UNSIGNED_SHORT, (void*)_offsetBegin);
}