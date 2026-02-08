#include <GL/gl3w.h>   
#include <GLFW/glfw3.h>

// ImGui 헤더 
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Game.h"
#include "ResourceManager.h"

#include <iostream>

// The Width of the screen
const unsigned int SCREEN_WIDTH = 1280;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 720;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(int argc, char* argv[])
{
#pragma region 초기화
    //강의 초기화 방식 그대로 사용 
    if (!glfwInit()) //glfw 초기화
    {
        // Initialization failed
    }
    //오픈지엘 버전 지정:
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //창크기조절 막기
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return-1;
    }
    //OpenGL context생성(context => 구조체 struct) glm3w 초기화
    glfwMakeContextCurrent(window);
    //헬퍼 초기화 : opengl의 함수를 이용하기위한 helper(loader)를 초기화 

    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return -1;
    }
    //3.2 서포트 하는지 확인 
    if (!gl3wIsSupported(3, 2)) {
        fprintf(stderr, "OpenGL 3.2 not supported\n");
        return -1;
    }
    //컴퓨터 버전 출력 
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
        glGetString(GL_SHADING_LANGUAGE_VERSION));
    glfwSwapInterval(1);  //enable vsync

    printf("OpenGL %s, GLSL %s\n",
        glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    // 기본적인 초기화 끝 

    //ImGui 초기화 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); 
    // 플랫폼 바인딩 확인
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        fprintf(stderr, "ImGui GLFW 초기화 실패\n");
        return -1;
    }
    // 렌더러 바인딩 확인 
    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        fprintf(stderr, "ImGui OpenGL3 초기화 실패\n");
        return -1;
    }
#pragma endregion

    //그릴 윈도우 생성 
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    //어디그릴지 투명도 등등 
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   

    game.Init();

    glfwSetWindowUserPointer(window, &game);
    glfwSetKeyCallback(window, key_callback);

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;
    static int frameSpeed = 1;
    float frameSpeedF;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        float time = glfwGetTime();
        deltaTime = time - lastFrameTime;
        lastFrameTime = time;
        glfwPollEvents();

        // ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Settings"); // 창 이름
            // SliderInt("이름", &변수, 최솟값, 최댓값)
            ImGui::SliderInt("frameSpeed", &frameSpeed, 1, 10);
            //ImGui::Text("%.1f frameSpeed", frameSpeed*0.1);
            ImGui::End();
            frameSpeedF = (float)frameSpeed;
        }

        // manage user input
        game.ProcessInput(deltaTime);

        // update game state
        game.Update(deltaTime, frameSpeedF);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        //imgui 그리기 
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //더블버퍼링 깜박임 현상 방지 위해 사용 
        glfwSwapBuffers(window);
    }

    //Imgui 종료 해제
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    game.Manager.Clear();
    glfwTerminate();//os 수준에서 쓴 자원 정리 용 
    return 0;       
}

//콜백함수 문법 대로 매개변수 처리  
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    void* ptr = glfwGetWindowUserPointer(window);
    Game* game = static_cast<Game*>(ptr);
    //게임창 포인터 추출 위해 

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //키 입력 처리 배열기반 관리 
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            game->Keys[key] = true;
        else if (action == GLFW_RELEASE) 
            game->Keys[key] = false;
    }
}