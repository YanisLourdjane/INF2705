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
    // TODO
        m_squareVao.specifyAttribute(m_squareBuffer, 0, 3, 3 * sizeof(float), 0);
        cout << "Square created" << endl;

        //Unbind
        // m_squareVao.unbind();
}

void SceneSquare::run(Window& w)
{
    // TODO
    m_resources.basic.use();
    m_squareVao.bind();
    m_squareDraw.draw();
}

