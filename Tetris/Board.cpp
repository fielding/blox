//
//  Board.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "Board.h"

Board::Board( int blockWidth, int blockHeight )
{
  // populate the board grid with empty blocks
  cout<<"Board Constructor called!"<<endl;
  for ( int x = 0; x < blockWidth; x++ )
  {
    for ( int y = 0; y < blockHeight; y++)
    {
      mBoard[x][y] = 0;
    }
  }
}

void Board::updateBlock( int x, int y, int status )
{
  mBoard[x][y] = status;
}

bool Board::checkBlockCollision(Tetrimino* tetrimino, int direction)
{
  // check each block of the tetrimino
  for ( int b = 0; b < 4; b++ )
  {
    int x = tetrimino->activeTetrimino[b].box.x / 16;
    int y = tetrimino->activeTetrimino[b].box.y / 16;
    switch ( direction )
    {
      case left:
        if ( getBlockStatus( ( x - 1 ), y ) != 0 ) { return true; }
        break;
      case right:
        if ( getBlockStatus( ( x + 1 ), y ) != 0 ) { return true; }
        break;
      case down:
        if ( getBlockStatus( x, ( y + 1 ) ) != 0 ) { return true; }
        break;
    }
  }
  return false;
}

int Board::getBlockStatus(int x, int y)
{
  return this->mBoard[x][y];
}