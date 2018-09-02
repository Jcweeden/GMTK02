#ifndef _CollisionManager_
#define _CollisionManager_

class GameObject;
class Ball;
class Block;

#include "Vector2D.h"

#include <algorithm>
#include <vector>

class CollisionManager {

public:
    //returns / creates singleton instance
    static CollisionManager* Instance();

    //returns true if two rectangles are colliding
    bool isCollidingRectRect(Ball* rectA, GameObject* rectB, int buffer = 1000);

    //returns true if parameter rectangle is colliding with circle
    bool isCollidingRectCircle(Ball* circle, GameObject* rect);

    std::vector<Vector2D> lineRect(Vector2D lineStartPos, Vector2D lineEndPos, Block* rect);

    Vector2D lineLine(Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4);
    
    //should value passed in be outside the upper/lower range it is clamped to this value
    double clamp(double value, double upper, double lower);
    

private:
    static CollisionManager* s_pInstance;
};

typedef CollisionManager TheCollManager;

#endif
