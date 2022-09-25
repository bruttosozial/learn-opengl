#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Shader
{
    unsigned int program_id_;
public:
    Shader(const char* vertex_path, const char* fragment_path);
    void use();
    void setBool(const char* &name, bool value) const;
    void setInt(const char* &name, int value) const;
    void setFloat(const char* &name, float value) const;
private:
    static void checkCompileErrors(unsigned int shader, std::string type);
};
