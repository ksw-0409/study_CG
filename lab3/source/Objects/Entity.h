#ifndef ENTITY_H
#define ENTITY_H

#include<glm/glm.hpp>
#include"Sprite2D.h"
#include"AnimatedSprite2D.h"

class Entity {
protected:
    glm::vec2 position; //포지션 
    glm::vec2 size; //사이즈
    float rotation; //회전
    bool flipX;     //뒤집기
    //컴포넌트
    Sprite2D* Sprite;
    AnimatedSprite2D* AnimatedSprite;
public:
    Entity(glm::vec2 pos, glm::vec2 s, Sprite2D* spr)
        : position(pos), size(s), Sprite(spr),
        rotation(0.0f), flipX(false), AnimatedSprite(nullptr) {}
    
    virtual ~Entity() {
        // 동적 할당된 컴포넌트 해제
        if (Sprite) delete Sprite;
        if (AnimatedSprite) delete AnimatedSprite;
    }

    glm::vec2 GetPosition() const { return position; }
    void SetPosition(glm::vec2 position) { this->position = position; }

    virtual void Update(float delta) {
        // 애니메이션 있다면 스프라이트의 UV를 업데이트함
        if (AnimatedSprite != nullptr && Sprite != nullptr) {
            AnimatedSprite->Update(delta, Sprite);
        }
    }
    bool isFlip() const { return flipX; }
};

#endif //ENTITY_H