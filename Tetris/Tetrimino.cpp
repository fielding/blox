//
//  Tetrimino.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "Tetrimino.h"
#include "Board.h"
#include "Block.h"


Tetrimino::Tetrimino()
{
  cout<<"Tetrimino Constructor Called!"<<endl;
  // Setup Initial Tetrimino and store it in Next Container (not visible yet)
  spawn( &nextTetrimino );
  spawn( &activeTetrimino );
  
  // TODO: add system to prevent the first active tetrimino and the first next tetrimino from being the same

}

Tetrimino::~Tetrimino()
{
  cout<<"Tetrimino Destructor Called!"<<endl;
  nextTetrimino.clear();
  activeTetrimino.clear();
}

bool Tetrimino::moveLeft(Board* myBoard)
{
  if ( getDimension( xMin, blocks ) > 0 && !myBoard->checkBlockCollision( this, left ) )
  {
    for ( int b = 0; b < 4; b++ )
    {
      activeTetrimino[b].box.x -= 1 * BLOCK_SIZE;
    }
    return true;
  }
  return false;
}

bool Tetrimino::moveRight(Board* myBoard)
{
  if ( getDimension( xMax, blocks ) < 9 && !myBoard->checkBlockCollision( this, right ) )
  {
    for ( int b = 0; b < 4; b++ )
    {
      activeTetrimino[b].box.x += 1 * BLOCK_SIZE;;
    }
    return true;
  }
  return false;
}

bool Tetrimino::moveDown(Board* myBoard)
{
  if ( getDimension( yMax, blocks ) < 19 && !myBoard->checkBlockCollision( this, down ) )
  {
    for ( int b = 0; b < 4; b++ )
    {
      activeTetrimino[b].box.y += 1 * BLOCK_SIZE;
    }
    return true;
  }
  return false;
}

void Tetrimino::hardDrop(Board* myBoard)
{
  // Move down until it can't anymore
  while(moveDown(myBoard));
}

void Tetrimino::next()
{
  activeTetrimino.clear();
  activeTetrimino = nextTetrimino;
  nextTetrimino.clear();
  spawn( &nextTetrimino);
}

void Tetrimino::spawn(std::vector<Block>* target)
{
  // randomize the Tetrimino chosen
  int rando = (random() % 7 + 1);
  
  cout<<"Tetrimino spawn type: "<<rando<<"\n";
  switch ( rando ) {
    case 1:   // I piece, blockType = 1 (cyan)
      target->push_back(Block(4, 0, 1));  // put the pivot block first
      target->push_back(Block(3, 0, 1));
      target->push_back(Block(5, 0, 1));
      target->push_back(Block(6, 0, 1));
      break;
    case 2:   // J piece, blockType = 2 (blue)
      target->push_back(Block(5, 0, 2));  // put the pivot block first
      target->push_back(Block(3, 0, 2));
      target->push_back(Block(4, 0, 2));
      target->push_back(Block(5, 1, 2));
      break;
    case 3:   // L piece, blockType = 3 (orange)
      target->push_back(Block(3, 0, 3));  // put the pivot block first
      target->push_back(Block(4, 0, 3));
      target->push_back(Block(5, 0, 3));
      target->push_back(Block(3, 1, 3));
      break;
    case 4:   // O piece, blockType = 4 (yellow)
      target->push_back(Block(4, 0, 4)); 
      target->push_back(Block(5, 0, 4));
      target->push_back(Block(4, 1, 4));
      target->push_back(Block(5, 1, 4));
      break;
    case 5:   // S piece, blockType = 5 (green)
      target->push_back(Block(4, 1, 5));
      target->push_back(Block(4, 0, 5));
      target->push_back(Block(5, 0, 5));
      target->push_back(Block(3, 1, 5));
      break;
    case 6:   // T piece, blockType = 6 (purple)
      target->push_back(Block(4, 1, 6));
      target->push_back(Block(4, 0, 6));
      target->push_back(Block(3, 1, 6));
      target->push_back(Block(5, 1, 6));
      break;
    case 7:   // Z piece, blockType = 7 (red)
      target->push_back(Block(4, 1, 7));
      target->push_back(Block(3, 0, 7));
      target->push_back(Block(4, 0, 7));
      target->push_back(Block(5, 1, 7));
      break;
  }
}

void Tetrimino::rotate(string dir)
{
  int pX, pY, translateX, translateY, originalX, originalY, rotatedX, rotatedY;
  double PI = 4.0*atan(1.0);
  
  if ( activeTetrimino[0].blockType != 4) // no need to rotate the O piece
  {
    // calculate pivot point based on rotate block (first block in vector)
    if ( activeTetrimino[0].blockType == 1 )   // If tetrinome is an I piece, handle it specially
    {
      pX = activeTetrimino[0].box.x;
      pY = activeTetrimino[0].box.y;
    }
    else    // Handle all other blocks
    {
      pX = activeTetrimino[0].box.x;
      pY = activeTetrimino[0].box.y;
      cout<<"Pivot X: "<<pX<<endl;
      cout<<"Pivot Y: "<<pY<<endl;
    }
  

    if( dir == "left" ){
      for ( int i = 0; i < 4; i++)
      {
        originalX = activeTetrimino[i].box.x;
        originalY = activeTetrimino[i].box.y;
        translateX = originalX - pX;
        translateY = originalY - pY;
      
        rotatedX = round(translateX * cos(PI/2) - translateY * sin(PI/2));
        rotatedY = round(translateX * sin(PI/2) - translateX * cos(PI/2));
      
        rotatedX += pX;
        rotatedY += pY;
        activeTetrimino[i].box.x = rotatedX;
        activeTetrimino[i].box.y = rotatedY;
      }
      cout<<"rotated X: "<<rotatedX<<endl;
      cout<<"rotated Y: "<<rotatedY<<endl;
    
    
    } else if ( dir == "right" ){
      for ( int i = 0; i < 4; i++)
      {
        originalX = activeTetrimino[i].box.x;
        originalY = activeTetrimino[i].box.y;
        translateX = originalX - pX;
        translateY = originalY - pY;
        
        rotatedX = round(translateX * cos(-PI/2) - translateY * sin(-PI/2));
        rotatedY = round(translateX * sin(-PI/2) - translateX * cos(-PI/2));
        
        rotatedX += pX;
        rotatedY += pY;
        activeTetrimino[i].box.x = rotatedX;
        activeTetrimino[i].box.y = rotatedY;
      }
      cout<<"rotated X: "<<rotatedX<<endl;
      cout<<"rotated Y: "<<rotatedY<<endl;
      
    }
  }
}

void Tetrimino::bubbleSort(vector <int> &num)
{
  int i, j, flag = 1;
  int temp;
  int numLength = num.size();
  for ( i = 1; ( i <= numLength ) && flag; i++ )
  {
    flag =0;
    for ( j = 0; j < numLength - 1; j++ )
    {
      if ( num[ j + 1 ] < num[ j ] )
      {
        temp = num[ j ];
        num[ j ] = num [ j + 1 ];
        num[ j + 1 ] = temp;
        flag = 1;;
      }
    }
  }
}

int Tetrimino::calcPixelWidth()
{
  vector <int> xValues;
  // get x values
  for ( int b = 0; b < 4; b++ )
  {
    xValues.push_back(activeTetrimino[b].box.x);
  }
  
  // sort in Descending Order
  bubbleSort( xValues );
  // return adjusted width (add 16 to the largest value)
  return ((xValues[3] + 16) - xValues[0]);

}

int Tetrimino::calcPixelHeight()
{
  vector <int> yValues;
  // get x values
  for ( int b = 0; b < 4; b++ )
  {
    yValues.push_back(activeTetrimino[b].box.y);
  }
  
  // sort in Descending Order
  bubbleSort(yValues);
  
  // return adjusted width (add 16 to the largest value)
  return ((yValues[3] + 16) - yValues[0]);
}

int Tetrimino::getDimension(int dimension, int unit)   // Calculate furthest position to the left on our board
{
  // store our values in vectors
  vector <int> xValues;
  vector <int> yValues;
  int returnValue = 0;

  for ( int b = 0; b < 4; b++ )   // for each block in the tetrimino, store the x and y in their respective vectors
  {
    xValues.push_back(activeTetrimino[b].box.x);
    yValues.push_back(activeTetrimino[b].box.y);
  }

  bubbleSort( xValues );
  bubbleSort( yValues );
  
  switch ( dimension )
  {
    case xMin:
      returnValue = xValues[0];
      break;
    case xMax:
      returnValue = xValues[3];
      break;
    case yMin:
      returnValue = yValues[0];
      break;
    case yMax:
      returnValue = yValues[3];
      break;
  }
  
  if ( unit == blocks ) { returnValue /= BLOCK_SIZE; }
  
  return (returnValue);
  
}

double Tetrimino::round( double number )
{
  return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}