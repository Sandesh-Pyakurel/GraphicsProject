#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec3& color)
    {
        this->pos = pos;
        this->color = color;
    }

    inline glm::vec3* GetPos(){ return &pos; }
    inline glm::vec3* GetColor(){ return &color; }

private:
    glm::vec3 pos;
    glm::vec3 color;
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
        TEXCOORD_VB,

        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif