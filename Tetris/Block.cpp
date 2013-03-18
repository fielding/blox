//
//  Block.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "Block.h"

Block::Block(int x, int y, int bType)
{
  // Initialize offsets
  box.x = x * BLOCK_SIZE;
  box.y = y * BLOCK_SIZE;
  
  // Set the square's dimensions
  box.w = BLOCK_SIZE;
  box.h = BLOCK_SIZE;
  
  // Type (used for color)
  blockType = bType;
  
  // Initialize velocity
  xVel = 0;
  yVel = 0;
  
}

Block::~Block(){
  //cout<<"Destructor Called!"<<endl;
}
void Block::handle_input()
{
  /*
  if ( event.type == SDL_KEYDOWN )      // If a key was presed
  {
    switch ( event.key.keysym.sym )
    {
      case SDLK_UP:
        yVel -= BLOCK_SIZE / 2;
        break;
      case SDLK_DOWN:
        yVel += BLOCK_SIZE / 2;
        break;
      case SDLK_LEFT:
        xVel -= BLOCK_SIZE / 2;
        break;
      case SDLK_RIGHT:
        xVel += BLOCK_SIZE / 2;
        break;
      default:
        break;
    }
  }
  else if ( event.type == SDL_KEYUP )   // If a key was released
  {
    switch ( event.key.keysym.sym )
    {
      case SDLK_UP:
        yVel += BLOCK_SIZE / 2;
        break;
      case SDLK_DOWN:
        yVel -= BLOCK_SIZE / 2;
        break;
      case SDLK_LEFT:
        xVel += BLOCK_SIZE / 2;
        break;
      case SDLK_RIGHT:
        xVel -= BLOCK_SIZE / 2;
        break;
      default:
        break;
    }
  }
   */
}

void Block::move()
{
  
  box.x += xVel;      // Move left or right
  
  if ( ( box.x < 0 ) || ( box.x + BLOCK_SIZE > SCREEN_WIDTH ) )     // Check x-axis screen bounds
  {
    box.x -= xVel;    // Move back
  }
  
  box.y += yVel;      // Move the square up or down
  
  if ( ( box.y < 0 ) || (box.y + BLOCK_SIZE > SCREEN_HEIGHT) )     // Check y-axis screen bounds
  {
    box.y -= yVel;    // Move Back
  }
  
}
