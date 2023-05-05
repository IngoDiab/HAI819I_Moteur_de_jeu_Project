#pragma once

#include <vector>
using namespace std;

class FBO
{
    unsigned int mBufferHandle;
    vector<unsigned int> mTexturesHandle;

public:
    FBO();

public:
    void GenerateFBO();
    void DeleteFBO();

    void BindFBO();

    void GenerateTextures(unsigned int _nbTextures);
    void DeleteTextures();
};