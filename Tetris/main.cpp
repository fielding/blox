//
//  main.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/14/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//


#include "Game.h"

int main ( int agrc, char **argv )
{
  Game *game = new Game();
  game->start();
  return 0;
}