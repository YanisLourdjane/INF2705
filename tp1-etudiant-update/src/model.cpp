#include "model.h"
#include "obj_loader.h"

Model::Model(const char* path): m_drawcall(m_vao, 0, GL_UNSIGNED_INT)
{
	// TODO: A COMPRENDRE
	std::vector<GLfloat> vertexData;
	std::vector<GLuint> indices;
	loadObj(path, vertexData, indices);

	m_vbo = BufferObject(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);
	m_ebo = BufferObject(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	m_vao = VertexArrayObject();
	m_vao.bind();
	m_vbo.bind();
	m_ebo.bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

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
	// TODO
	m_vao.bind();
	m_drawcall.draw();
}

