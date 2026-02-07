#include"Game.h"

Game::Game(int width, int height) :width(width), height(height) {
   // Cat = new Sprite(0.3f);
}
Game::~Game() {
    if (Renderer) {
        delete Renderer;
    }
}

    void Game::Init() { //세이더 연결, 변화없는 프로젝션행렬 , 이미지쉐이더 유니폼으로 전달  
        Manager.LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
        Program* Shader = Manager.GetShader("sprite");
        Shader->BindProgram();
        Shader->SetMatrix("projection", projection);
        Shader->SetTexture("image", 0);
        Renderer = new SpriteRenderer(*Shader);

        player = new Player(this->width, this->height, new Sprite2D());

        SpriteLoader::LoadConfig("assets/data/knight.json", player, Manager);
    }
// game loop
void Game::ProcessInput(float dt) {
    player->ProcessInput(this->Keys, dt);
}

void Game::Update(float dt,float fspeed){
    player->Update(dt);
}
void Game::Render(){
        // Sprite2D에서 최신 UV와 텍스처 정보를 가져옵니다.
        Renderer->DrawSprite(
            *Manager.GetTexture("knight"),
            player->GetPosition(),
            player->GetSprite2D()->GetUV(), // AnimatedSprite에 의해 업데이트된 UV
            player->GetSprite2D()->GetSize(), 
            0.0f,
            glm::vec3(1.0f),
            player->isFlip() // ProcessInput에서 결정된 뒤집기 상태
        );
    
}
