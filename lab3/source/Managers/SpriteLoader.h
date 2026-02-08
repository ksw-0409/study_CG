#ifndef SPRITELOADER_H
#define SPRITELOADER_H

#include"Entity.h"
#include"ResourceManager.h"

#include <fstream>
#include <iostream>
// json 해더 
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class SpriteLoader {
public:
    SpriteLoader() = delete;
    static void LoadConfig(const std::string& filepath, Entity* target, ResourceManager& manager) {
        std::ifstream file(filepath);
        json data = json::parse(file);

        // 텍스처 로드
        //uv 계산 위한 텍스처 전체 사이즈 
        manager.LoadTexture(data["texturePath"].get<std::string>().c_str(), true, data["textureName"]);
        auto texture = manager.GetTexture(data["textureName"]);
        float texWidth = static_cast<float>(texture->Width);
        float texHeight = static_cast<float>(texture->Height);

        //애니메이션 여부 확인
        bool isAnimated = data.value("isAnimated", false); // 기본값 false

        //콜론 로우 
        int rows = data["grid"]["rows"];
        int cols = data["grid"]["columns"];

        //애니메이션일경우       
        if (isAnimated) {
            // 애니메이션 데이터 
            for (auto it = data["animations"].begin(); it != data["animations"].end(); ++it) {
                Animation anim;
                auto thisAnim = it.value();
                //기본 정보
                anim.speed = thisAnim["speed"];
                anim.loop = thisAnim["loop"];
                int frameCount = thisAnim["frameCount"];
                //첫프레임 포지션 
                float startX = thisAnim["startX"];
                float startY = thisAnim["startY"];
                //칸 크기
                float widthF = thisAnim["frameWidth"];
                float heightF = thisAnim["frameHeight"];
                float widthUV= widthF / texWidth;
                float heightUV = heightF / texHeight;

                for (int i = 0; i < frameCount; i++) {
                    // UV 좌표 계산 2줄일 경우도 가능하도록 수정 
                    float u = ((float)(i % (int)cols) * widthF + startX)/ texWidth;
                    float v = ((float)(i / (int)cols) * heightF + startY)/texHeight;
                    anim.frames.push_back(glm::vec4(u , v , widthUV , heightUV));
                }
                // AnimatedSprite2D에 완성된 Animation 구조체 전달
                target->GetAnimatedSprite2D()->addAnimation(thisAnim["index"],anim);
            }
        }
        else {//애니메이션이 아닐경우 
            //추가 필요 타일멥이나 등등 
            target->GetSprite2D()->SetUV(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        }
    }
};

#endif //SPRITELOADER_H