#include "Shader.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(const char* vertex_path, const char* fragment_path)
{
    // retrieve code from filepath
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream v_shader_file;
    std::ifstream f_shader_file;
    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        v_shader_file.open(vertex_path);
        f_shader_file.open(fragment_path);

        std::stringstream v_shader_stream, f_shader_stream;

        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();

        v_shader_file.close();
        f_shader_file.close();

        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
    }
    catch(std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();

    // compile shaders
    // vertex
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &v_shader_code, nullptr);
    glCompileShader(vertex_shader_id);
    checkCompileErrors(vertex_shader_id, "VERTEX");

    // fragment
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1,  &f_shader_code, nullptr);
    glCompileShader(fragment_shader_id);
    checkCompileErrors(fragment_shader_id, "FRAGMENT");

    // shader program
    program_id_ = glCreateProgram();
    glAttachShader(program_id_, vertex_shader_id);
    glAttachShader(program_id_, fragment_shader_id);
    glLinkProgram(program_id_);
    checkCompileErrors(program_id_, "PROGRAM");

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}
void Shader::use()
{
    glUseProgram(program_id_);
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const char* &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(program_id_, name), (int) value); 
}
// ------------------------------------------------------------------------
void Shader::setInt(const char* &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(program_id_, name), value); 
}
// ------------------------------------------------------------------------
void Shader::setFloat(const char* &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(program_id_, name), value); 
}
// ------------------------------------------------------------------------
void Shader::set4f(const char* &name, float value1, float value2, float value3, float value4) const
{
    glUniform4f(glGetUniformLocation(program_id_, name), value1, value2, value3, value4);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}



