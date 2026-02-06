#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ResourceManager::~ResourceManager() {
    Clear(); 
}

void ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    auto newTexture2D = loadTextureFromFile(file, alpha);
    Textures[name] = std::move(newTexture2D);
}

Texture2D* ResourceManager::GetTexture(std::string name)
{
    auto it = Textures.find(name);
    //안전검사 
    if (it == Textures.end())
    {
        std::cout << "no value getShader" << std::endl;
        return nullptr;
    }
    return it->second.get();
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    Shaders.clear();   
    // (properly) delete all textures
    Textures.clear();
}

void  ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
     auto newProgram= Program::GenerateFromFileVsFs(vShaderFile, fShaderFile);
     Shaders[std::string(name)] = std::move(newProgram);
}

Program* ResourceManager::GetShader(std::string name)
{
    auto it = Shaders.find(name);
    //안전검사 
    if (it == Shaders.end())
    {
        std::cout << "no value getShader" << std::endl;
        return nullptr;
    }
    return it->second.get();
}

std::unique_ptr<Texture2D> ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    // create texture object
    auto newTexture = std::make_unique<Texture2D>();
    if (alpha)
    {
        newTexture->Internal_Format = GL_RGBA;
        newTexture->Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    newTexture->Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return newTexture;
}