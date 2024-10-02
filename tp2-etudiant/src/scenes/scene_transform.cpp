#include "scene_transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"

// TODO - coordonnées de texture
const GLfloat groundData[] = {
    -10.0f, 0.0f, -10.0f,  0.0f, 0.0f,
     10.0f, 0.0f, -10.0f,  3.0f, 0.0f,
    -10.0f, 0.0f,  10.0f,  0.0f, 3.0f,
     10.0f, 0.0f,  10.0f,  3.0f, 3.0f,
};

const GLubyte indexes[] = {
    2, 3, 0,
    3, 1, 0
};


SceneTransform::SceneTransform(Resources& res, bool& isMouseMotionEnabled, bool& isThirdPerson, bool& isOrtho)
: Scene(res)
, m_isMouseMotionEnabled(isMouseMotionEnabled)
, m_isThirdPerson(isThirdPerson)
, m_isOrtho(isOrtho)
, m_cameraPosition(0.0f, 1.0f, 5.0f)
, m_cameraOrientation(0.0f, 0.0f)
, m_carouselAngleRad(0.0f)

, m_groundBuffer(GL_ARRAY_BUFFER, sizeof(groundData), groundData, GL_STATIC_DRAW)
, m_groundIndicesBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW)
, m_groundVao()
, m_groundDraw(m_groundVao, 6)

{
    // TODO - spécifier les attributs
    m_groundVao.bind();
    m_groundBuffer.bind();
    m_groundIndicesBuffer.bind();
    m_groundVao.specifyAttribute(m_groundBuffer, 0, 3, 3, 0);
    m_groundVao.specifyAttribute(m_groundIndicesBuffer, 1, 3, 3, 0);
    m_groundVao.unbind();
    
    // TODO - init des textures
    glGenTextures(1, &m_groundTexture);
    glBindTexture(GL_TEXTURE_2D, m_groundTexture);

    //load la texture a partir de son path

    //Repetition horizontale et verticale de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glGenerateMipmap( GL_TEXTURE_2D );

    glBindTexture(GL_TEXTURE_2D, 0);
    
}

void SceneTransform::run(Window& w)
{
    // TODO - ajout des textures
    m_groundVao.bind();
    m_groundBuffer.bind();
    m_groundIndicesBuffer.bind();

    glBindTexture(GL_TEXTURE_2D, m_groundBuffer);

    glm::mat4 mvpTerrain = glm::mat4(1.0f);
    glm::translate(mvp, glm::vec3(0.0f, -0.1f, 0.0f));
    m_resources.model.use();
    glUniformMatrix4fv(m_resources.mvpLocationModel,  1, GL_FALSE, glm::value_ptr(mvpTerrain));

    m_groundDraw.draw();

    glBindTexture(GL_TEXTURE_2D, 0);
    m_groundVao.unbind();



    m_resources.model.use();
    
    updateInput(w);

    glm::mat4 model, proj, view, mvp;
    
    const float SCREEN_SIZE_ORTHO = 5.0f;
    
    proj = getProjectionMatrix(w);
    
    if (m_isThirdPerson)
        view = getCameraThirdPerson();
    else
        view = getCameraFirstPerson();
    
    glm::mat4 projView = proj * view;

    model = computeCarouselFrameModelMatrix();
    mvp = projView * model;
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    m_carouselFrame.draw();
    
    const int N_HORSES = 5;
    for (int i = 0; i < N_HORSES; i++)
    {
        mvp = projView * computeCarouselPoleModelMatrix(i);
        glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
        m_carouselPole.draw();
        
        mvp = mvp * computeCarouselHorseModelMatrix(i);
        glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
        m_carouselHorse.draw();
    }
    
    m_carouselAngleRad -= 0.01f;
    
    
    // TODO - dessin du sol
    
}

void SceneTransform::updateInput(Window& w)
{
    int x = 0, y = 0;
    if (m_isMouseMotionEnabled)
        w.getMouseMotion(x, y);
    m_cameraOrientation.y -= x * 0.01f;
    m_cameraOrientation.x -= y * 0.01f;

    glm::vec3 positionOffset = glm::vec3(0.0);
    const float SPEED = 0.1f;
    if (w.getKeyHold(Window::Key::W))
        positionOffset.z -= SPEED;
    if (w.getKeyHold(Window::Key::S))
        positionOffset.z += SPEED;
    if (w.getKeyHold(Window::Key::A))
        positionOffset.x -= SPEED;
    if (w.getKeyHold(Window::Key::D))
        positionOffset.x += SPEED;
        
    if (w.getKeyHold(Window::Key::Q))
        positionOffset.y -= SPEED;
    if (w.getKeyHold(Window::Key::E))
        positionOffset.y += SPEED;

    positionOffset = glm::rotate(glm::mat4(1.0f), m_cameraOrientation.y, glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(positionOffset, 1);
    m_cameraPosition += positionOffset;
}


