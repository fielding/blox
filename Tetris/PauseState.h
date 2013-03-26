//
//  PauseState.h
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__PauseState__
#define __Tetris__PauseState__

#include <iostream>

#include "GameState.h"
#include "MenuState.h"

#include "SDL.h"
#include "SDL_image.h"

class PauseState: public GameState
{
public:
  void Init();
  void Cleanup();
  
  void Pause();
  void Resume();
  
  void HandleEvents( GameEngine* game );
  void Update( GameEngine* game );
  void Draw( GameEngine* game );
  
  static PauseState* Instance()
  {
    return &pausestate;
  }
  
protected:
  PauseState() { }
  
private:
  // Objects/Object Pointers
  static PauseState pausestate;
  
  // Surfaces
  SDL_Surface* interfaceMessagePaused;
  
  // Variables
  void loadAssets();
  
  // Functions
  SDL_Surface *load_image( std::string filename );
  void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
  
};


#endif /* defined(__Tetris__PauseState__) */
