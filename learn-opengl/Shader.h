#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Shader
{
public:
    unsigned int program_id_;
    Shader(const char* vertex_path, const char* fragment_path);
    void use();
    void setBool(const char* &name, bool value) const;
    void setInt(const char* &name, int value) const;
    void setFloat(const char* &name, float value) const;
    void set4f(const char* &name, float value1, float value2, float value3, float value4) const;
private:
    static void checkCompileErrors(unsigned int shader, std::string type);
};
