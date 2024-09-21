#include "scene_transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

SceneTransform::SceneTransform(Resources& res, bool& isMouseMotionEnabled, bool& isThirdPerson, bool& isOrtho)
: Scene(res),
    m_isMouseMotionEnabled(isMouseMotionEnabled),
    m_isThirdPerson(isThirdPerson),
    m_isOrtho(isOrtho),
    m_cameraPosition(0.0f, 0.0f, 3.0f),
    m_cameraOrientation(0.0f, 0.0f),
    m_carouselAngleRad(0.0f),
    m_carouselFrame("../models/carousel_frame.obj"),
    m_carouselPole("../models/carousel_pole.obj"),
    m_carouselHorse("../models/carousel_horse.obj")
{
    // TODO
}

void SceneTransform::run(Window& w)
{
    updateInput(w);

    // TODO
    const float SCREEN_SIZE_ORTHO = 5.0f;
    
    float carouselHorseTranslation = sin(m_carouselAngleRad * 2.0f) / 6.0f;
    const int N_HORSES = 5;
    for (int i = 0; i < N_HORSES; i++)
    {
        //TODO	
	}
    m_carouselAngleRad -= 0.01f;    
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


glm::mat4 SceneTransform::getCameraFirstPerson()
{   
    // TODO
}


glm::mat4 SceneTransform::getCameraThirdPerson()
{
    // TODO
}




