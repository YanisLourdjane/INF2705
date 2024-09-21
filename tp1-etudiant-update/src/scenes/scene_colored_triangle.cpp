#include "scene_colored_triangle.h"
#include <iostream>
using namespace std;
#include "vertices_data.h"

SceneColoredTriangle::SceneColoredTriangle(Resources& res)
: Scene(res),
    m_coloredTriangleVao(),
    m_coloredTriangleDraw(m_coloredTriangleVao, 3)
{
    // TODO
    m_coloredTriangleVao.bind();
    m_resources.coloredTriangleBuffer.bind();
    m_coloredTriangleVao.specifyAttribute(m_resources.coloredTriangleBuffer, 0, 3, 6 * sizeof(float), 0);
    m_coloredTriangleVao.specifyAttribute(m_resources.coloredTriangleBuffer, 1, 3, 6 * sizeof(float), 3 * sizeof(float));
    cout << "Col triangle created" << endl;
}

void SceneColoredTriangle::run(Window& w)
{
    // TODO
    m_resources.color.use();
    // m_coloredTriangleVao.bind();
    m_coloredTriangleDraw.draw();
    
}

