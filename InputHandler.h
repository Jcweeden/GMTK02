#ifndef _InputHandler_
#define _InputHandler_

#include "SDL2/SDL.h"
#include "Game.h"
#include "Vector2D.h"


#include <iostream>
#include <vector>

class InputHandler
{
  
public:
  static InputHandler* Instance();

  void update(); //collects new input
  void clean();  //remove init joysticks - //if no joysticks - unneeded


  //returns true if parameter key is pressed
  bool isKeyDown(SDL_Scancode key);

  bool getIsSpaceKeyPressed()
  {
    if (isSpaceKeyPressed)
    {
      isSpaceKeyPressed = false;
      return true;
    }
    else
    {
    return isSpaceKeyPressed;
    }
  }

    Vector2D* getMousePosition() { return m_mousePosition; }

  
private:

    InputHandler()
        : isSpaceKeyPressed(false), m_mousePosition(new Vector2D(0,0))
    {};
  
  static InputHandler* s_pInstance;

  //keys
  const Uint8* m_keystates;
  bool isSpaceKeyPressed;

  Vector2D* m_mousePosition;

};

typedef InputHandler TheInputHandler;

#endif
