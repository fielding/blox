//
//  GameOverState.h
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__GameOverState__
#define __Tetris__GameOverState__

#include <iostream>

#include "GameState.h"
#include "PlayState.h"

#include "SDL.h"
#include "SDL_image.h"

class GameOverState: public GameState
{
public:
  GameOverState( GameEngine* game );
  ~GameOverState();
  
  void Pause();
  void Resume();
  
  void HandleEvents( GameEngine* game );
  void Update( GameEngine* game );
  void Draw( GameEngine* game );

private:
  // Objects/Object Pointers
  
  // Surfaces
  SDL_Surface* interfaceMessageGameOver;
  
  // Variables
  void loadAssets();
  
  // Functions
  SDL_Surface *load_image( std::string filename );
  void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
  
};


#endif /* defined(__Tetris__GameOverState__) */
