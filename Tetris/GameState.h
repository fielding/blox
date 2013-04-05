//
//  GameState.h
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef Tetris_GameState_h
#define Tetris_GameState_h

#include "GameEngine.h"

class GameState
{
public:
  
  //GameState( GameEngine* game );
  virtual ~GameState() {}
  //{
  //  std::cout<<"Destructor Called!"<<std::endl;
  //}
  
  virtual void Pause() = 0;
  virtual void Resume() = 0;
    
  virtual void HandleEvents( GameEngine* game ) = 0;
  virtual void Update( GameEngine* game ) = 0;
  virtual void Draw ( GameEngine* game ) = 0;
  
  void ChangeState( GameEngine* game, GameState* state)
  {
    game->ChangeState( state );
  }
};


#endif
