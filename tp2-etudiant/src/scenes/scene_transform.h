#ifndef SCENE_TRANSFORM_H
#define SCENE_TRANSFORM_H

#include "scene.h"

#include <glm/glm.hpp>

#include "model.h"
#include "texture.h"

class SceneTransform : public Scene
{
public:
    SceneTransform(Resources& res, bool& isMouseMotionEnabled, bool& isThirdPerson, bool& isOrtho);
    ~SceneTransform();

    virtual void run(Window& w);
    
private:
    void updateInput(Window& w);

    glm::mat4 getCameraFirstPerson();
    glm::mat4 getCameraThirdPerson();
    
    glm::mat4 getProjectionMatrix(Window& w);
    glm::mat4 computeCarouselFrameModelMatrix();
    glm::mat4 computeCarouselPoleModelMatrix(int i);
    glm::mat4 computeCarouselHorseModelMatrix();
    
private:
    bool& m_isMouseMotionEnabled;
    bool& m_isThirdPerson;
    bool& m_isOrtho;

    glm::vec3 m_cameraPosition;
    glm::vec2 m_cameraOrientation;
    
    float m_carouselAngleRad;
    
    BufferObject m_groundBuffer;
    BufferObject m_groundIndicesBuffer;
    VertexArrayObject m_groundVao;
    DrawElementsCommand m_groundDraw;

    Model m_carouselFrame;
    Model m_carouselPole;
    Model m_carouselHorse;
    
    Texture2D m_groundTexture;
    Texture2D m_frameTexture;
    Texture2D m_poleTexture;
    Texture2D m_horseTexture;
};

#endif // SCENE_TRANSFORM_H
