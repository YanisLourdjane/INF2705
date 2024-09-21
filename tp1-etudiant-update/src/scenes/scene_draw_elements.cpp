#include "scene_draw_elements.h"

#include "vertices_data.h"

SceneDrawElements::SceneDrawElements(Resources& res)
: Scene(res),
    m_coloredSquareReduceVao(),
    m_coloredSquareReduceDraw(m_coloredSquareReduceVao, 6)
{
    // TODO
}

void SceneDrawElements::run(Window& w)
{
    // TODO
    m_coloredSquareReduceVao.bind();
    m_coloredSquareReduceDraw.draw();
}


