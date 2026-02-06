#ifndef PLAYER_H
#define PLAYER_H

#include<glm/glm.hpp>
#include "AnimatedSprite.h"

class Player {
private:
    glm::vec2 position;
    glm::vec2 velocity;
    bool isGround;
    AnimatedSprite* sprite;
    float moveSpeed = 200.0f;
    float jumpFoce = 200.0f;
    float width;
    float height;
    bool flip;
public:
    Player(AnimatedSprite* s,float width,float height) :sprite(s), width(width),height(height),
        position(200.0f, 200.0f), velocity(0.0f, 0.0f), isGround(false), flip(false){}

    glm::vec2 getPosition() { return position; }
    bool isFlip() { return flip; }

    void ProcessInput(bool keys[], float dt) {
        velocity.x = 0.0f;

        if (keys[GLFW_KEY_LEFT]) {
            velocity.x = -moveSpeed;
            if (isGround)sprite->setAnimName("Walk");
            flip = true;
        }
        else if (keys[GLFW_KEY_RIGHT]) {
            velocity.x = moveSpeed;
            if (isGround) sprite->setAnimName("Walk");
            flip = false;
        }
        else  {
            if(isGround)sprite->setAnimName("Idle");
        }

        if (keys[GLFW_KEY_UP] && isGround) {
            velocity.y -= jumpFoce;
            isGround = false;
            sprite->setAnimName("Jump");
            position.y -= 1.0f;
        }
    }

    void Update(float dt) {
        const float GRAVITY = 400.0f;
        velocity.y += GRAVITY * dt; //공중 가는 속도 중력으로 조정 
        position += velocity * dt; //위치를 속도로 변화

        if (position.y >= 300.0f) { //땅 밑으로 갈경우 
            position.y = 300.0f; //땅으로 고정 
            velocity.y = 0.0f; //0으로 
            isGround = true; //땅임
        }
        else { isGround = false; }  //300 보다 위면 공중 
        //좌우 막기 
        if (position.x < 0) position.x = 0;
        if (position.x > width - 100.0f) position.x = width - 100.0f; 
    }
};

#endif // PLAYER_H