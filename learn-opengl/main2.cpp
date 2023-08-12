#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

unsigned int initializeShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
static unsigned int initializeShader(const char* source, int type);
static GLFWwindow* initializeWindow();
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);}";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);}";

int main()
{
    
    GLFWwindow* window = initializeWindow();
    if(window == nullptr) {return -1;}

    // The vertices of the first triangle
    float verticesTriangle[] = {
        -0.5f, -0.5f,  0.0f, // lower left
         0.5f, -0.5f,  0.0f, // lower right
         0.0f,  0.5f,  0.0f  // up
    };

    float verticesTriangle2[] = {
        -0.5f, -1.5f,  0.0f,  // 2 - lower left
         0.5f, -1.5f,  0.0f,  // 2 - lower right
         0.0f, -0.5f,  0.0f   // 2 - up
    };

    
    float squareVertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left 
   };
    unsigned int squareIndices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  
    
    // Create the shader programs
    unsigned int shaderProgramId = initializeShaderProgram(vertexShaderSource, fragmentShaderSource);
    unsigned int shaderProgramId2 = initializeShaderProgram(vertexShaderSource, fragmentShaderSource2);
    
    unsigned int vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    unsigned int vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);
    
    glVertexAttribPointer(
    0, // location of the position attribute, as specified in the shader source
    3, // pointer has 3 values
    GL_FLOAT,
    GL_FALSE,
    3 * sizeof(float),
    reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    
    unsigned int vaoId2;
    glGenVertexArrays(1, &vaoId2);
    glBindVertexArray(vaoId2);
    
    unsigned int vboId2;
    glGenBuffers(1, &vboId2);
    glBindBuffer(GL_ARRAY_BUFFER, vboId2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle2), verticesTriangle2, GL_STATIC_DRAW);
    
    glVertexAttribPointer(
    0, // location of the position attribute, as specified in the shader source
    3, // pointer has 3 values
    GL_FLOAT,
    GL_FALSE,
    3 * sizeof(float),
    reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    
    unsigned int vaoId3;
    glGenVertexArrays(1, &vaoId3);
    glBindVertexArray(vaoId3);
    
    unsigned int vboId3;
    glGenBuffers(1, &vboId3);
    glBindBuffer(GL_ARRAY_BUFFER, vboId3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

    unsigned int eboId;
    glGenBuffers(1, &eboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(
    0, // location of the position attribute, as specified in the shader source
    3, // pointer has 3 values
    GL_FLOAT,
    GL_FALSE,
    3 * sizeof(float),
    reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window)) {
        
        processInput(window);
        
        glClearColor(0.38f, 0.38f, 0.38f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        /*
        glUseProgram(shaderProgramId);
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramId2);
        glBindVertexArray(vaoId2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        */

        glUseProgram(shaderProgramId);
        glBindVertexArray(vaoId3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int initializeShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    unsigned int vertexShaderId = initializeShader(vertexShaderSource, GL_VERTEX_SHADER);
    if(vertexShaderId == -1) {return -1;}
    
    unsigned int fragmentShaderId = initializeShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    if(fragmentShaderId == -1) {return -1;}
    
    // Create the shader program
    unsigned int shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);
    int success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return -1;
    }

    // glUseProgram(shaderProgramId);
    
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return shaderProgramId;
}

unsigned int initializeShader(const char* source, int type)
{
    unsigned int id;

    id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int compilationSuccess;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compilationSuccess);
    if(!compilationSuccess)
    {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    
    return id;
}

GLFWwindow* initializeWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "opengl lern", NULL, NULL);
    if (window == nullptr) {
        std::cout << "no window here :((" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // Information for OpenGL to translate internal coordinates to screen coordinates
    // (Internal OpenGL Coordinates go from -1 to 1)
    glViewport(0, 0, 800, 600);

    // Everytime the window gets resized, GLFW executes the callback to give the OpenGL context the new information
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

