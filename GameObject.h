#ifndef _GameObject_
#define _GameObject_

#include "I_GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "TextureManager.h"

#include <iostream>
#include <string>

class GameObject : public I_GameObject {

public:

  GameObject(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_currentRow, int p_currentFrame, int p_animationSpeed = 200);

  virtual void draw();
  virtual void drawFrame();
  virtual void update();
  virtual void clean();

  Vector2D& getPosition() { return position; }
  Vector2D& setPosition(Vector2D p_position) { position = p_position; }

  Vector2D& setPositionX(float p_x) { position = Vector2D(p_x, position.getY()); }
  Vector2D& setPositionY(float p_y) { position = Vector2D(position.getX(), p_y); }

  Vector2D& setVelocityX(float p_x) { velocity.setX(p_x); }
  Vector2D& setVelocityY(float p_y) { velocity.setY(p_y); }
  
  int getWidth() { return width; }
  int getHeight() { return height; }

  int setWidth(int p_width) { width = p_width; }
  int setHeight(int p_height) { height = p_height; }
  
  virtual void setFrame(int frame) { currentFrame = frame;}
  int getFrame() { return currentFrame;}
  void setTextureID(std::string p_textureID) { textureID = p_textureID;}
  void setRow(int row) { currentRow = row;}
  
  void setNumFrames(unsigned val) { numFrames = val;} 
  void setAnimationSpeed(unsigned val) { animationSpeed = val;} 


protected:

  int width;
  int height;

  Vector2D position;
  Vector2D velocity;
  Vector2D acceleration;

  int numFrames;
  int currentRow;
  int currentFrame;
  int animationSpeed;
  
  std::string textureID;

};

#endif
