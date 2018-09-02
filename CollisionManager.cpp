#include "CollisionManager.h"

#include <iostream>
#include "GameObject.h"
#include "Ball.h"
#include "Block.h"


CollisionManager* CollisionManager::s_pInstance = 0;

CollisionManager* CollisionManager::Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new CollisionManager();
      return s_pInstance;
    }

    return s_pInstance;
  }

double CollisionManager::clamp(double value, double upper, double lower)
{
  return std::min(upper, std::max(value, lower));
}

bool CollisionManager::isCollidingRectRect(Ball* rectA, GameObject* rectB, int buffer)
{
  //calculate buffers that reduce the hitbox size of the rects
  int aHBuf = rectA->getHeight() / 1000;
  int aWBuf = rectA->getWidth() / 1000;
    
  int bHBuf = rectB->getHeight() / 1000;
  int bWBuf = rectB->getWidth() / 1000;
  
  //if the bottom of rectA is lower than the top of rectB - no collision
  if((rectA->getPosition().getY() + rectA->getHeight()) - aHBuf <= rectB->getPosition().getY() + bHBuf)
  { return false; }
    
  //if the top of rectA is higher than the bottom of rectB - no collision
  if(rectA->getPosition().getY() + aHBuf >= (rectB->getPosition().getY() + rectB->getHeight()) - bHBuf)
  { return false; }
    
  //if the right of rectA does not meet the left of rectB - no collision
  if((rectA->getPosition().getX() + rectA->getWidth()) - aWBuf <= rectB->getPosition().getX() +  bWBuf)
  { return false; }
    
  //if the left of rectA is further away than the right of rectB - no collision
  if(rectA->getPosition().getX() + aWBuf >= (rectB->getPosition().getX() + rectB->getWidth()) - bWBuf)
  { return false; }
    
  //else, a collision
  return true;
}

bool CollisionManager::isCollidingRectCircle(Ball* circle, GameObject* rect)
{
  //find the closest point to the circle within the rect
  float closestX = clamp(circle->getPosition().getX(),
                         rect->getPosition().getX(),
                         rect->getPosition().getX() + rect->getWidth());
  
  float closestY = clamp(circle->getPosition().getY(),
                         rect->getPosition().getY(),
                         rect->getPosition().getY() + rect->getHeight());

  //calc distance between the circle's center and this closest point
  float distanceX = circle->getPosition().getX() - closestX;
  float distanceY = circle->getPosition().getY() - closestY;

  //if dist is less than the circle's radius, is a collision
  float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
  return distanceSquared < (circle->getWidth()/2 * circle->getWidth()/2);
}

Vector2D CollisionManager::lineLine(Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4)
{
  float x1 = p1.getX(), x2 = p2.getX(), x3 = p3.getX(), x4 = p4.getX();
  float y1 = p1.getY(), y2 = p2.getY(), y3 = p3.getY(), y4 = p4.getY();
 
  float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  // If d is zero, there is no intersection
  if (d == 0) return Vector2D(0,0);
 
  // Get the x and y
  float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
  float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
  float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

  // Check if the x and y coordinates are within both lines
  if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
       x < std::min(x3, x4) || x > std::max(x3, x4) ) return Vector2D(0,0);
  if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
       y < std::min(y3, y4) || y > std::max(y3, y4) ) return Vector2D(0,0);
 
  // Return the point of intersection
  Vector2D ret (x,y);
  //ret->x = x;
  //ret->y = y;

  return ret;
}


std::vector<Vector2D> CollisionManager::lineRect(Vector2D lineStartPos, Vector2D lineEndPos, Block* rect)
{
  std::vector<Vector2D> hitPositions;

  unsigned buffer = 0;
  unsigned bufferLR = 1;

  // check if the line has hit any of the rectangle's sides
  // uses the Line/Line function below

  //L
  hitPositions.push_back(lineLine(lineStartPos,lineEndPos,
                       Vector2D(rect->getPosition().getX(),rect->getPosition().getY()-buffer),
                                  Vector2D(rect->getPosition().getX(),rect->getPosition().getY()+rect->getHeight()+buffer)));

  //R
  hitPositions.push_back(lineLine(lineStartPos,lineEndPos,
                        Vector2D(rect->getPosition().getX()+rect->getWidth(),rect->getPosition().getY()-buffer),
                                  Vector2D(rect->getPosition().getX()+rect->getWidth(),rect->getPosition().getY()+rect->getHeight()+buffer)));

  //T
  hitPositions.push_back(lineLine(lineStartPos,lineEndPos,
                      Vector2D(rect->getPosition().getX()-buffer,rect->getPosition().getY()),
                                  Vector2D(rect->getPosition().getX()+rect->getWidth()+buffer,rect->getPosition().getY())));
  //B
  hitPositions.push_back(lineLine(lineStartPos,lineEndPos,
                         Vector2D(rect->getPosition().getX()-buffer,rect->getPosition().getY()+rect->getHeight()),
                                  Vector2D(rect->getPosition().getX()+rect->getWidth()+buffer,rect->getPosition().getY()+rect->getHeight())));
                           

  // if ANY of the above are true, the line
  // has hit the rectangle


  //add the type of collision to end of vector
  //horiz collision
  if (hitPositions[0].getX() != 0 && hitPositions[0].getY() != 0)
    hitPositions.push_back(Vector2D(1,0));
  if (hitPositions[1].getX() != 0 && hitPositions[1].getY() != 0)
    hitPositions.push_back(Vector2D(1,0));
  //vert collision
  if (hitPositions[2].getX() != 0 && hitPositions[2].getY() != 0)
    hitPositions.push_back(Vector2D(0,1));
  if (hitPositions[3].getX() != 0 && hitPositions[3].getY() != 0)
    hitPositions.push_back(Vector2D(0,1));

  return hitPositions;

  /*
    if (left || right || top || bottom) {
    return true;
  }
  return false;
  */
  /*
  if (left)
    return 1;
  if (right)
    return 2;
  if (top)
    return 3;
  if (bottom)
    return 4;
  else
    return 0;
  */
}
