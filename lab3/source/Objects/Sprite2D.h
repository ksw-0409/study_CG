#ifndef SPRITE2D_H
#define SPRITE2D_H

#include <glm/glm.hpp>

class Sprite2D {
private:
    glm::vec4 uv;           // 현재 출력할 영역 (u, v, w, h)
    glm::vec2 size;         // 스프라이트의 기본 크기 (폭, 높이)

public:
    Sprite2D(glm::vec2 baseSize = glm::vec2(100.0f, 100.0f))
        :  uv(0.0f, 0.0f, 1.0f, 1.0f), size(baseSize) {
    }
    glm::vec4 GetUV() const { return uv; }
    glm::vec2 GetSize() const { return size; }

    // 애니메이터가 이 함수를 호출하여 화면에 보일 프레임을 바꿈
    void SetUV(const glm::vec4& newUV) { uv = newUV; }

    void SetSize(const glm::vec2& newSize) { size = newSize; }
};

#endif //SPRITE2D