#ifndef _Shooter_
#define _Shooter_

#include "I_GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "TextureManager.h"

#include <iostream>
#include <string>

class Shooter : public GameObject {

public:

  Shooter (int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame);


  virtual void update();
  virtual void draw();

public:

  float angle;

};

#endif
