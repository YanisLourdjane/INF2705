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

, m_carouselFrame("../models/carousel_frame.obj")
, m_carouselPole("../models/carousel_pole.obj")
, m_carouselHorse("../models/carousel_horse.obj")

, m_groundTexture("../textures/grassSeamless.jpg")
, m_frameTexture("../textures/carousel_frame.png")
, m_poleTexture("../textures/carousel_pole.png")
, m_horseTexture("../textures/carousel_horsesAtlas.png")
{
    m_groundVao.bind();
    m_groundBuffer.bind();
    m_groundIndicesBuffer.bind();
    m_groundVao.specifyAttribute(m_groundBuffer, 0, 3, 5, 0);
    m_groundVao.specifyAttribute(m_groundBuffer, 1, 2, 5, 3);
    m_groundVao.unbind();
    

    m_groundTexture.setWrap(GL_REPEAT);
    m_groundTexture.enableMipmap();

    m_frameTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_frameTexture.setFiltering(GL_LINEAR);

    m_poleTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_poleTexture.setFiltering(GL_LINEAR);

    m_horseTexture.setWrap(GL_CLAMP_TO_EDGE);
    m_horseTexture.setFiltering(GL_NEAREST);
}

void SceneTransform::run(Window& w)
{
    m_resources.model.use();
    
    glUniform1i(m_resources.model.getUniformLoc("myTexture"), 0);
    
    updateInput(w);

    glm::mat4 model, proj, view, mvp;
    
        
    proj = getProjectionMatrix(w);
    
    if (m_isThirdPerson)
        view = getCameraThirdPerson();
    else
        view = getCameraFirstPerson();
    
    glm::mat4 projView = proj * view;

    model = computeCarouselFrameModelMatrix();
    mvp = projView * model;
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
    
    m_frameTexture.use();
    m_carouselFrame.draw();

    m_resources.horse.use();
    glUniform1i(m_resources.model.getUniformLoc("myTexture"), 0);

    
    const int N_HORSES = 5;
    for (int i = 0; i < N_HORSES; i++)
    {
        mvp = projView * computeCarouselPoleModelMatrix(i);
        glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
        m_poleTexture.use();
        m_carouselPole.draw();
        
        mvp = mvp * computeCarouselHorseModelMatrix(i);
        glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &mvp[0][0]);
        glUniform1i(m_resources.textureIndexLocationHorse, i);
        m_horseTexture.use();
        m_carouselHorse.draw();
    }
    
    m_carouselAngleRad -= 0.01f;
    
    
    m_resources.model.use();
    glm::mat4 groundModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));
    groundModel = projView * groundModel;
    glUniformMatrix4fv(m_resources.mvpLocationModel, 1, GL_FALSE, &groundModel[0][0]);
    m_groundTexture.use();
    m_groundDraw.draw();

    glBindTexture(GL_TEXTURE_2D, 0);
    m_groundVao.unbind();
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


