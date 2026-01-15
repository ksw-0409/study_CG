#include <GL/gl3w.h>   
#include <GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"

#include <iostream>

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;


int main(int argc, char* argv[])
{
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

    //그릴 윈도우 생성 
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    //어디그릴지 투명도 등등 
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    game.Init();

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        float time = glfwGetTime();
        deltaTime = time - lastFrameTime;
        lastFrameTime = time;
        glfwPollEvents();

        // manage user input
        //first.ProcessInput(deltaTime);

        // update game state
        game.Update(deltaTime);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        //더블버퍼링 깜박임 현상 방지 위해 사용 
        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    //game.Manager.Clear();
    glfwTerminate();//os 수준에서 쓴 자원 정리 용 
    return 0;       
}