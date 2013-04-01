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

class GameEngine;
class Board;
class Block;

struct Coords
{
  int x;
  int y;
};

class Tetrimino
{


public:
  
  // Constructor
  Tetrimino(bool spawn, int type);
  ~Tetrimino();
  
  // public functions
  bool moveLeft(Board* myBoard);
  bool moveRight(Board* myBoard);
  bool moveDown(Board* myBoard, bool gravity);
  void hardDrop(Board* myBoard, int& score);
  void rotate(int direction, Board* myBoard);
  void spawn(int type);
  void resetPosition();
  int getDimension( int dimension, int unit);
  int getCurrentRotationState();
  
  std::vector<Block> pieces;
  std::vector<Block> pieceOrigins;
  bool held;
  int getPixelHeight();
  int getPixelWidth();
  bool wallKick( std::vector<Block>& rPieces, Board* myBoard, int direction );
  bool wallKickTest(int stateTransition, std::vector<Block>& rPieces, Board* myBoard, bool isI = false);
  
  
private:
  GameEngine* engine;
  Coords wallKickTests[8][4]=
  {
    { {-1,0},{-1,-1},{0,2},{-1,2} },
    { {1,0},{1,1},{0,-2},{1,-2} },
    { {1,0},{1,1},{0,-2},{1,-2} },
    { {-1,0},{-1,-1},{0,2},{-1,2} },
    { {1,0},{1,-1},{0,2},{1,2} },
    { {-1,0},{-1,1},{0,-2},{-1,-2} },
    { {-1,0},{-1,1},{0,-2},{-1,-2} },
    { {1,0},{1,-1},{0,2},{1,2} },
  };
  
  Coords wallKickTestsI[8][4] =
  {
    { {-2,0},{1,0},{-2,1},{1,-2} },
    { {2,0},{-1,0},{2,-1},{-1,2} },
    { {-1,0},{2,0},{-1,-2},{2,1} },
    { {1,0},{-2,0},{1,2},{-2,-1} },
    { {2,0},{-1,0},{2,-1},{-1,2} },
    { {-2,0},{1,0},{-2,1},{1,-2} },
    { {1,0},{-2,0},{1,2},{-2,-1} },
    { {-1,0},{2,0},{-1,-2},{2,1} },
  };
  
  void bubbleSort(vector <int> &num);
  double round( double number );
  enum direction_t { left, right, down };
  enum dimension_t { xMin, xMax, yMin, yMax };
  enum unit_t { blocks, pixels };
  int distanceDown;
  int distanceLeft;
  int distanceRight;
  int rotationsRight;
  int rotationsLeft;
};

#endif /* defined(__Tetris__Tetrimino__) */
