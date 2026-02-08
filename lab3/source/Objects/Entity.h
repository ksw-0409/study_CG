#ifndef ENTITY_H
#define ENTITY_H

#include<glm/glm.hpp>
#include"Sprite2D.h"
#include"AnimatedSprite2D.h"

class Entity {
    std::string textureName; // 텍스처 이름 
protected:
    glm::vec2 position; //포지션 
    glm::vec2 size; //사이즈
    float rotation; //회전
    bool flipX;     //뒤집기
    //컴포넌트
    Sprite2D* Sprite;
    AnimatedSprite2D* AnimatedSprite;
public:
    Entity()
        : textureName(""),position(0.0f, 0.0f), size(1.0f, 1.0f), rotation(0.0f),
        flipX(false), Sprite(nullptr), AnimatedSprite(nullptr)
    {
        Sprite = new Sprite2D();
    }

    Entity(glm::vec2 pos, glm::vec2 s, Sprite2D* spr)
        : textureName(""),position(pos), size(s), Sprite(spr),
        rotation(0.0f), flipX(false), AnimatedSprite(nullptr) {}
    
    virtual ~Entity() {
        // 동적 할당된 컴포넌트 해제
        if (Sprite) delete Sprite;
        if (AnimatedSprite) delete AnimatedSprite;
    }
    void SetTextureName(std::string name) { textureName = name; }
    std::string GetTextureName()const {  return textureName;  }
    glm::vec2 GetSize()const { return size; }
    float GetRotation()const { return rotation; }
    glm::vec2 GetPosition() const { return position; }
    void SetPosition(glm::vec2 position) { this->position = position; }
    AnimatedSprite2D* GetAnimatedSprite2D() { return AnimatedSprite; }
    Sprite2D* GetSprite2D() { return Sprite; }

    //버추얼 사용해서 플레이어나 에너미 에서 업데이트 사용시 그 자식의 함수가 실행할수있도록 구현 
    virtual void Update(float delta) {
        // 애니메이션 있다면 스프라이트의 UV를 업데이트함
        if (AnimatedSprite != nullptr && Sprite != nullptr) {
            AnimatedSprite->Update(delta, Sprite);
        }
    }

    bool isFlip() const { return flipX; }
};

#endif //ENTITY_H