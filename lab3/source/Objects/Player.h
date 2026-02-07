#ifndef PLAYER_H
#define PLAYER_H

#include<glm/glm.hpp>
#include "Entity.h"

class Player : public Entity {
private:
    glm::vec2 velocity;
    bool isGround;
    float moveSpeed = 300.0f;
    float jumpFoce = 450.0f;
    float width;
    float height;
public:
    Player(float w, float h, Sprite2D* spr)
        : Entity(glm::vec2(400.0f, 300.0f), glm::vec2(100.0f, 100.0f), spr),
        width(w), height(h), velocity(0.0f, 0.0f), isGround(true) {
        AnimatedSprite = new AnimatedSprite2D();
    }

    void ProcessInput(bool keys[], float dt) {
        velocity.x = 0.0f;
        if (keys[GLFW_KEY_LEFT]) {
            velocity.x = -moveSpeed;
            if (isGround)AnimatedSprite->play(1); //Run
            flipX = true;
        }
        else if (keys[GLFW_KEY_RIGHT]) {
            velocity.x = moveSpeed;
            if (isGround) AnimatedSprite->play(1); //Run
            flipX = false;
        }
        else  {
            if(isGround)AnimatedSprite->play(0); //Idle
        }
        
        if (keys[GLFW_KEY_UP] && isGround) {
            AnimatedSprite->play(2); //rull
           // position.y=-1.0f;
        }
    }

    void Update(float dt) {
        const float GRAVITY = 400.0f;
       // velocity.y += GRAVITY * dt; //공중 가는 속도 중력으로 조정 
        position += velocity * dt; //위치를 속도로 변화
        /*
        //지면판별
        float groundLevel = 500.0f; // 화면 하단 기준 설정
        if (position.y >= groundLevel) { //땅 밑으로 갈경우 
            position.y = groundLevel; //땅으로 고정 
            velocity.y = 0.0f; //0으로 
            isGround = true; 
        }
        else { isGround = false; }  //500 보다 위면 공중 
        //좌우 막기 
        if (position.x < 0) position.x = 0;
        if (position.x > width - size.x) position.x = width - size.x;
        */
        Entity::Update(dt);
    }
};

#endif // PLAYER_H