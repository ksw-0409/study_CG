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
        Manager.LoadTexture("textures/cat.png", true, "cat");
        Manager.LoadTexture("textures/background.png", true, "background");
        Cat->setUV(8.0f, 10.0f);
        Cat->addAnimation("Walk", 4, 8,true);
        Cat->addAnimation("Idle", 3, 4, true);
        Cat->addAnimation("Jump", 8, 5,false);
        Cat->setAnimName("Idle");
    
    }
// game loop
void Game::ProcessInput(float dt) {
    PlayerCat->ProcessInput(this->Keys, dt);
}

void Game::Update(float dt,float fspeed){
    Cat->Update(dt, fspeed);
    PlayerCat->Update(dt);
}
void Game::Render(){

}
