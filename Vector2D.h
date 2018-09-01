#ifndef _Vector2D_
#define _Vector2D_

#include <math.h>
#include <stdio.h>

class Vector2D {
public:

  Vector2D(float p_x, float p_y) {x = p_x; y = p_y;}
  
  float getX() {return x;}
  float getY() {return y;}
  
  void setX(float newX) {x = newX;}
  void setY(float newY) {y = newY;}


  friend Vector2D& operator+=(Vector2D& v1, const Vector2D v2)
  {
    v1.x += (float)v2.x;
    v1.y += (float)v2.y;

    return v1;
  }

    float calcDistance(Vector2D v2)
  {
    //calculate distance between this vector and vector v2 using pyth theorem
    return sqrt(pow(v2.x - x, 2) + 
                pow(v2.y - y, 2) * 1.0);
  }
  
protected:
  float x;
  float y;
};

#endif
