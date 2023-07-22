#include <iostream>
#include <cmath>

#include <glad/glad.h>

#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"
#include "texture.hpp"
#include "transform.hpp"

#define WIDTH 800
#define HEIGHT 600

int main()
{
    Window window(WIDTH, HEIGHT, "glfw window");

    Shader shader("./res/basicShader");

    // input to shader.
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec2(0.0, 0.0)),
        Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 0.0)),
        Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.5, 1.0)),
    };

    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    Texture texture("./res/bricks.png");
    Transform transform;

    shader.setInt("texture0", 0);
    shader.setInt("texture1", 1);

    float counter = 0.0f;

   // render loop
    while (!window.IsClosed())
    {
        window.Clear(0.2f, 0.3f, 0.0f, 1.0f);
        // input
        window.HandleInput();

        // rendering commands here

        float sinCounter = sinf(counter);
        float cosCounter = cosf(counter);

        transform.GetPos()->x = sinCounter;
        transform.GetPos()->z = cosCounter;
        transform.GetRot()->x = counter * 5;
        transform.GetRot()->y = counter * 5;
        transform.GetRot()->z = counter * 5;
        transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));

        
        // using the created program.
        shader.Bind();
        shader.Update(transform);

        texture.Bind(0);

        mesh.Draw(); 

        window.Update();

        counter += 0.005f;
    }
}