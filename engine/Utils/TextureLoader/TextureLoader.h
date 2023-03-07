#ifndef TEXTURELOADER_H_DEFINED
#define TEXTURELOADER_H_DEFINED

#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <GL/glew.h>
#include <vector>

unsigned char* loadImage(const std::string& _path, int& _width, int& _height, int& _channels, const int _forceChannel);
void freeImage(unsigned char* _image);

GLuint loadTexture2DFromFilePath(const std::string& path);
GLuint loadTextureCubeMap2DFromFilePath(const std::vector<std::string>& path);

void setDefaultTexture2DParameters(GLuint texture);
void setDefaultTextureCubemapParameters(GLuint texture);

#endif