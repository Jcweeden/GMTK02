#include "Shooter.h"

Shooter::Shooter(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame)
    : GameObject::GameObject(x,y,48,96,"shooter",p_numFrames,p_currentRow,p_currentFrame), angle(0.0f)
{
}

void Shooter::update()
{

}

void Shooter::draw()
{
  GameObject::draw();
}
