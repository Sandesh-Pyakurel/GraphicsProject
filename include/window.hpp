#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Window
{
public:
    Window(int width, int height, const std::string& title);

    void Update();
    void HandleInput();
    bool IsClosed();
    void Clear(float r, float g, float b, float a);

    virtual ~Window();

private:
    GLFWwindow* m_window;

    bool m_isClosed;
};

#endif