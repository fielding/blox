//
//  Board.h
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Board__
#define __Tetris__Board__

#include <iostream>
#include <SDL.h>
#include "Constants.h"
#include "Block.h"
#include "Tetrimino.h"


using namespace std;

class Board
{
public:
  
  // Constructor
  Board( int blockWidth, int blockHeight );

  // Functions
  void updateBlock(int x, int y, int status);
  bool checkBlockCollision(Tetrimino* tetrimino, int direction);
  int mBoard[10][20];
  int getBlockStatus(int x, int y);
  
private:
  // TODO: Fix this, either make it a vector or whatever is needed to make it scalable
  //int mBoard[BOARD_BLOCK_WIDTH][BOARD_BLOCK_HEIGHT];
  // bring mBoard back to being private
  enum direction_t {left, right, down};
};


#endif /* defined(__Tetris__Board__) */
