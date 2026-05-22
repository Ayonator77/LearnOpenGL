#pragma once
#include "shader.h"

struct SceneData{
    unsigned int VAO, VBO, EBO;
    Shader shader;
    unsigned int texture;
};

unsigned int loadTexture(const char* path);
void exercise3();