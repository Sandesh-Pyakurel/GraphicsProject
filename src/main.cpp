#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include "stb/stb_image.h"

#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "camera.hpp"

#define WIDTH 800
#define HEIGHT 600

int main()
{
    Window window(WIDTH, HEIGHT, "glfw window");

    Shader shader("./res/basicShader");

    Model ourModel("./res/nanosuit/nanosuit.obj");


    Camera camera(glm::vec3(0.0f, 0.0f, 40.0f));

       // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // for using more texture in same mesh.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float counter = 0.0f;

   // render loop
    while (!window.IsClosed())
    {
        window.CalcDeltaTime();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // input
        window.HandleInput(camera);

        // rendering commands here

        
        // using the created program.
        shader.Bind();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setMat4("model", model);

        // shader.Update(transform);
        ourModel.Draw(shader);

        window.Update();
    }
}