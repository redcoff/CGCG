#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/type_ptr.hpp>

#include <cstdlib>
#include <fstream>

#include "Camera.h"
#include "ParticleSystem.h"
#include "Utils.h"

GLFWwindow* window;
static Camera camera;
int mViewProjUniform;

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

    ParticleSystem::Draw(glm::identity<glm::mat4>());
    //glDrawArrays(GL_TRIANGLES, 0, 3);


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

    /*
    float positions[] = {
        -0.5f, -0.5, 0.f, 1.f, 1.f, 0.f,
        0.0f, 0.5f, 0.f, 1.f, 1.f, 0.f,
        0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f
    };
 
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), positions, GL_STATIC_DRAW);
     
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
*/

    Utils::ShaderProgramSource source = Utils::ParseShader("res/shaders/Basic.shader");
	unsigned int shader = Utils::CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    mViewProjUniform = glGetUniformLocation(shader, "mViewProj");
    glPointSize(8.f);

    ParticleSystem::Emit();
    loop();

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}