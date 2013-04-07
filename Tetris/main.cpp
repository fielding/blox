//
//  main.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/14/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include <memory>

// #include "Game.h"
#include "GameEngine.h"
#include "PlayState.h"

int main ( int agrc, char **argv )
{
  int loops;
  float interpolation;
  
  // creat intance of the GameEngine called game
  GameEngine game( "Blox", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP );
  
  Uint32 next_game_tick = game.globalTimer.get_ticks();
  
  // Set the initial game state
 
  game.ChangeState( std::unique_ptr<PlayState>( new PlayState( &game ) ) );
  
  
  // game loop
  while ( game.Running() )
  {
    loops = 0;
    
    
    while ( game.globalTimer.get_ticks() > next_game_tick && loops < MAX_FRAMESKIP )
    {
      game.HandleEvents();
      game.Update();
    
      next_game_tick += SKIP_TICKS;
      loops++;
    }
    
    interpolation = float( game.globalTimer.get_ticks() + SKIP_TICKS - next_game_tick ) / float( SKIP_TICKS ); // implementing, but uncertain if I need yet due to nature of the piece movement
    game.Draw( interpolation );
    
  }
  
  return 0;
}