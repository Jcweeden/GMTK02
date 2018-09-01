#include "Ball.h"

Ball::Ball(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame)
    : GameObject::GameObject(x,y,3,3,"ball",p_numFrames,p_currentRow,p_currentFrame), angle(0.0f), speedMulitplier(4.5f), bounceCooldown(0), toBeDeleted(false)
{

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
  GameObject::draw();
  setWidth(3);
  setHeight(3);
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
