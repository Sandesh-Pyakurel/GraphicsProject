#include "window.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(int width, int height, const std::string& title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS X.

    m_window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    m_isClosed = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::HandleInput()
{
    if (glfwWindowShouldClose(m_window))
    {
        m_isClosed = true;
    }

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_isClosed = true;
    }
}

void Window::Update()
{
    // check and call events and sawp the buffers
    glfwSwapBuffers(m_window);
    glfwPollEvents(); 
}

bool Window::IsClosed()
{
   return m_isClosed; 
}

void Window::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);


}

Window::~Window()
{
    glfwTerminate();
}