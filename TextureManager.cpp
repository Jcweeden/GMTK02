#include "TextureManager.h"


TextureManager* TextureManager::s_pInstance = 0;

TextureManager* TextureManager::Instance()
{
  if(s_pInstance == 0)
    {
      s_pInstance = new TextureManager();
      return s_pInstance;
    }

    return s_pInstance;
}

bool TextureManager::load(std::string file, std::string mapID, SDL_Renderer* pRenderer)
{
  SDL_Surface* pTempSurface = IMG_Load(file.c_str());

  if (pTempSurface == 0) {
    std::cout << "Error in TextureManager::load(): incorrect file path" << std::endl;
    return false;
  }
  
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  if(pTexture !=0)   //if everything went okay, add to our list
  {
    textureMap[mapID] = pTexture;
    return true;
  }
  
  std::cout << "Error in TextureManager::load()" << std::endl;
  return false;   //reaching here meant something went wrong
}

void TextureManager:: draw(std::string mapID, int x, int y, int width, int height, SDL_Renderer* pRenderer, int currentRow, int currentFrame, SDL_RendererFlip flip)
{  
  SDL_Rect srcRect;
  SDL_Rect destRect;
  
  srcRect.x = width * currentFrame;
  srcRect.y = height * (currentRow-1);
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, textureMap[mapID], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentFrame, SDL_Renderer* pRenderer, int currentRow, SDL_RendererFlip flip) {
  
  SDL_Rect srcRect;
  SDL_Rect destRect;
  //std::cout << currentFrame << " " << currentRow << std::endl;
  srcRect.x = width * currentFrame;
  srcRect.y = height * (currentRow-1);
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
  textureMap.erase(id);
}
