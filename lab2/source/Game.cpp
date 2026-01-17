#include"Game.h"

Game::Game(int width, int height) :width(width), height(height) { Anime = new AnimatedSprite(0.3f); }
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
    Anime->setUV(8.0f, 10.0f);
    Anime->addAnimation("Walk", 4, 8);
    Anime->addAnimation("Idle", 3, 4);
    Anime->addAnimation("Jump", 8, 7);
    Anime->setAnimName("Idle");
}
// game loop
//void Game::ProcessInput(float dt) {}

void Game::Update(float dt,float fspeed){
    Anime->Update(dt, fspeed);
}
void Game::Render(){
    Renderer->DrawSprite(
        *Manager.GetTexture("background"),
        glm::vec2(-300.0f, 0.0f), 
        glm::vec2(1600.0f, 900.0f)
    );

    glm::vec4 currentUV = glm::vec4(Anime->getU(), Anime->getV(), 1.0f / 8.0f, 1.0f / 10.0f);
    Renderer->DrawSprite(
        *Manager.GetTexture("cat"),
        glm::vec2(200.0f, 200.0f),
        currentUV,
        glm::vec2(300.0f, 300.0f), 
        0.0f, 
        glm::vec3(1.0f, 1.0f, 1.0f));
}
