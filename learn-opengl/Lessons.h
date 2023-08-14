#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"

class Lessons
{
public:
    unsigned int generateTexture1VAO();
    unsigned int generateColorVao();
};


