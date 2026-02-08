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

            Entity* fruit = new Entity();
            fruit->SetPosition(glm::vec2(300.0f, 300.0f));
            Manager.LoadTexture("assets/textures/fruit.png", true, "fruit");
            fruit->SetTextureName("fruit");
            object.push_back(fruit);
        
    }
// game loop
void Game::ProcessInput(float dt) {
    player->ProcessInput(this->Keys, dt);
}

void Game::Update(float dt,float fspeed){
    player->Update(dt);
}
void Game::Render(){
    Renderer->DrawSprite(
        *Manager.GetTexture("knight"),
        player->GetPosition(),
        player->GetSprite2D()->GetUV(), 
        player->GetSprite2D()->GetSize(), 
        0.0f,
        glm::vec3(1.0f),
        player->isFlip() 
    );
        
    for (Entity* ent : object) {
        std::string texName = ent->GetTextureName();
        Renderer->DrawSprite(
            *Manager.GetTexture(texName),   // 엔티티마다 다른 텍스처 불러오게 처리 
            ent->GetPosition(),            
            ent->GetSprite2D()->GetUV(),    
            ent->GetSize(),                 
            ent->GetRotation(),           
            glm::vec3(1.0f),                
            ent->isFlip()                 
        );
    }
}
