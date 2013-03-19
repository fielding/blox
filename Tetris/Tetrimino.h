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
#include <cmath>

using namespace std;

class Tetrimino
{
public:
  
  // Constructor
  Tetrimino();
  ~Tetrimino();
  
  // public functions
  void move( int xOffset, int yOffset );
  void next();
  void rotate(string dir);
  void spawn(std::vector<Block>* target);
  
  std::vector<Block> nextTetrimino;
  std::vector<Block> activeTetrimino;

private:
  void bubbleSort(vector <int> &num);
  int calcPixelHeight();
  int calcPixelWidth();
  int calcPixelOriginX();
  int calcPixelOriginY();
  double round( double number );

};

#endif /* defined(__Tetris__Tetrimino__) */
