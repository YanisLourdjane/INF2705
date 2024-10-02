#ifndef SCENE_STENCIL_H
#define SCENE_STENCIL_H

#include "scene.h"

#include <glm/glm.hpp>

#include "model.h"
#include "texture.h"

class SceneStencil : public Scene
{
public:
    SceneStencil(Resources& res);

    virtual void run(Window& w);
    
    
private:
    void updateInput(Window& w);
    
private:
    glm::vec2 m_cameraPosition;

    BufferObject m_squareBuffer;
    BufferObject m_squareIndicesBuffer;
    VertexArrayObject m_squareVao;
    DrawElementsCommand m_squareDraw;
    
    Texture2D m_playerTexture;
    Texture2D m_playerHiddenTexture;
    Texture2D m_enemyTexture;
    Texture2D m_cloudTexture;
    Texture2D m_bushTexture;
};

#endif // SCENE_STENCIL_H

