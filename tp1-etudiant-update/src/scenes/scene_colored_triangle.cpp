#include "scene_colored_triangle.h"
#include <iostream>
using namespace std;
#include "vertices_data.h"

SceneColoredTriangle::SceneColoredTriangle(Resources& res)
: Scene(res),
    m_coloredTriangleVao(),
    m_coloredTriangleDraw(m_coloredTriangleVao, 3)
{
    m_coloredTriangleVao.bind();
    m_resources.coloredTriangleBuffer.bind();
    m_coloredTriangleVao.specifyAttribute(m_resources.coloredTriangleBuffer, 0, 3, 6, 0);
    m_coloredTriangleVao.specifyAttribute(m_resources.coloredTriangleBuffer, 1, 3, 6, 3);
}

void SceneColoredTriangle::run(Window& w)
{
    m_resources.color.use();
    m_coloredTriangleDraw.draw();
    
}

