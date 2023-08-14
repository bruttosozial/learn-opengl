#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include "Lessons.h"

unsigned int Lessons::generateTexture1VAO()
{
    float rectangleColorTextureData[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
       };

        unsigned int squareIndices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        
        unsigned int vaoId;
        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);
    
        unsigned int vboId;
        glGenBuffers(1, &vboId);
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleColorTextureData), rectangleColorTextureData, GL_STATIC_DRAW);

        unsigned int eboId;
        glGenBuffers(1, &eboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

        // Position Attribute
        glVertexAttribPointer(
        0, // location of the position attribute, as specified in the shader source
        3, // pointer has 3 values
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);

        // Color Attribute
        glVertexAttribPointer(
        1, // location of the position attribute, as specified in the shader source
        3, // pointer has 3 values
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Tex Coordinates
        glVertexAttribPointer(
        2, // location of the position attribute, as specified in the shader source
        2, // pointer has 3 values
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        reinterpret_cast<void*>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        return vaoId;
}

unsigned Lessons::generateColorVao()
{
    float colorVertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
   };
    
    unsigned int vaoIdColor;
    glGenVertexArrays(1, &vaoIdColor);
    glBindVertexArray(vaoIdColor);
    
    unsigned int vboIdColor;
    glGenBuffers(1, &vboIdColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboIdColor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorVertices), colorVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(
    0, // location of the position attribute, as specified in the shader source
    3, // pointer has 3 values
    GL_FLOAT,
    GL_FALSE,
    6 * sizeof(float),
    reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
    1, // location of the position attribute, as specified in the shader source
    3, // pointer has 3 values
    GL_FLOAT,
    GL_FALSE,
    6 * sizeof(float),
    reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return vaoIdColor;
}
