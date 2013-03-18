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