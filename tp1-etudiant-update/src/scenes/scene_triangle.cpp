#include "scene_triangle.h"
#include <iostream>
using namespace std;
#include "vertices_data.h"

SceneTriangle::SceneTriangle(Resources &res)
    : Scene(res),
      m_triangleBuffer(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW),
      m_triangleVao(),
      m_triangleDraw(m_triangleVao, 3)
{
    // TODO
    m_triangleVao.specifyAttribute(m_triangleBuffer, 0, 3, 3 * sizeof(float), 0);
    cout << "Triangle created" << endl;
}

void SceneTriangle::run(Window &w)
{
    // TODO
    m_resources.basic.use();
    m_triangleVao.bind();
    m_triangleDraw.draw();
}
