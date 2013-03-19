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
#include <cmath>

using namespace std;

class Board;
class Block;

class Tetrimino
{


public:
  
  // Constructor
  Tetrimino();
  ~Tetrimino();
  
  // public functions
  bool moveLeft(Board* myBoard);
  bool moveRight(Board* myBoard);
  bool moveDown(Board* myBoard);
  void hardDrop(Board* myBoard);
  void next();
  void rotate(string dir);
  void spawn(std::vector<Block>* target);
  int getDimension( int dimension, int unit);
  std::vector<Block> nextTetrimino;
  std::vector<Block> activeTetrimino;

private:
  void bubbleSort(vector <int> &num);
  int calcPixelHeight();
  int calcPixelWidth();
  double round( double number );
  enum direction_t { left, right, down };
  enum dimension_t { xMin, xMax, yMin, yMax };
  enum unit_t { blocks, pixels };
};

#endif /* defined(__Tetris__Tetrimino__) */
