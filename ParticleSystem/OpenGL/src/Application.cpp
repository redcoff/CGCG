#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/type_ptr.hpp>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Camera.h"
#include "ParticleSystem.h"
#

GLFWwindow* window;
static Camera camera;
int mViewProjUniform;

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

static ShaderProgramSource ParseShader(const std::string& filepath)
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

static unsigned int CompileShader(unsigned int type, const std::string& source)
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

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

bool createWindow()

{
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

bool initializeOpenGL()
{
    // Initialize the GLFW library 
    if (!glfwInit())
        return false;

    // Create the window
    if (!createWindow())
        return false;
    
    // Initialize the GLEW library
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glewError));

        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    return true;
}

void draw()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glUniformMatrix4fv(mViewProjUniform, 1, GL_FALSE, glm::value_ptr(camera.GetViewProjection()));

    glDrawArrays(GL_TRIANGLES, 0, 3);


    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

void update(double deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W))
    {
        camera.Rotate(0.f, .005f);
    }
	if (glfwGetKey(window, GLFW_KEY_S))
    {
        camera.Rotate(0.f, -.005f);
    }
    if (glfwGetKey(window, GLFW_KEY_A))
    {
        camera.Rotate(.005f, 0.f);
    }
    if (glfwGetKey(window, GLFW_KEY_D))
    {
        camera.Rotate(-.005f, 0.f);
    }

    ParticleSystem::Emit();
    ParticleSystem::Update(deltaTime);
}

void loop()
{
    static double prevTime = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();
        double dt = time - prevTime;
        prevTime = time;

        update(dt);
        draw();
    }
}


int main(void)
{
    initializeOpenGL();

    float positions[] = {
        -0.5f, -0.5, 1.f, 0.f, 0.f,
        0.0f, 0.5f, 0.f, 1.f, 0.f,
        0.5f, -0.5f, 0.f, 0.f, 1.f
    };
 
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), positions, GL_STATIC_DRAW);
     
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 2));

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    mViewProjUniform = glGetUniformLocation(shader, "mViewProj");

    loop();

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}