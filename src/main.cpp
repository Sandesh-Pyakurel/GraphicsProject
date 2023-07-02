#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS X.

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // creating shader.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // checking for error.
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error::Shader::Vertex::Compilation_failed\n" << infoLog << std::endl;
    }
    // creating shader.
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // checking for error.
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error::Shader::Fragment::Compilation_failed\n" << infoLog << std::endl;
    }

    // shader program.
    unsigned int shaderPorgram;
    shaderPorgram = glCreateProgram();
    glAttachShader(shaderPorgram, vertexShader);
    glAttachShader(shaderPorgram, fragmentShader);
    glLinkProgram(shaderPorgram);

    // checking for error.
    glGetProgramiv(shaderPorgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderPorgram, 512, NULL, infoLog);
    }

    // deleting shader objects once linked them into the program object.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // input to shader.
    float vertiecs[] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,  
         0.0f,  0.5f,  0.0f,  
         // second triangle
         1.0f,  0.5f,  0.0f,  
         0.0f,  0.75f,  0.0f,  
         0.5f,  0.5f,  0.0f,  
    };

    // using vertex array objects(VAO).
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    // initalizing array buffer in gpu.
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertiecs), vertiecs, GL_STATIC_DRAW);

 
    // telling opengl how to interpret vertex data.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // input
        processInput(window);

        // rendering commands here
        
        // using the created program.
        glUseProgram(shaderPorgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // check and call events and sawp the buffers
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    // de-allocating resources.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderPorgram);

    glfwTerminate();

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}