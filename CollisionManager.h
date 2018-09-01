#ifndef _CollisionManager_
#define _CollisionManager_

class GameObject;
class Ball;

class CollisionManager {

public:
    //returns / creates singleton instance
    static CollisionManager* Instance();

    //returns true if two rectangles are colliding
    bool isCollidingRectRect(Ball* rectA, GameObject* rectB, int buffer = 1000);

    //returns true if parameter rectangle is colliding with circle
    bool isCollidingRectCircle(Ball* circle, GameObject* rect);

    //should value passed in be outside the upper/lower range it is clamped to this value
    double clamp(double value, double upper, double lower);
    

private:
    static CollisionManager* s_pInstance;
};

typedef CollisionManager TheCollManager;

#endif
