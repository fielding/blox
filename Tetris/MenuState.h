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
#include "Constants.h"

#include "SDL.h"
#include "SDL_image.h"

class MenuState: public GameState
{
public:
  void Init();
  void Cleanup();
  
  void Pause();
  void Resume();
  
  void HandleEvents( GameEngine* game );
  void Update( GameEngine* game );
  void Draw( GameEngine* game );
  
  static MenuState* Instance()
  {
    return &menustate;
  }
  
protected:
  MenuState() { }
  
private:
  // Objects/Object Pointers
  static MenuState menustate;
  
  // Surfaces
  SDL_Surface* interfaceMenu;
  
  // Variables
  void loadAssets();
  
  // Functions
  SDL_Surface *load_image( std::string filename );
  void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );

};


#endif /* defined(__Tetris__MenuState__) */
