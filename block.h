#ifndef _Block_
#define _Block_

#include "I_GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Ball.h"

#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>


class Block : public GameObject {

public:

  Block (int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame, unsigned p_countdownValue, int width = 48, int height = 48);


  virtual void update();
  virtual void draw();
  virtual void clean();

  void updateColliderPositions();

public:

  GameObject topCollider, bottomCollider, leftCollider, rightCollider;
  unsigned bounceReset;
  bool toBeDeleted;
  unsigned countdownValue;


  TTF_Font* fontTTF;
  SDL_Color textColour = {255,255,255};

  SDL_Surface* scoreMessage;
  SDL_Texture* scoreText; 
  SDL_Rect scoreRect;

};

#endif
