#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord)
    {
        this->pos = pos;
        this->color = color;
        this->texCoord = texCoord;
    }

    inline glm::vec3* GetPos(){ return &pos; }
    inline glm::vec3* GetColor(){ return &color; }
    inline glm::vec2* GetTexCoord(){ return &texCoord; }

private:
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
};

class Mesh
{
public:
    Mesh(Vertex* vertices, unsigned int numVertices);

    void Draw();

    virtual ~Mesh();

private:
    Mesh(const Mesh& other);
    void operator=(const Mesh& other);

    enum
    {
        POSITION_VB,
        COLOR_VB,
        TEXCOORD_VB,

        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif