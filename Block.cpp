#include "Block.h"

Block::Block(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame, unsigned p_countdownValue)
    : GameObject::GameObject(x,y,48,48,"blocks",p_numFrames,p_currentRow,p_currentFrame), countdownValue(p_countdownValue),


    topCollider(GameObject   (x,   y,    48, 1,"none",0,0,0)),
    bottomCollider(GameObject(x,   y+47, 48, 1,"none",0,0,0)),
    leftCollider(GameObject  (x,   y,  1,48,"none",0,0,0)),
    rightCollider(GameObject (x+47,y,  1,48,"none",0,0,0)),
    
    bounceReset(1), toBeDeleted(false)
{

  fontTTF = TTF_OpenFont("Assets/karmatic_arcade.ttf", 48);
  if (fontTTF == NULL) {
    fprintf(stderr, "error: font not found\n");
  }

  scoreMessage = TTF_RenderText_Solid(fontTTF, std::to_string(countdownValue).c_str(), textColour);
  scoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreMessage); 
  scoreRect.x = x+6;
  scoreRect.y = y+6;
  scoreRect.w = 36; 
  scoreRect.h = 36;
}

void Block::update()
{
  if (!toBeDeleted) {

    bool hasCollided = false;
    
    for (size_t i = 0; i < ThePlayState::Instance()->balls.size();i++)
    {
      if (ThePlayState::Instance()->balls[i]->bounceCooldown <= 0)
      {
        //check if colliding at all before checking each collider
        if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],this))
        {
          if (ThePlayState::Instance()->balls[i]->lastBounceType != 1)
          {
            {
              if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&topCollider))
              {
                ThePlayState::Instance()->balls[i]->bounceVertical();
                // ThePlayState::Instance()->balls[i]->lastBounceType = 1;
                ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
                if (!hasCollided)
                {
                  countdownValue--;
                  hasCollided = true;
                }
              }
            }
          }
    

          if (ThePlayState::Instance()->balls[i]->lastBounceType != 2)
          {
            if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&bottomCollider))
            {
              {
                ThePlayState::Instance()->balls[i]->bounceVertical();
                // ThePlayState::Instance()->balls[i]->lastBounceType = 2;
                ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
                if (!hasCollided)
                {
                  countdownValue--;
                  hasCollided = true;
                }
              }
            }
          }

          if (ThePlayState::Instance()->balls[i]->lastBounceType != 3)
          {
            {
              if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&rightCollider))
              {
                ThePlayState::Instance()->balls[i]->bounceHorizontal();
                // ThePlayState::Instance()->balls[i]->lastBounceType = 3;
                ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
                if (!hasCollided)
                {
                  countdownValue--;
                  hasCollided = true;
                }
              }
            }
          }

          if (ThePlayState::Instance()->balls[i]->lastBounceType != 4)
          {
            {
              if (TheCollManager::Instance()->isCollidingRectRect(ThePlayState::Instance()->balls[i],&leftCollider))
              {
                ThePlayState::Instance()->balls[i]->bounceHorizontal();
                // ThePlayState::Instance()->balls[i]->lastBounceType = 4;
                ThePlayState::Instance()->balls[i]->bounceCooldown = bounceReset;
                if (!hasCollided)
                {
                  countdownValue--;
                  hasCollided = true;
                }
              }
            }
          }
        }
      }
    }
    if (countdownValue == 0)
    {
      toBeDeleted = true;
      return;
    }
    else if (hasCollided)
    {
      if( scoreText != NULL ) SDL_DestroyTexture( scoreText );
      scoreMessage = TTF_RenderText_Blended(fontTTF,
                                            std::to_string(countdownValue).c_str(),
                                            textColour);
      scoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreMessage);
      SDL_FreeSurface( scoreMessage );
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

  SDL_RenderCopy(TheGame::Instance()->getRenderer(), scoreText, NULL, &scoreRect);
}

void Block:: clean()
{
  TTF_CloseFont( fontTTF );
  fontTTF = NULL;

  if( scoreText != NULL ) SDL_DestroyTexture( scoreText );
  
  GameObject::clean();
}

void Block::updateColliderPositions()
{
  topCollider.setPositionY(topCollider.getPosition().getY()+48);
  bottomCollider.setPositionY(bottomCollider.getPosition().getY()+48);
  leftCollider.setPositionY(leftCollider.getPosition().getY()+48);
  rightCollider.setPositionY(rightCollider.getPosition().getY()+48);

  scoreRect.y = getPosition().getY()+6;
}
