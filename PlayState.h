#ifndef _PlayState_
#define _PlayState_

#include "SDL2/SDL2_gfxPrimitives.h"
#include <SDL2/SDL_ttf.h>

//coll
//sound

#include "Vector2D.h"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>


class GameObject;
class Ball;
class Block;
class Shooter;


class PlayState {

public:
  static PlayState* Instance();

  PlayState();

  void update();
  void updateBlocks();
  void render();
  void handleInput();
  void clean();

  void initText();
  void loadSounds();

  void setupLevel();
  void lostGame();
  void nextLevel();
  void updateHighScoreText();

  void spawnNextRowBlocks();
  void moveDownBlocks();
  
  
public:

  bool gameOver;
  unsigned levelNumber;
  unsigned highScore;
  unsigned score;

  bool canShoot;

  Shooter* shooter;
  
  std::vector<Ball*> balls;
  std::vector<Block*> blocks;


  //contains x row indexs where double sushis are to be instantiated in the next level
  std::vector<unsigned> toInstantiateDoubleSushiRowIndex;

  
private:

  static PlayState* s_pInstance;

  //text
  TTF_Font* fontTTF;
  SDL_Color textColour = {255,255,255};

  SDL_Surface* scoreMessage;
  SDL_Texture* scoreText; 
  SDL_Rect scoreRect;

  SDL_Surface* scoreLabelMessage;
  SDL_Texture* scoreLabelText; 
  SDL_Rect scoreLabelRect;

  SDL_Surface* highscoreMessage;
  SDL_Texture* highscoreText; 
  SDL_Rect highscoreRect;

  SDL_Surface* highscoreLabelMessage;
  SDL_Texture* highscoreLabelText; 
  SDL_Rect highscoreLabelRect;
  
};

typedef PlayState ThePlayState;

#endif
