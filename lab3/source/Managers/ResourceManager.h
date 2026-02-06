#ifndef MANAGER_H
#define MANAGER_H

#include <GL/gl3w.h>

#include <map>
#include <string>


#include "texture2D.h"
#include "Program.h"


class ResourceManager
{
public:
    // 리소스 저장소
     std::map<std::string, std::unique_ptr<Program>>  Shaders; //Program.h 기능을 활용해 스마트포인터 map 으로 만들었습니다 
     std::map<std::string, std::unique_ptr<Texture2D>> Textures;
     ResourceManager(){}
     ~ResourceManager();
     // 셰이더 프로그램을 로드(및 생성)합니다
     void  LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
     // 저장된 sader를 검색합니다.
     Program* GetShader(std::string name);
  
     // 파일에서 텍스처를 불러오고 생성합니다
     void LoadTexture(const char* file, bool alpha, std::string name);
     // 저장된 텍스처를 검색합니다
     Texture2D* GetTexture(std::string name);
     // 로드된 모든 리소스를 적절하게 할당 해제
     void Clear();
private:
    // 파일에서 단일 텍스처를 불러옵니다.
    std::unique_ptr<Texture2D> loadTextureFromFile(const char* file, bool alpha);
};

#endif#pragma once
