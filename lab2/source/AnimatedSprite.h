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
        bool repeat;        // 애니메이션 반복할지 
    };

    float epsilon = 0.01f; // 아주 미세한 보정값
public:
    AnimatedSprite(float speed=0.5f,float u=0,float v=0) :speed(speed),u(u),v(v) {  }
    std::map<std::string, Animation> animations;
    
    //애니메이션 종류 추가(ex walk 몇행 몇개프레임 추가)
    void addAnimation(std::string name, int row, int frameCount,bool repeat) {
        animations[name] = { row, frameCount,repeat };
    }

    //시트의 총 가로u 새로v 크기 넣어줌 
    void setUV(float u, float v) { this->u = u; this->v = v; }

    //지금 실행할 애니메이션 
    void setAnimName(std::string name) { 
        if (currentAnimName != name)currentFrame = 0;
        currentAnimName = name; 
    }


    //sptriteRenderer 에 있는 drawSprite 를 사용해 실질적 렌더링을 하기 위해서 
    // U V 의 크기를 리턴할수있게 만들었습니다  
    //U 칸당 크기 
    float getU(){return (float)currentFrame / u+ epsilon; }
    //V 칸당 크기 
    float getV() { return (float)animations[currentAnimName].row / v+ epsilon; }

    //애니메이션 프레임 fspeed는 스크롤로 조정하는 값 받아옴
    void Update(float delta, float fspeed) {
        speed = fspeed;
        //애니메이션 종류가 없으면 리턴 
        if (animations.find(currentAnimName) == animations.end()) return;

        const Animation& anim = animations[currentAnimName];
        timer += delta;
        if (timer >= speed) {
            if (anim.repeat) {
                currentFrame = (currentFrame + 1) % anim.frameCount;
            }
            else if (currentFrame<anim.frameCount-1) {
                currentFrame++;
            }
            timer = 0.0f;
        }
    }
};

#endif // GAME_H
