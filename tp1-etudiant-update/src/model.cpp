#include "model.h"
#include "obj_loader.h"

#include "model.h"
#include "obj_loader.h"

Model::Model(const char* path)
    : m_vbo(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW)
    , m_ebo(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW)
    , m_vao()
    , m_drawcall(m_vao, 0, GL_UNSIGNED_INT)  // Default initialize it with valid params
{
    // Initialize the vectors to store vertex data and indices
    std::vector<GLfloat> vertexData;
    std::vector<GLuint> indices;

    // Load vertex and index data from the .obj file
    loadObj(path, vertexData, indices);

    // Now that we have vertexData and indices, update the VBO and EBO
    m_vbo.update(vertexData.size() * sizeof(GLfloat), vertexData.data());
    m_ebo.update(indices.size() * sizeof(GLuint), indices.data());

    // Initialize and bind the Vertex Array Object (VAO)
    m_vao.bind();

    // Bind the Vertex Buffer Object (VBO) and Element Buffer Object (EBO)
    m_vbo.bind();
    m_ebo.bind();

    // Define the vertex attribute pointer

    m_vao.specifyAttribute(m_vbo, 0, 3, 0, 0);

    // Use a custom method to set the count later
    m_drawcall.setCount(indices.size());
}



void Model::loadObj(const char* path, std::vector<GLfloat>& vertexData, std::vector<GLuint>& indices)
{
    objl::Loader loader;
    bool loadout = loader.LoadFile(path);
    if (!loadout)
    {
        std::cout << "Unable to load model " << path << std::endl;
        return;
    }

    for (size_t i = 0; i < loader.LoadedVertices.size(); i++)
    {
        objl::Vector3 p = loader.LoadedVertices[i].Position;
        vertexData.push_back(p.X);
        vertexData.push_back(p.Y);
        vertexData.push_back(p.Z);
    }
    indices = loader.LoadedIndices;
}

void Model::draw()
{
    m_drawcall.draw();
}