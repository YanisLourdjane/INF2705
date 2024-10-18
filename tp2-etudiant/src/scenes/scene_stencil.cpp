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

, m_playerTexture("../textures/player.png")
, m_playerHiddenTexture("../textures/player_hidden.png")
, m_enemyTexture("../textures/enemy.png")
, m_cloudTexture("../textures/cloud.png")
, m_bushTexture("../textures/bush.png")
{
    // TODO - specification des attributs
    
    m_squareVao.bind();
    m_squareBuffer.bind();
    m_squareIndicesBuffer.bind();
    m_squareVao.specifyAttribute(m_squareBuffer, 0, 3, 5, 0);
    m_squareVao.specifyAttribute(m_squareBuffer, 1, 2, 5, 3);
    m_squareVao.unbind();
    

    m_playerTexture.setFiltering(GL_LINEAR);
    m_playerTexture.setWrap(GL_CLAMP_TO_EDGE);

    m_playerHiddenTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_playerHiddenTexture.setFiltering(GL_LINEAR);

    m_enemyTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_enemyTexture.setFiltering(GL_LINEAR);

    m_cloudTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_cloudTexture.setFiltering(GL_LINEAR);

    m_bushTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_bushTexture.setFiltering(GL_LINEAR);
}

void SceneStencil::run(Window& w)
{
    glm::mat4 model, proj, view, mvp;

    const float SCREEN_SIZE_ORTHO = 6.0f;    
    proj = glm::ortho(-SCREEN_SIZE_ORTHO/2.0f, SCREEN_SIZE_ORTHO/2.0f, -SCREEN_SIZE_ORTHO/2.0f, SCREEN_SIZE_ORTHO/2.0f, -10.0f, 10.0f);
    view = glm::mat4(1);
    
    glm::mat4 projView = proj * view;

    // Clear the stencil buffer
    glDepthMask(GL_FALSE);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0x1); // Toujours passer et écrire le 1 dans le tampon de stencil
    glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );
    glDisable(GL_DEPTH_TEST);

    //1. Dessiner le buisson  afin de mettre des 1 dans le tampon de stencil aux endroits où le buisson est présent
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(3.0f, 3.0f, 1.0f));
    mvp = projView * model;
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_bushTexture.use();
    m_squareDraw.draw();

    // 2. Dessiner le joueur et les ennemis

    // 2.1. Dessiner la partie du joueur non cachée par le buisson
    glStencilFunc(GL_EQUAL, 0, 0x1);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    mvp = projView * model;
    // TODO: Utiliser le shader pour dessiner le joueur ici
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_playerTexture.use();
    m_squareDraw.draw();

    // 2.2. Dessiner la partie du joueur cachée par le buisson
    glStencilFunc(GL_EQUAL, 1, 0x1);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    mvp = projView * model;
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_playerHiddenTexture.use();
    m_squareDraw.draw();

    // 2.3. Dessiner l'ennemi caché partiellement par le buisson
    glStencilFunc(GL_EQUAL, 0, 0x1);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
    mvp = projView * model;
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_enemyTexture.use();
    m_squareDraw.draw();

    // 2.4. Dessiner l'ennemi completement caché par le buisson (il ne sera pas visible)
    glStencilFunc(GL_EQUAL, 0, 0x1);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mvp = projView * model;
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_enemyTexture.use();
    m_squareDraw.draw();



    // 3. Dessiner le nuage avec blending
    glStencilFunc(GL_ALWAYS, 1, 0x1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 1.0f));
    mvp = projView * model;

    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_cloudTexture.use();
    m_squareDraw.draw();

    // Réinitialiser le test de stencil  et le blending
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}



