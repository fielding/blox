//
//  MenuState.h
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__MenuState__
#define __Tetris__MenuState__

#include <iostream>
#include <string>

#include "GameState.h"
#include "PlayState.h"
#include "Constants.h"

#include "SDL.h"
#include "SDL_image.h"

class MenuState: public GameState
{
public:
  MenuState( GameEngine *game );
  ~MenuState();
  
  void Pause();
  void Resume();
  
  void HandleEvents( GameEngine* game );
  void Update( GameEngine* game );
  void Draw( GameEngine* game );
  
private:
  // Objects/Object Pointers
  
  // Surfaces
  SDL_Surface* interfaceMenu;
  
  // Functions
  void loadAssets( GameEngine* game );
};


#endif /* defined(__Tetris__MenuState__) */
