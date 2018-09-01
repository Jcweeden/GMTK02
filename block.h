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

class Block : public GameObject {

public:

  Block (int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame);


  virtual void update();
  virtual void draw();

  void updateColliderPositions();

public:

  GameObject topCollider, bottomCollider, leftCollider, rightCollider;
  unsigned bounceReset;
};

#endif
