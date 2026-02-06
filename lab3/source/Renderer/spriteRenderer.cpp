#include"spriteRenderer.h"

#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale 함수
#include <glm/gtc/type_ptr.hpp>


SpriteRenderer::SpriteRenderer(Program& shader):shader(shader)
{
this->shader = shader;
this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

//모델행렬 계산, 받은 칼라 -> 두개값 유니폼으로 전달 
void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec4 uvOffset,
    glm::vec2 size, float rotate, glm::vec3 color)
{
    // prepare transformations
    this->shader.BindProgram();

    this->shader.SetVector("spriteOffset", uvOffset);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.SetMatrix("model", model);
    this->shader.SetVector("spriteColor", glm::vec3(color.x, color.y, color.z));
    glActiveTexture(GL_TEXTURE0); //텍스처(이미지)를 0번 슬롯 활성화
    texture.Bind(); // 활성화된 슬롯에 할당

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size) {
    this->DrawSprite(texture, position, glm::vec4(0, 0, 1, 1), size, 0.0f, glm::vec3(1.0f));
}

//맨 처음 렌더링 데이터 초기화용 VAO VBO싹다 초기화
void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO 인터리브 방식 
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
