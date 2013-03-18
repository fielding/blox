//
//  Tetrimino.h
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Tetrimino__
#define __Tetris__Tetrimino__

#include <iostream>
#include <vector>
#include "Block.h"

using namespace std;

class Tetrimino
{
public:
  
  // Constructor
  Tetrimino();
  ~Tetrimino();
  
  // public functions
  void spawn(std::vector<Block>* target);
  void move( int xOffset, int yOffset );
  void next();
  
  std::vector<Block> nextTetrimino;
  std::vector<Block> activeTetrimino;

private:
  // can I make nextTetrimino and activeTetrimino private?
  
};

#endif /* defined(__Tetris__Tetrimino__) */
