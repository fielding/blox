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
  // Game *game = new Game();
  // game->start();
  
  // creat intance of the GameEngine called game
  GameEngine game( "Blox", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP );
  
  // initialize the engine
  //game.Init( "Blox", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
  
  // Set the initial game state
  game.ChangeState( PlayState::Instance() );
  
  
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