#include "Block.h"

Block::Block(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame)
    : GameObject::GameObject(x,y,48,48,"blocks",p_numFrames,p_currentRow,p_currentFrame),


    topCollider(GameObject   (x,   y,    48, 1,"none",0,0,0)),
    bottomCollider(GameObject(x,   y+47, 48, 1,"none",0,0,0)),
    leftCollider(GameObject  (x,   y,  1,48,"none",0,0,0)),
    rightCollider(GameObject (x+47,y,  1,48,"none",0,0,0)),
    
    bounceReset(1)
{
}

void Block::update()
{
  for (size_t i = 0; i < ThePlayState::Instance()->balls.size();i++)
  {
    if (ThePlayState::Instance()->balls[i]->bounceCooldown <= 0)
    {
      if (ThePlayState::Instance()->balls[i]->lastBounceType != 1)
      {
        // if (ThePlayState::Instance()->balls[i]->getPosition().getX() + 12 > topCollider.getPosition().getX())
        {
          if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&topCollider))
          {
            ThePlayState::Instance()->balls[i]->bounceVertical();
            // ThePlayState::Instance()->balls[i]->lastBounceType = 1;
            ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
            //return;
          }
        }
      }
    

      if (ThePlayState::Instance()->balls[i]->lastBounceType != 2)
      {
        if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&bottomCollider))
        {
          //  if (ThePlayState::Instance()->balls[i]->getPosition().getX() + 12 > bottomCollider.getPosition().getX()+bottomCollider.getHeight())
          {
            ThePlayState::Instance()->balls[i]->bounceVertical();
            // ThePlayState::Instance()->balls[i]->lastBounceType = 2;
            ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
            //return;
          }
        }
      }

      if (ThePlayState::Instance()->balls[i]->lastBounceType != 3)
      {
        // if (ThePlayState::Instance()->balls[i]->getPosition().getY() + 12 > rightCollider.getPosition().getY()+rightCollider.getWidth())
        {
          if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&rightCollider))
          {
            ThePlayState::Instance()->balls[i]->bounceHorizontal();
            // ThePlayState::Instance()->balls[i]->lastBounceType = 3;
            ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
            //return;
          }
        }
      }

      if (ThePlayState::Instance()->balls[i]->lastBounceType != 4)
      {
        //  if (ThePlayState::Instance()->balls[i]->getPosition().getY() + 12 > leftCollider.getPosition().getY())
        {
          if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&leftCollider))
          {
            ThePlayState::Instance()->balls[i]->bounceHorizontal();
            // ThePlayState::Instance()->balls[i]->lastBounceType = 4;
            ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
            //return;
          }
        }
      }
    }
  }
}

void Block::draw()
{
  /*
  boxRGBA(TheGame::Instance()->getRenderer(),
          topCollider.getPosition().getX(), topCollider.getPosition().getY(),
          topCollider.getPosition().getX() + topCollider.getWidth(), topCollider.getPosition().getY() +topCollider.getHeight(),
          255, 0, 0, 150);
  boxRGBA(TheGame::Instance()->getRenderer(),
          bottomCollider.getPosition().getX(), bottomCollider.getPosition().getY(),
          bottomCollider.getPosition().getX() + bottomCollider.getWidth(), bottomCollider.getPosition().getY() + bottomCollider.getHeight(),
          0, 255, 0, 150);
  boxRGBA(TheGame::Instance()->getRenderer(),
          rightCollider.getPosition().getX(), rightCollider.getPosition().getY(),
          rightCollider.getPosition().getX() + rightCollider.getWidth(), rightCollider.getPosition().getY() + rightCollider.getHeight(),
          0, 0, 255, 150);
  boxRGBA(TheGame::Instance()->getRenderer(),
          leftCollider.getPosition().getX(), leftCollider.getPosition().getY(),
          leftCollider.getPosition().getX() + leftCollider.getWidth(), leftCollider.getPosition().getY() +leftCollider.getHeight(),
          0, 123, 123, 150);
  */
    GameObject::draw();

}

void Block::updateColliderPositions()
{
  topCollider.setPositionY(topCollider.getPosition().getY()+48);
  bottomCollider.setPositionY(bottomCollider.getPosition().getY()+48);
  leftCollider.setPositionY(leftCollider.getPosition().getY()+48);
  rightCollider.setPositionY(rightCollider.getPosition().getY()+48);
}
