#ifndef ANIMATEDSPRITE2D_H
#define ANIMATEDSPRITE2D_H

#include <string>
#include<vector>
#include <glm/glm.hpp>
#include "Sprite2D.h"

// 애니메이션 데이터를 담는 구조체
struct Animation {
    std::vector<glm::vec4> frames; // UV 좌표
    float speed;    // 재생 속도
    bool loop;      // 반복 여부
};

class AnimatedSprite2D {
    std::vector<Animation> animations;      // 애니메이션 데이터 저장소
    int currentAnimIndex;                    // 현재 재생 중인 이름
    int currentFrame;                       // 현재 프레임 인덱스
    float timer;                            // 시간 누적용 타이머
    float speedMultiplier;                  // 전체 속도 조절
public:
    AnimatedSprite2D() : currentAnimIndex(-1), currentFrame(0), timer(0.0f), speedMultiplier(1.0f) {}
   
    //애니메이션 종류 추가(ex walk 몇행 몇개프레임 추가) 제이슨 자동화 하기 
    void addAnimation(int index, const Animation& anim) {
        animations.push_back(anim);
    }

    // 재생할 애니메이션 설정
    void play(const int index) {
        if (index < 0 || index >= animations.size()) return;
        if (currentAnimIndex == index) return; // 이미 재생 중이면 무시
        currentAnimIndex = index;
        currentFrame = 0;
        timer = 0.0f;
    }

    // 핵심 업데이트 로직 
    void Update(float delta, Sprite2D* targetSprite) {
        //안전장치 
        if (currentAnimIndex ==-1 || !targetSprite) return;

        Animation& anim = animations[currentAnimIndex];
        timer += delta * speedMultiplier; // 시간을 누적
        // 타이머가 지정된 속도에 도달하면 다음 프레임으로 교체
        if (timer >= anim.speed) {
            timer = 0.0f;
            currentFrame++;
            // 마지막 프레임 처리
            if (currentFrame >= (int)anim.frames.size()) {
                if (anim.loop) currentFrame = 0;
                else currentFrame = anim.frames.size() - 1;
            }
            targetSprite->SetUV(anim.frames[currentFrame]);
        }
    }

    // 속도 조절 기능
    void setSpeed(float multiplier) { speedMultiplier = multiplier; }
};

#endif