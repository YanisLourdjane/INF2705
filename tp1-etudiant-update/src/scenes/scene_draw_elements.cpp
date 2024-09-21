#include "scene_draw_elements.h"

#include "vertices_data.h"

SceneDrawElements::SceneDrawElements(Resources& res)
: Scene(res),
    m_coloredSquareReduceVao(),
    m_coloredSquareReduceDraw(m_coloredSquareReduceVao, 6)
{
    m_coloredSquareReduceVao.bind();
    m_resources.coloredSquareReduceBuffer.bind();
    m_resources.coloredSquareReduceIndicesBuffer.bind();
    m_coloredSquareReduceVao.specifyAttribute(m_resources.coloredSquareReduceBuffer, 0, 3, 6, 0);
    m_coloredSquareReduceVao.specifyAttribute(m_resources.coloredSquareReduceBuffer, 1, 3, 6, 3);
    m_resources.coloredSquareReduceIndicesBuffer.bind();
}

void SceneDrawElements::run(Window& w)
{
    m_resources.color.use();
    m_coloredSquareReduceVao.bind();
    m_coloredSquareReduceDraw.draw();
}


