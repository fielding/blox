//
//  main.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/14/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//


// #include "Game.h"
#include "GameEngine.h"
#include "PlayState.h"

int main ( int agrc, char **argv )
{
  // creat intance of the GameEngine called game
  GameEngine game( "Blox", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP );
  
  // Set the initial game state

  game.ChangeState( new PlayState( &game ) );
  
  
  // game loop
  while ( game.Running() )
  {
    game.HandleEvents();
    game.Update();
    game.Draw();
  }
  
  // cleanup the engine
  //game.Cleanup();
  
  return 0;
}