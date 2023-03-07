#pragma once

#include <vector>
using namespace std;

#include <GL/glew.h>

class VBO
{
    unsigned int mBufferType;
    unsigned int mBufferHandle;

protected:
    unsigned int GetBufferType() const {return mBufferType;}
    unsigned int GetBufferHandle() const {return mBufferHandle;}

public:
    VBO();
    VBO(const unsigned int _bufferType);
    VBO(VBO& _vbo);
    virtual ~VBO();

public:
    void GenerateVBO();
    void DeleteVBO();

    void BindVBO();

    template <typename BufferData>
    void CopyDataToVBO(const vector<BufferData>& _data);

    void DrawVBO(const unsigned int _attribute, const int _size, const unsigned int _type, const unsigned char _normalized = 0, const int _stride = 0, const int _offsetBegin = 0);
    void DrawVBOIndices(const unsigned int _mode, const int _size, const int _offsetBegin = 0);
};

template <typename BufferData>
void VBO::CopyDataToVBO(const vector<BufferData>& _data)
{
    BindVBO();
    glBufferData(mBufferType, _data.size() * sizeof(BufferData), &_data[0] , 0x88E4); //GL_STATIC_DRAW
}