#ifndef GAME_H
#define GAME_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include<memory>
#include<vector>

#include "Program.h"
#include "spriteRenderer.h"
#include "ResourceManager.h"
#include "Player.h"
#include "SpriteLoader.h"

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
    bool Keys[1024] = { false };

    Player* player;
    //std::vector<Entity*> object;
private:
	int width;
	int height;
    SpriteRenderer* Renderer;
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    float animationTime = 0.0f;
};

#endif // GAME_H
