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
        manager.LoadTexture(data["texturePath"].get<std::string>().c_str(), true, data["textureName"]);

        //애니메이션 여부 확인
        bool isAnimated = data.value("isAnimated", false); // 기본값 false
        //애니메이션일경우       
        if (isAnimated) {
            // 시트의 전체 칸 수 가져오기
            float cols = data["grid"]["columns"];
            float rows = data["grid"]["rows"];

            // 애니메이션 데이터 
            for (auto it = data["animations"].begin(); it != data["animations"].end(); ++it) {
                Animation anim;

                anim.speed = it.value()["speed"];
                anim.loop = it.value()["loop"];

                int row = it.value()["row"];
                int frameCount = it.value()["frameCount"];

                // 해당 애니메이션의 모든 프레임 UV를 미리 계산해서 저장

                //칸 크기 먼저 구함
                float width = 1.0f / cols;
                float height = 1.0f / rows;

                for (int i = 0; i < frameCount; i++) {
                    // UV 좌표 계산 2줄일 경우도 가능하도록 수정 
                    float u = (float)(i % (int)cols) * width;
                    float v = (float)(row + i / (int)cols) * height;

                    anim.frames.push_back(glm::vec4(u , v , width , height));
                }
                // AnimatedSprite2D에 완성된 Animation 구조체 전달
                target->GetAnimatedSprite2D()->addAnimation(it.value()["index"],anim);
            }
        }
        else {//애니메이션이 아닐경우 
            //추가 필요 타일멥이나 등등 
            target->GetSprite2D()->SetUV(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        }
    }
};

#endif //SPRITELOADER_H