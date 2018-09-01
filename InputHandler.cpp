#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = 0;


InputHandler* InputHandler::Instance()
{
  if(s_pInstance ==0)
    {
      s_pInstance = new InputHandler();
    }

    return s_pInstance;
}


bool InputHandler::isKeyDown(SDL_Scancode key)
{
  if (m_keystates != 0)
  {
    if (m_keystates[key] == 1) {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}


void InputHandler::update()
{
  SDL_Event event;

  while(SDL_PollEvent(&event))
  {
    m_keystates = SDL_GetKeyboardState(0);//update presssed keys

          if(event.type == SDL_MOUSEMOTION)
    {
      // std::cout << "InputHandler::update: button motion x: " << event.motion.x << " y: " << event.motion.y << std::endl;
      m_mousePosition->setX((float)event.motion.x);
      m_mousePosition->setY((float)event.motion.y);
    }
    
    if (event.type == SDL_QUIT)
    {
      std::cout << "InputHandler.cpp: Quit event found\n";
      TheGame::Instance()->quit();
    }

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_SPACE)
      {
        //std::cout << "space\n";
        isSpaceKeyPressed = true;
      }
    }
  }
}


void InputHandler::clean()
{
  m_keystates = SDL_GetKeyboardState(0);//update presssed keysym
  isSpaceKeyPressed = false;
  delete s_pInstance;
}
