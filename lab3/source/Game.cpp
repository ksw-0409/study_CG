#include"Game.h"

Game::Game(int width, int height) :width(width), height(height) {
    Cat = new AnimatedSprite(0.3f);
    Cat2= new AnimatedSprite(0.3f);
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
    
        Cat2->setUV(8.0f, 10.0f);
        Cat2->addAnimation("Walk", 4, 8, true);
        Cat2->addAnimation("Idle", 3, 4, true);
        Cat2->addAnimation("Jump", 8, 5, false);
        Cat2->setAnimName("Idle");
    
        PlayerCat = new Player(Cat, width, height);
        PlayerCat2 = new Player2(Cat2, width, height);
    }
// game loop
void Game::ProcessInput(float dt) {
    PlayerCat->ProcessInput(this->Keys, dt);
    PlayerCat2->ProcessInput(this->Keys, dt);
}

void Game::Update(float dt,float fspeed){
    Cat->Update(dt, fspeed);
    Cat2->Update(dt, fspeed);
    PlayerCat->Update(dt);
    PlayerCat2->Update(dt);
}
void Game::Render(){
    Renderer->DrawSprite(
        *Manager.GetTexture("background"),
        glm::vec2(0.0f, 0.0f), 
        glm::vec2(1600.0f, 900.0f)
    );

    //(시작 위치 U, 시작 위치 V, 가로 폭, 세로 높이)
    glm::vec4 currentUV = glm::vec4(Cat->getU(), Cat->getV(), 1.0f / 8.0f, 1.0f / 10.0f);
    float direction = (PlayerCat->isFlip()) ? -1.0f : 1.0f; //Player에서 뒤집히는지 
    glm::vec2 renderPos = PlayerCat->getPosition(); //Player 에서 계산한 포지션 
    // 뒤집을때 이미지 너비만큼 x축 이동 보정
    if (PlayerCat->isFlip()) {
        renderPos.x += 300.0f; // 캐릭터 가로 크기만큼 더해줌
    }

    Renderer->DrawSprite(
        *Manager.GetTexture("cat"),
        renderPos,
        currentUV,
        glm::vec2(300.0f* direction, 300.0f), //가로크기가 300, -300 으로 랜더링
        0.0f, 
        glm::vec3(1.0f, 1.0f, 1.0f));

    glm::vec4 uv2 = glm::vec4(Cat2->getU(), Cat2->getV(), 1.0f / 8.0f, 1.0f / 10.0f);
    float dir2 = (PlayerCat2->isFlip()) ? -1.0f : 1.0f;
    glm::vec2 pos2 = PlayerCat2->getPosition();
    if (PlayerCat2->isFlip()) pos2.x += 300.0f;

    Renderer->DrawSprite(
        *Manager.GetTexture("cat"),
        pos2,
        uv2,
        glm::vec2(300.0f * dir2, 300.0f),
        0.0f,
        glm::vec3(0.0f, 1.0f, 1.0f));
}
