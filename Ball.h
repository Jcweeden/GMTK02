#ifndef _Ball_
#define _Ball_

#include "I_GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "CollisionManager.h"

#include <iostream>
#include <string>

class Ball : public GameObject {

public:

  Ball(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame);

  void fixedUpdate(float frameTimeRemaining = 1000.0f / 60);
  virtual void update();
  virtual void draw();

  void bounceHorizontal();
  void bounceVertical();

  bool checkIfWallCollision(Vector2D endPos, float frameTimeRemaining);

public:

  float angle;
  float speedMulitplier;
  unsigned lastBounceType;
  //0 = none, 1 = top, 2 = bottom, 3 = right, 4 = left, 5 = topWall, 6 = rightWall, 7 = leftWall;

  unsigned bounceCooldown;

  bool toBeDeleted;

  Block* lastBlockCollidedWith;
};

#endif
