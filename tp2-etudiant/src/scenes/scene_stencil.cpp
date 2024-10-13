#include "scene_stencil.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"

const GLfloat squareData[] = {
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
};

const GLubyte indexes[] = {
    0, 1, 2,
    1, 3, 2
};


SceneStencil::SceneStencil(Resources& res)
: Scene(res)
, m_cameraPosition(0.0f, 0.0f)
, m_squareBuffer(GL_ARRAY_BUFFER, sizeof(squareData), squareData, GL_STATIC_DRAW)
, m_squareIndicesBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW)
, m_squareVao()
, m_squareDraw(m_squareVao, 6)
, m_playerTexture("../textures/player.jpg")
, m_playerHiddenTexture("../textures/player_hidden.jpg")
, m_enemyTexture("../textures/enemy.jpg")
, m_cloudTexture("../textures/cloud.jpg")
, m_bushTexture("../textures/bush.jpg")
{
    // TODO - specification des attributs
    
    m_squareVao.bind();
    m_squareIndicesBuffer.bind();
    m_squareVao.unbind();
    
    // TODO - init des textures
}

void SceneStencil::run(Window& w)
{
    glm::mat4 model, proj, view, mvp;
    
    const float SCREEN_SIZE_ORTHO = 6.0f;    
    proj = glm::ortho(-SCREEN_SIZE_ORTHO/2.0f, SCREEN_SIZE_ORTHO/2.0f, -SCREEN_SIZE_ORTHO/2.0f, SCREEN_SIZE_ORTHO/2.0f, -10.0f, 10.0f);
    view = glm::mat4(1);
    
    glm::mat4 projView = proj * view;
    
    // TODO - dessiner la scène
}



