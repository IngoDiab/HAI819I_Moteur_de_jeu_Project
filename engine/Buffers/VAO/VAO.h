#pragma once

class VAO
{
    unsigned int mBufferHandle;

public:
    VAO();

public:
    void GenerateVAO();
    void DeleteVAO();

    void BindVAO();
};