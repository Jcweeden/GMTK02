#include "PlayState.h"

#include "Game.h"
#include "Ball.h"
#include "Block.h"
#include "Shooter.h"

PlayState* PlayState::s_pInstance = 0;

PlayState* PlayState::Instance()
{
  if (s_pInstance == 0)
  {
    s_pInstance = new PlayState();
    return s_pInstance;
  }

  return s_pInstance;
}

PlayState::PlayState()
    : score(0), highScore(0), levelNumber(1), gameOver(false), canShoot(true), shooter(nullptr)
{
  srand (time(NULL));

  
  
  initText();
  loadSounds();

  TheTextureManager::Instance()->load("Assets/shooter.png", "shooter", TheGame::Instance()->getRenderer());
  TheTextureManager::Instance()->load("Assets/ball.png", "ball", TheGame::Instance()->getRenderer());
  TheTextureManager::Instance()->load("Assets/blocks.png", "blocks", TheGame::Instance()->getRenderer());
  TheTextureManager::Instance()->load("Assets/HorizontalBlocks.png", "HorizontalBlocks", TheGame::Instance()->getRenderer());
  TheTextureManager::Instance()->load("Assets/VerticalBlocks.png", "VerticalBlocks", TheGame::Instance()->getRenderer());

  shooter = new Shooter(240, 720, 0, 1, 0);

  
  setupLevel();
}

void PlayState::setupLevel()
{
  gameOver = false;
  score = 0;
  //clean();

  //setup first row of blocks
  spawnNextRowBlocks();
}

void PlayState::spawnNextRowBlocks()
{
  std::vector<bool> xPos(11); //vector set to false for each row index if a block is not yet in that row
  for (bool typ : xPos)
  {
    typ = false;
  }
  
  //if any vertical blocks to add instantiate them now
  if (toInstantiateDoubleSushiRowIndex.size() > 0)
  {
    for (size_t i = 0; i < toInstantiateDoubleSushiRowIndex.size(); i++)
    {
      Block* newSushi = new Block(toInstantiateDoubleSushiRowIndex[i]*48, 120, 0, 1, 0);
      newSushi->setTextureID("VerticalBlocks");
      blocks.push_back(newSushi);
      xPos[toInstantiateDoubleSushiRowIndex[i]] = true;
      //std::cout << toInstantiateDoubleSushiRowIndex[i]*48 << "\n";
      std::cout << "spawning second part of vert bloc\n";
    }
  }
  
  //randomly select between 2 and row length - 1 num of blocks to spawn (min 2)
  //deduct existing double lengths to be instantiated from the number that can be spawned
  unsigned numToSpawn = rand() % 5 /*- toInstantiateDoubleSushiRowIndex.size()*/ + 1;

  std::cout << "numToSpawn: " << numToSpawn << "\n";
  std::cout << "toInstantiateDoubleSushiRowIndex: " << toInstantiateDoubleSushiRowIndex.size() << "\n";
  
  //reset vertical blocks to empty so can be filled for next level
  toInstantiateDoubleSushiRowIndex.clear();
  

  //randomly select position for +1 balls pickup
  //TODO

  //for each block to spawn
  for (size_t i = 0; i < numToSpawn; i++)
  {
    unsigned pos;
    unsigned attempts = 0;
    bool freeRowFound = false;
      
    while (attempts < 10 && !freeRowFound)
    {
      //std::cout << "attempting to find free row\n";
      //select a random index in positions vector
      unsigned randSelectedXIndex = rand() % xPos.size();
      attempts++;
      if (xPos[randSelectedXIndex] == false)
      {
        //get the position from this
        pos = randSelectedXIndex;

        //remove the value so it will not be selected again
        xPos[randSelectedXIndex] = true;

        freeRowFound = true;
        attempts = 11;
      }
    }
    if (freeRowFound)
    {
      //decide whether to instantiate a double vertical length sushi or single
      int sushiType = rand() % 5;

      //if not at edge and can instantiate a horizontal sushi allow possibilty of horizontal being instantiated
      if (pos != 10) sushiType = rand() % 6;

      switch (sushiType)
      {
        case 5: //instantiate horizontal sushi block
          {
            //if block next door is free
            if (xPos[pos+1] == false)
            {
              //select random sprite
              unsigned sushiSprite = rand() % 2+1;

              //create blocks
              Block* newSushiA = new Block(pos*48, 144, 0, sushiSprite, 0);
              newSushiA->setTextureID("HorizontalBlocks");
              Block* newSushiB = new Block((pos+1)*48, 144, 0, sushiSprite, 1);
              newSushiB->setTextureID("HorizontalBlocks");
              std::cout << "spawning horiz bloc\n";

              //set the block next door to already set
              xPos[pos+1] = true;

              //set num to spawn to one less, as have instantiated two blocks
              numToSpawn--;
              
              //add to vector
              blocks.push_back(newSushiA);
              blocks.push_back(newSushiB);
            }
            else {
              //else just instantiate a normal block
              sushiType = 0;
            }
            break;
          }
        case 0: case 1:  case 2:  case 3: //instantiate a normal sushi
          { 
            Block* newSushi = new Block(pos*48, 144, 0, 1, rand() % 3);
            blocks.push_back(newSushi);
            std::cout << "spawning normal bloc\n";
            break;
          }
        case 4:
          {
            //TODO: instantiate start of vertical sushi block
            Block* newSushi = new Block(pos*48, 144, 0, 1, 1);
            newSushi->setTextureID("VerticalBlocks");
            blocks.push_back(newSushi);
            //std::cout << pos*48 << "\n";
            std::cout << "spawning vert bloc top\n";
            toInstantiateDoubleSushiRowIndex.push_back(pos);
            break;
          }
      }
    }
  }
}

void PlayState::nextLevel()
{
  levelNumber++;
  gameOver = false;

  moveDownBlocks();
  spawnNextRowBlocks();
}


void PlayState::moveDownBlocks()
{
  //move all blocks down
  for (size_t i = 0 ; i < blocks.size(); i++)
  {
    blocks[i]->setPositionY(blocks[i]->getPosition().getY()+48);
    blocks[i]->updateColliderPositions(); 
  }

  //if one has reached bottom - game over
}

void PlayState::lostGame()
{
  if (score > highScore) highScore = score;
  updateHighScoreText();
  levelNumber = 1;
  setupLevel();
}

void PlayState::update()
{
  if (gameOver)
    lostGame();

  if (shooter != nullptr) shooter->update();

  std::vector<unsigned> toDelete;
  
  for (size_t i = 0; i < balls.size(); i++)
  {
    if (balls[i] != nullptr) balls[i]->update();
    if (balls[i]->toBeDeleted)
      toDelete.insert(toDelete.begin(), i);
  }

  if (toDelete.size() > 0 )
  {
    for (size_t i = 0; i < toDelete.size(); i++)
    {
      delete balls[toDelete[i]];
      balls.erase(balls.begin() + toDelete[i]);
    }
  }
  
  for (size_t i = 0 ; i < blocks.size(); i++)
  {
    if (blocks[i] != nullptr) blocks[i]->update();
  }  
  
}

void PlayState::render()
{
  
  //box on top of screen
  boxRGBA(TheGame::Instance()->getRenderer(),
           0, 0,
           528, 72,
           52, 252, 60, 255);

  
  
  for (size_t i = 0; i < balls.size(); i++)
  {
    if (balls[i] != nullptr) balls[i]->draw();
  }

  if (shooter != nullptr) shooter->draw();
  
    
  for (size_t i = 0 ; i < blocks.size(); i++)
  {
    if (blocks[i] != nullptr) blocks[i]->draw();
  }
  
  if (canShoot)
  {


    float mouseAngle = atan2(
        shooter->getPosition().getY() - TheInputHandler::Instance()->getMousePosition()->getY(),
        TheInputHandler::Instance()->getMousePosition()->getX() - shooter->getPosition().getX());

    mouseAngle *= (180.0f / 3.14159265359f);

    
    //std::cout << mouseAngle << "\n";
    //std::cout << mouseAngle * (180 / 3.141592f) << "\n";

    if ( mouseAngle < 0.0f) {
      mouseAngle = 180.0f + (180.0f + mouseAngle );
      }

    int lbound = 8;
    int ubound = 172;
    if (mouseAngle > 90.0f && mouseAngle < 270.0f) {
      // Left
      if (mouseAngle > ubound) {
        mouseAngle = ubound;
      }
    } else {
      // Right
      if (mouseAngle < lbound || mouseAngle >= 270.0f ) {
        mouseAngle = lbound;
      }
    }        

    shooter->angle = mouseAngle;

    if (mouseAngle > 8 && mouseAngle < 172)
    {      
      //draw shoot line
      lineRGBA(TheGame::Instance()->getRenderer(),
               shooter->getPosition().getX()+24, shooter->getPosition().getY(),
               TheInputHandler::Instance()->getMousePosition()->getX(), TheInputHandler::Instance()->getMousePosition()->getY(),
               255, 255, 255, 255);
    }
    
    //player.y+tileheight/2) - pos.y, pos.x - (player.x+tilewidth/2)));

    
    for (size_t i = 0 ; i < blocks.size(); i++)
    {
      if (blocks[i] != nullptr) blocks[i]->update();
    }  
  }
  
  //text

  /*
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), scoreLabelText, NULL, &scoreLabelRect); 
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), scoreText, NULL, &scoreRect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), highscoreLabelText, NULL, &highscoreLabelRect); 
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), highscoreText, NULL, &highscoreRect);
  */
}


void PlayState::handleInput()
{
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
  {
    nextLevel();
  }
  
  if (TheInputHandler::Instance()->getIsSpaceKeyPressed())
  {
    //nextLevel();
    //}

    if (canShoot && shooter->angle > 8 && shooter->angle < 172)// & shooter->angle > 8 && shooter->angle < 172)
    {
      //std::cout<<std::cout.precision();
      std::cout << "shot ball\n";
      //canShoot = false; //disable further shots
      //spawn and send off a new bubble at this angle

      Ball* newBall = new Ball(shooter->getPosition().getX()+24-4, shooter->getPosition().getY(), 0,1,0);

      //set velocity
      newBall->angle = shooter->angle;

      // Move the bubble in the direction of the mouse
      float x = (float)cos(newBall->angle * (3.14159265359f/180.0f));
      float y = -1.0f * (float)sin(newBall->angle * (3.14159265359f/180.0f));

      //std::cout << "velocity x: " << x << " y: " << y <<"\n";
      newBall->setVelocityX((x-0.03f)*newBall->speedMulitplier);
      newBall->setVelocityY(y*newBall->speedMulitplier);
      
      //add to balls
      balls.push_back(newBall);
    }

  }
}

void PlayState::clean()
{
  if (shooter != nullptr) delete shooter;
  
  for (size_t i = 0 ; i < blocks.size(); i++)
  {
    if (blocks[i] != nullptr)
    {
      blocks[i]->clean();
      delete blocks[i];
    }
  }
  blocks.clear();

  for (size_t i = 0 ; i < balls.size(); i++)
  {
    if (balls[i] != nullptr)
    {
      balls[i]->clean();
      delete balls[i];
    }
  }
  balls.clear();
  
  //text
  /*
    if( scoreText != NULL ) SDL_DestroyTexture( scoreText );
    if( scoreLabelText != NULL ) SDL_DestroyTexture( scoreLabelText );
  if( highscoreText != NULL ) SDL_DestroyTexture( highscoreText );
  if( highscoreLabelText != NULL ) SDL_DestroyTexture( highscoreLabelText );
  */
}

void PlayState::updateHighScoreText()
{
  if( highscoreText != NULL ) SDL_DestroyTexture( highscoreText );
  
  std::string scoreStr = std::to_string(highScore);
  
  highscoreMessage = TTF_RenderText_Blended(fontTTF,
                                        scoreStr.c_str(),
                                        textColour);
  highscoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), highscoreMessage);
  SDL_FreeSurface( highscoreMessage );
}

void PlayState::initText()
{

  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  
  fontTTF = TTF_OpenFont("Assets/karmatic_arcade.ttf", 48);
  if (fontTTF == NULL) {
    fprintf(stderr, "error: font not found\n");
  }

  scoreMessage = TTF_RenderText_Solid(fontTTF, "0000", textColour);
  scoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreMessage); 
  scoreRect.x = 65;
  scoreRect.y = 55;
  scoreRect.w = 80; 
  scoreRect.h = 30;

  scoreLabelMessage = TTF_RenderText_Solid(fontTTF, " YOUR-SCORE ", textColour);
  scoreLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreLabelMessage); 
  scoreLabelRect.x = 15;
  scoreLabelRect.y = 15;
  scoreLabelRect.w = 180;
  scoreLabelRect.h = 30;

  highscoreMessage = TTF_RenderText_Solid(fontTTF, "0000", textColour);
  highscoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreMessage); 
  highscoreRect.x = 360;
  highscoreRect.y = 55;
  highscoreRect.w = 80; 
  highscoreRect.h = 30;

  highscoreLabelMessage = TTF_RenderText_Solid(fontTTF, "HIGH-SCORE", textColour);
  highscoreLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), highscoreLabelMessage); 
  highscoreLabelRect.x = 310;
  highscoreLabelRect.y = 15;
  highscoreLabelRect.w = 180;
  highscoreLabelRect.h = 30;
}

void PlayState::loadSounds()
{
  //TheSoundMixer::Instance()->load("Assets/audio/name.wav", "name", SOUND_SFX);
}
