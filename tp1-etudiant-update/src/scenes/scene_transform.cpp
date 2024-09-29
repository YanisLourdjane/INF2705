#include "scene_transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


SceneTransform::SceneTransform(Resources& res, bool& isMouseMotionEnabled, bool& isThirdPerson, bool& isOrtho)
: Scene(res),
    m_isMouseMotionEnabled(isMouseMotionEnabled),
    m_isThirdPerson(isThirdPerson),
    m_isOrtho(isOrtho),
    m_cameraPosition(0.0f, 0.0f, 0.0f),
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
    const float SCREEN_SIZE_ORTHO = 5.0f;

    // TODO
    //v est configuree dans getCameraThirdPerson et getCameraFirstPerson
    
    glm::mat4 p;
    

    if (m_isOrtho){
        p = glm::ortho(-SCREEN_SIZE_ORTHO, SCREEN_SIZE_ORTHO, -SCREEN_SIZE_ORTHO, SCREEN_SIZE_ORTHO, 0.1f, 100.0f);
    }else{
        float aspectRatio = static_cast<float>(w.getWidth())/static_cast<float>(w.getHeight());
        p = glm::perspective(glm::radians(70.0f), aspectRatio, 0.1f, 100.0f);
    }


    glm::mat4 v = m_isThirdPerson ? getCameraThirdPerson() : getCameraFirstPerson();
    
    
    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));

    glm::mat4 mvpFrame = p*v*m;
    m_resources.transformSolidColor.use();
    glUniformMatrix4fv(m_resources.mvpLocationTransformSolidColor, 1, GL_FALSE, glm::value_ptr(mvpFrame));
    glUniform3f(m_resources.colorLocationTransformSolidColor, 0.7f, 0.0f, 0.0f);
    
    
    m_carouselFrame.draw();


    glm::mat4 rotationCarousel = glm::rotate(glm::mat4(1.0f), m_carouselAngleRad, glm::vec3(0.0f, 1.0f, 0.0f));

    float carouselHorseTranslation = sin(m_carouselAngleRad * 2.0f) / 6.0f;
    const int N_HORSES = 5;

    for (int i = 0; i < N_HORSES; i++) {
        glm::mat4 modelPoleCheval = glm::mat4(1.0f);

        modelPoleCheval = glm::translate(modelPoleCheval, glm::vec3(0.0f, 1.0f, 0.0f));

        float angle = (2.0f * glm::pi<float>() / N_HORSES) * i;
        modelPoleCheval = glm::rotate(modelPoleCheval, angle, glm::vec3(0.0f, 1.0f, 0.0f));

        modelPoleCheval = glm::translate(modelPoleCheval, glm::vec3(1.7f, 0.0f, 0.0f));

        modelPoleCheval = rotationCarousel * modelPoleCheval;

        float horseVerticalTranslation = (i % 2 == 0) ? carouselHorseTranslation : -carouselHorseTranslation;
        glm::mat4 horse_translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, horseVerticalTranslation, 0.0f));

        glm::mat4 mvpPole = p * v * modelPoleCheval;
        m_resources.transformSolidColor.use();
        glUniformMatrix4fv(m_resources.mvpLocationTransformSolidColor, 1, GL_FALSE, glm::value_ptr(mvpPole));
        glUniform3f(m_resources.colorLocationTransformSolidColor, 0.0f, 0.7f, 0.0f);
        m_carouselPole.draw();

        glm::mat4 mvpCheval = p * v * modelPoleCheval * horse_translation;
        m_resources.transformSolidColor.use();
        glUniformMatrix4fv(m_resources.mvpLocationTransformSolidColor, 1, GL_FALSE, glm::value_ptr(mvpCheval));
        glUniform3f(m_resources.colorLocationTransformSolidColor, 0.0f, 0.0f, 0.7f);
        m_carouselHorse.draw();
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
    glm::mat4 v = glm::mat4(1.0f);
    //L'ordre est inverse en raison dont la multiplication entre une
    //matrice et un vecteur est appliquee
    v = glm::translate(v, -m_cameraPosition);
    v = glm::rotate(v, m_cameraOrientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    v = glm::rotate(v, m_cameraOrientation.x, glm::vec3(1.0f, 0.0f, 0.0f));

    return v;
}


glm::mat4 SceneTransform::getCameraThirdPerson()
{
    float rayon = 6.0f;
    float azimut = glm::pi<float>() / 2.0f;
    float polaire = glm::pi<float>() / 2.0f;

    float x = rayon * cos(azimut) * sin(polaire);
    float y = rayon * cos(polaire);
    float z = rayon * sin(azimut) * sin(polaire);

    glm::mat4 v = glm::mat4(1.0f);

    glm::vec3 cameraPosition = glm::vec3(x, y, z);
    glm::vec3 ptVise = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

    v = glm::lookAt(cameraPosition, ptVise, upVec);
    return v;
}