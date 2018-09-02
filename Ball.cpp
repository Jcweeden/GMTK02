#include "Ball.h"
#include "Block.h"

Ball::Ball(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame)
    : GameObject::GameObject(x,y,1,1,"ball",p_numFrames,p_currentRow,p_currentFrame), angle(0.0f), speedMulitplier(6.5f), bounceCooldown(0), toBeDeleted(false), lastBlockCollidedWith(nullptr)
{

}


void Ball::fixedUpdate(float frameTimeRemaining)
{
  //set ball collider to middle of sprite
  //getPosition().setX(getPosition().getX()+5);
  //getPosition().setY(getPosition().getY()+5);

  //distance to move left for this frame
  float timeRemaining = (1000.0f / 60) / frameTimeRemaining;

  
  //calculate end pos after movement
  Vector2D endPos = Vector2D (getPosition().getX() + (velocity.getX() * timeRemaining),
                              getPosition().getY() + (velocity.getY() * timeRemaining));

  aalineRGBA(TheGame::Instance()->getRenderer(),
             getPosition().getX(),
             getPosition().getY(),
             endPos.getX(),
             endPos.getY(),
             255,255,255,255);
  
  //check for collisions of the line with blocks
  std::vector<Vector2D> blocksHitPos;
  std::vector<Vector2D> tempBlocksHitPos;

  float closestBlockCollDist = 10000.0f;

  //CHECK WALLS HERE - pass in rect that is edges of screen

  //skip blocks if wall coll
  if (blocksHitPos.size() == 0/*4*/)
  {
    //for each block
    for (size_t i = 0; i < ThePlayState::Instance()->blocks.size();i++)
    {
      //if not the same block that was collided with before
      if (ThePlayState::Instance()->blocks[i] != lastBlockCollidedWith)
      {
        //get all collisions with it
        tempBlocksHitPos = TheCollManager::Instance()->lineRect(getPosition(), endPos, ThePlayState::Instance()->blocks[i]);
        //and if were collisions
        if (tempBlocksHitPos.size() > 4)
        {
          //check if the closest block to collide with
          float distance = getPosition().calcDistance(
              Vector2D(ThePlayState::Instance()->blocks[i]->getPosition().getX()+24,
                       ThePlayState::Instance()->blocks[i]->getPosition().getY()+24));
          if (distance < closestBlockCollDist )
          {
            closestBlockCollDist = distance;
            //prevent the next run of fixedUpdate from colliding with the same block
            lastBlockCollidedWith = ThePlayState::Instance()->blocks[i];

            blocksHitPos.clear();
            
            for (int i = 0; i < tempBlocksHitPos.size(); i++)
              blocksHitPos.push_back(tempBlocksHitPos[i]);
            //decrement the life of the block
        
            //break as block will collide with the ball
            //break;
          }
        }
      }
    }     
  }
  //getPosition().setX(getPosition().getX()-5);
  //getPosition().setY(getPosition().getY()-5);

  //if a coll was found
  if (blocksHitPos.size() > 4)
  {
    //find the collision that occurs closest to the ball
    unsigned closestColIndex = 0;
    float closestColLength = 100000;
    unsigned numberColIndex = 0;
    unsigned actualColIndex = 0;
    
    for (size_t i = 0; i < 4; i++)
    {
      //if a collision with this wall occured
      if (blocksHitPos[i].getX() != 0 && blocksHitPos[i].getY() != 0)
      {
        //increment the number of collisions found
        numberColIndex++;
        
        //if collision distance from the ball is less than closest one found
        if ((int)getPosition().calcDistance(blocksHitPos[i]) == (int)closestColLength)
        {
          std::cout << "same length\n";
        }
        else if (getPosition().calcDistance(blocksHitPos[i]) < closestColLength)
        {
          closestColLength = getPosition().calcDistance(blocksHitPos[i]);
          closestColIndex = i;
          actualColIndex = numberColIndex;
        }
      }
    }

    //and alter its movement direction based on whether it hit horizontally or vertically
    if (blocksHitPos[3+actualColIndex].getX() == 0)
      bounceVertical();//bounceHorizontal();
    else
      bounceHorizontal();//bounceVertical();


    //now determine how far along the original movement this collision occured
    //distance between orig and final point / length of the line
    float timePassedInMovement = frameTimeRemaining * (getPosition().calcDistance(endPos) / getPosition().calcDistance(blocksHitPos[closestColIndex]));

    //move the ball to the closest coll point
    setPosition(blocksHitPos[closestColIndex]);

    boxRGBA(TheGame::Instance()->getRenderer(),
            blocksHitPos[closestColIndex].getX()-2, blocksHitPos[closestColIndex].getY()-2,
            blocksHitPos[closestColIndex].getX()+2, blocksHitPos[closestColIndex].getY()+2,
            255, 0, 0, 255);

    //and call update with the remaining movement time left in the frame
    fixedUpdate(frameTimeRemaining - (timePassedInMovement*frameTimeRemaining));
  }
  else //no collision
  {
    //set blocks to ignore in next frame to null
    lastBlockCollidedWith = nullptr;
    //and continue ball on its normal path
    update();
  }
}


void Ball::update()
{
  if (bounceCooldown > 0) bounceCooldown--;

  if (getPosition().getY() > 768)
  {
    toBeDeleted = true;
    return;
  }
  
  if (getPosition().getX() < 0 && lastBounceType != 7)
  {
    bounceHorizontal();
    //lastBounceType = 7;
    getPosition().setX(1);
    bounceCooldown = 0;
  }
  else if (getPosition().getX() > 528 - width && lastBounceType != 6)
  {
    bounceHorizontal();
    getPosition().setX(528-width-1);
    //lastBounceType = 6;
    bounceCooldown = 0;
  }
  else if (getPosition().getY() < 72 && lastBounceType != 5)
  {
    bounceVertical();
    getPosition().setY(73);
    //lastBounceType = 5;
    bounceCooldown = 0;
  }
  
  //std::cout << "updating ball\n"; 
  GameObject::update();
}

void Ball::draw()
{
  setWidth(12);
  setHeight(12);
  getPosition().setX(getPosition().getX()-5);
  getPosition().setY(getPosition().getY()-5);
  GameObject::draw();
  getPosition().setX(getPosition().getX()+5);
  getPosition().setY(getPosition().getY()+5);
  setWidth(1);
  setHeight(1);

  /*
    boxRGBA(TheGame::Instance()->getRenderer(),
    getPosition().getX(), getPosition().getY(),
    getPosition().getX() + getWidth(), getPosition().getY() + getHeight(),
    255, 0, 0, 150);
  */
}

void Ball::bounceHorizontal()
{
  angle = 180 - angle;
  float x = (float)cos(angle * (3.14159265359f/180.0f));
  float y = -1.0f * (float)sin(angle * (3.14159265359f/180.0f));

  setVelocityX(x*speedMulitplier);
  setVelocityY(y*speedMulitplier);
}


void Ball::bounceVertical()
{
  angle = -angle;
  float x = (float)cos(angle * (3.14159265359f/180.0f));
  float y = -1.0f * (float)sin(angle * (3.14159265359f/180.0f));

  setVelocityX(x*speedMulitplier);
  setVelocityY(y*speedMulitplier);
}
