#include <iostream>
#include <cmath>

#include <glad/glad.h>

#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"

#define WIDTH 800
#define HEIGHT 600

int main()
{
    Window window(WIDTH, HEIGHT, "glfw window");

    Shader shader("./res/basicShader");

    // input to shader.
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec3(1.0, 0.0, 0.0)),
        Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec3(0.0, 1.0, 0.0)),
        Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec3(0.0, 0.0, 1.0)),
    };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

   // render loop
    while (!window.IsClosed())
    {
        window.Clear(0.2f, 0.3f, 0.0f, 1.0f);
        // input
        window.HandleInput();

        // rendering commands here
        
        // using the created program.
        shader.Bind();
        shader.Update();

        // uupdate the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        shader.setFloat("ourColor", 0.0f, greenValue, 0.0f);

        mesh.Draw(); 

        window.Update();
    }
}