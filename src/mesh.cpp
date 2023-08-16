#include "mesh.hpp"
#include <vector>


void IndexedModel::CalcNormals()
{
    for(unsigned int i = 0; i < indices.size(); i += 3)
    {
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];

        glm::vec3 v1 = positions[i1] - positions[i0];
        glm::vec3 v2 = positions[i2] - positions[i0];
        
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
            
        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }
    
    for(unsigned int i = 0; i < positions.size(); i++)
        normals[i] = glm::normalize(normals[i]);
}


void Mesh::InitMesh(const IndexedModel& model)
{
    m_numIndices = model.indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.colors[0]) * model.colors.size(), &model.colors[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

    // to unbind the vertex array object.
    glBindVertexArray(0);

}


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;

    for (unsigned int i = 0; i < numVertices; i++)
    {
        model.positions.push_back(*vertices[i].GetPos());
        model.colors.push_back(*vertices[i].GetColor());
        model.texCoords.push_back(*vertices[i].GetTexCoord());
        model.normals.push_back(*vertices[i].GetNormal());
    }

    for (unsigned int i = 0; i < numIndices; i++)
    {
        model.indices.push_back(indices[i]);
    }

    InitMesh(model);

}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
    glBindVertexArray(m_vertexArrayObject);

    // glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
    glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

    glBindVertexArray(0);
}