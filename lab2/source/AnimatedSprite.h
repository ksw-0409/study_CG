#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <string>
#include <map>
#include <glm/glm.hpp>


class AnimatedSprite {
    float speed;        // 재생 속도
    float u, v;
    std::string currentAnimName;
    int currentFrame = 0;
    float timer = 0.0f;

    struct Animation {
        int row;            // 시트에서의 행 번호
        int frameCount;     // 프레임 개수
    };

    float epsilon = 0.01f; // 아주 미세한 보정값
public:
    AnimatedSprite(float speed=0.5f,float u=0,float v=0) :speed(speed),u(u),v(v) {  }

    std::map<std::string, Animation> animations;

    void addAnimation(std::string name, int row, int frameCount) {
        animations[name] = { row, frameCount };
    }
    void setUV(float u, float v) { this->u = u; this->v = v; }
    void setAnimName(std::string name) { currentAnimName = name; }
    float getU(){return (float)currentFrame / u+ epsilon; }
    float getV() { return (float)animations[currentAnimName].row / v+ epsilon; }

    void Update(float delta, float fspeed) {
        speed = fspeed;
        if (animations.find(currentAnimName) == animations.end()) return;

        const Animation& anim = animations[currentAnimName];
        timer += delta;
        if (timer >= speed) {
            currentFrame = (currentFrame + 1) % anim.frameCount;
            timer = 0.0f;
        }
    }
};

#endif // GAME_H
