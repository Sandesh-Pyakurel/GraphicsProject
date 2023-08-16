#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord,const glm::vec3& normal)
    {
        this->pos = pos;
        this->color = color;
        this->texCoord = texCoord;
        this->normal= normal;
    }

    inline glm::vec3* GetPos(){ return &pos; }
    inline glm::vec3* GetColor(){ return &color; }
    inline glm::vec2* GetTexCoord(){ return &texCoord; }
    inline glm::vec3* GetNormal(){ return &normal; }

private:
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    glm::vec3 normal;
};


enum MeshBufferPosition
{
    POSITION_VB,
    COLOR_VB,
    TEXCOORD_VB,
    NORMAL_VB,

    INDEX_VB
};

class IndexedModel
{
public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<unsigned int> indices;
    
    void CalcNormals();
};


class Mesh
{
public:
    Mesh(const std::string& filename);
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

    void Draw();

    virtual ~Mesh();

private:
    static const unsigned int NUM_BUFFERS = 5;

    Mesh(const Mesh& other);
    void operator=(const Mesh& other);

    void InitMesh(const IndexedModel& model);

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_numIndices;
};

#endif