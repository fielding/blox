//
//  Block.h
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Block__
#define __Tetris__Block__

#include <iostream>
#include <SDL.h>
#include "Constants.h"

using namespace std;

class Block
{
  
public:
  Block( int x, int y, int bType );
  ~Block();
  
  // move the object
  void move();
  
  // Define type (mainly used to determine the block color
  int blockType;
  
  // The collision box of the square; object's x/y coordinates and dimensions are held inside a SDL_Rect
  SDL_Rect box;

private:
  
  // Velocity
  int xVel, yVel;
  
};

#endif /* defined(__Tetris__Block__) */
