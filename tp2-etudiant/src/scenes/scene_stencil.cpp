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
    
    // TODO - init des textures

    m_playerTexture.setWrap(GL_REPEAT);
    m_playerTexture.enableMipmap();

    m_playerHiddenTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_playerHiddenTexture.setFiltering(GL_LINEAR);

    m_enemyTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_enemyTexture.setFiltering(GL_LINEAR);

    m_cloudTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_cloudTexture.setFiltering(GL_NEAREST);

    m_bushTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_bushTexture.setFiltering(GL_NEAREST);
}

void SceneStencil::run(Window& w)
{
        glm::mat4 model, proj, view, mvp;

    const float SCREEN_SIZE_ORTHO = 6.0f;    
    proj = glm::ortho(-SCREEN_SIZE_ORTHO/2.0f, SCREEN_SIZE_ORTHO/2.0f, -SCREEN_SIZE_ORTHO/2.0f, SCREEN_SIZE_ORTHO/2.0f, -10.0f, 10.0f);
    view = glm::mat4(1);
    
    glm::mat4 projView = proj * view;

    // Clear the stencil buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // 1. Dessiner le buisson et écrire dans le tampon de stencil
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0x1);  // Autoriser l'écriture sur le bit 0
    glStencilFunc(GL_ALWAYS, 1, 0x1); // Toujours passer et écrire le 1 dans le tampon de stencil

    // Dessiner le buisson
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(3.0f, 3.0f, 1.0f));
    mvp = projView * model;
    // TODO: Utiliser le shader pour dessiner le buisson ici
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_bushTexture.use();
    m_squareDraw.draw();

    // 2. Désactiver l'écriture dans le tampon de stencil
    glStencilMask(0x0); // Désactiver l'écriture

    // 3. Dessiner le joueur
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    mvp = projView * model;
    // TODO: Utiliser le shader pour dessiner le joueur ici
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_playerTexture.use();
    m_squareDraw.draw();

    // 4. Modifier le test de stencil pour cacher les ennemis derrière le buisson
    glStencilFunc(GL_EQUAL, 1, 0x1); // Passer si le tampon de stencil est égal à 1 (buisson présent)

    // Dessiner le premier ennemi (partiellement caché)
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
    mvp = projView * model;
    // TODO: Utiliser le shader pour dessiner l'ennemi ici
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_enemyTexture.use();
    m_squareDraw.draw();

    // Dessiner le deuxième ennemi (complètement caché)
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mvp = projView * model;
    // TODO: Utiliser le shader pour dessiner l'ennemi ici
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_squareDraw.draw();

    // 5. Dessiner le nuage avec blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 1.0f));
    mvp = projView * model;
    // TODO: Utiliser le shader pour dessiner le nuage ici
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_cloudTexture.use();
    m_squareDraw.draw();

    // Réinitialiser le test de stencil
    glStencilMask(0xFF);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);
}



