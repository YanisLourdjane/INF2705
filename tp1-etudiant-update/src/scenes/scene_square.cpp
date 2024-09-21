#include "scene_square.h"
#include <iostream>
using namespace std;
#include "vertices_data.h"

SceneSquare::SceneSquare(Resources& res)
: Scene(res),
    m_squareBuffer(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW),
    m_squareVao(),
    m_squareDraw(m_squareVao, 6)
{
        m_squareVao.specifyAttribute(m_squareBuffer, 0, 3, 3, 0);
}

void SceneSquare::run(Window& w)
{
    m_resources.basic.use();
    m_squareVao.bind();
    m_squareDraw.draw();
}

