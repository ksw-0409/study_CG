#ifndef PLAYER2_H
#define PLAYER2_H

#include<glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "AnimatedSprite.h"

class Player2 {
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
    Player2(AnimatedSprite* s, float width, float height) :sprite(s), width(width), height(height),
        position(200.0f, 200.0f), velocity(0.0f, 0.0f), isGround(false), flip(false) {
    }

    glm::vec2 getPosition() { return position; }
    bool isFlip() { return flip; }

    void ProcessInput(bool keys[], float dt) {
        velocity.x = 0.0f;

        if (keys[GLFW_KEY_A]) {
            velocity.x = -moveSpeed;
            if (isGround)sprite->setAnimName("Walk");
            flip = true;
        }
        else if (keys[GLFW_KEY_D]) {
            velocity.x = moveSpeed;
            if (isGround) sprite->setAnimName("Walk");
            flip = false;
        }
        else {
            if (isGround)sprite->setAnimName("Idle");
        }

        if (keys[GLFW_KEY_W] && isGround) {
            velocity.y -= jumpFoce;
            isGround = false;
            sprite->setAnimName("Jump");
            position.y -= 1.0f;
        }
    }

    void Update(float dt) {
        const float GRAVITY = 400.0f;
        velocity.y += GRAVITY * dt;
        position += velocity * dt;

        if (position.y >= 300.0f) {
            position.y = 300.0f;
            velocity.y = 0.0f;
            isGround = true;
        }
        else { isGround = false; }
        if (position.x < 0) position.x = 0;
        if (position.x > width - 100.0f) position.x = width - 100.0f;
    }
};

#endif // PLAYER2_H