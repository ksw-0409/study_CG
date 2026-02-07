#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <glm/glm.hpp>

#include<iostream>
#include "Program.h"
#include "texture2D.h"

class SpriteRenderer
{
public:
    SpriteRenderer(Program& shader);
    ~SpriteRenderer();
    void initRenderData();
    void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec4 uvOffset=glm::vec4(0,0,1.0f,1.0f),
        glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f),bool flipX =false);
private:
    Program shader;
    GLuint quadVAO;
};

#endif#pragma once
