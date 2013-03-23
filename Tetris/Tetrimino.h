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
  Tetrimino(bool spawn, int type);
  ~Tetrimino();
  
  // public functions
  bool moveLeft(Board* myBoard);
  bool moveRight(Board* myBoard);
  bool moveDown(Board* myBoard);
  void hardDrop(Board* myBoard);
  void rotate(string dir);
  void spawn(int type);
  void resetPosition();
  int getDimension( int dimension, int unit);
  
  std::vector<Block> pieces;
  std::vector<Block> pieceOrigins;
  bool held;
  int getPixelHeight();
  int getPixelWidth();
  
  
private:
  void bubbleSort(vector <int> &num);
  double round( double number );
  enum direction_t { left, right, down };
  enum dimension_t { xMin, xMax, yMin, yMax };
  enum unit_t { blocks, pixels };
  int distanceDown;
  int distanceLeft;
  int distanceRight;
};

#endif /* defined(__Tetris__Tetrimino__) */
