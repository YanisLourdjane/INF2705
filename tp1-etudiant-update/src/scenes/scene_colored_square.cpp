#include "scene_colored_square.h"
#include <iostream>
using namespace std;
#include "vertices_data.h"

SceneColoredSquare::SceneColoredSquare(Resources &res)
    : Scene(res),
      m_coloredSquareBuffer(GL_ARRAY_BUFFER, sizeof(colorSquareVertices), colorSquareVertices, GL_STATIC_DRAW),
      m_coloredSquareVao(),
      m_coloredSquareDraw(m_coloredSquareVao, 6)
{
    m_coloredSquareVao.bind();
    m_coloredSquareBuffer.bind();
    m_coloredSquareVao.specifyAttribute(m_coloredSquareBuffer, 0, 3, 6, 0);
    m_coloredSquareVao.specifyAttribute(m_coloredSquareBuffer, 1, 3, 6, 3);
}

void SceneColoredSquare::run(Window &w)
{
    m_resources.color.use();
    // m_coloredSquareVao.bind();
    m_coloredSquareDraw.draw();
}
