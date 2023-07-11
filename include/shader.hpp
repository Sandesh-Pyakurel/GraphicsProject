#ifndef SHADER_H
#define SHADER_H    

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader(const std::string& fileName);

    void Bind();
    void Update();

    virtual ~Shader();

    // Utility uniform functions.
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float r, float g, float b) const;


private:
    static const unsigned int NUM_SHADERS = 2;

    std::string LoadShader(const std::string& fileName);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, unsigned int type);

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];

};

#endif