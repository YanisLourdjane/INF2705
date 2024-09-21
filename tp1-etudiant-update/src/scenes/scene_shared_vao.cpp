#include "scene_shared_vao.h"

#include "vertices_data.h"

SceneSharedVao::SceneSharedVao(Resources &res)
    : Scene(res),
      m_sharedVao(),
      m_coloredTriangleSharedDraw(m_sharedVao, 3),
      m_coloredSquareSharedDraw(m_sharedVao, 4)
{
    // TODO: create the shared VAO
    m_sharedVao.bind();
    
}

void SceneSharedVao::run(Window &w)
{
    // Exceptionnellement, cette méthode n'est pas utilisée
}

void SceneSharedVao::runTriangle()
{
    // TODO: draw the triangle
    glClear(GL_COLOR_BUFFER_BIT);
    m_sharedVao.bind();
    m_coloredTriangleSharedDraw.draw();
    m_sharedVao.unbind();
}

void SceneSharedVao::runSquare()
{
    // TODO
    m_sharedVao.bind();
    m_coloredSquareSharedDraw.draw();
    m_sharedVao.unbind();

}
