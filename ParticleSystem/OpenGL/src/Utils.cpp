#include "Utils.h"

#include <iostream>
#include <ostream>
#include <GL/glew.h>
#include <sstream>
#include <fstream>

Utils::ShaderProgramSource Utils::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];

    ShaderType type = NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << std::endl;
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Utils::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Error - Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "shader") << " shader!!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Utils::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program, vs);
    glDeleteShader(vs);
    glDetachShader(program, fs);
    glDeleteShader(fs);

    return program;
}
