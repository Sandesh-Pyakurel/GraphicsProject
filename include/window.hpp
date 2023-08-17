#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "camera.hpp"

class Window
{
public:
    Window(int width, int height, const std::string& title);

    void Update();
    void HandleInput(Camera camera);
    bool IsClosed();
    void Clear(float r, float g, float b, float a);
    void CalcDeltaTime();

    virtual ~Window();

private:
    GLFWwindow* m_window;

    bool m_isClosed;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};

#endif