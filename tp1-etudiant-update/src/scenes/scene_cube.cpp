#include "scene_cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vertices_data.h"

SceneCube::SceneCube(Resources &res)
    : Scene(res),
      m_cubeBuffer(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW),
      m_cubeVao(),
      m_cubeDraw(m_cubeVao, 36),
      m_rotationAngleDegree(0.0f)
{
    // TODO
    m_cubeVao.specifyAttribute(m_cubeBuffer, 0, 3, 6 * sizeof(GLfloat), 0);
    m_cubeVao.specifyAttribute(m_cubeBuffer, 1, 3, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));
}

void SceneCube::run(Window &w)
{
    m_rotationAngleDegree += 0.5f;
    // TODO
    m_cubeVao.bind();
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationAngleDegree), glm::vec3(0.0f, 1.0f, 0.0f));
    // res.m_programs[0].setUniform("model", model);
    m_cubeDraw.draw();
    m_cubeVao.unbind();
}
