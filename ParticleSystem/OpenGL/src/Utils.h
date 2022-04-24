#pragma once
#include <string>

namespace Utils
{
    enum ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

	ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};

