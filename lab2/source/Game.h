#ifndef GAME_H
#define GAME_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include<memory>

#include "Program.h"
#include "spriteRenderer.h"
#include"ResourceManager.h"
#include"AnimatedSprite.h"
#include"Player.h"


class Game {
public:
    Game(int width, int height);
    ~Game();

    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt,float fspeed);
    void Render();
    ResourceManager Manager;
    AnimatedSprite* Cat;
    AnimatedSprite* Ball;
    bool Keys[1024] = { false };

private:
	int width;
	int height;
    SpriteRenderer* Renderer;
    Player* PlayerCat;
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    float animationTime = 0.0f;
    int currentFrame = 0;
};

#endif // GAME_H
