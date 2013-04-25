//
//  Tetrimino.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "GameEngine.h"
#include "Tetrimino.h"
#include "Board.h"
#include "Block.h"


Tetrimino::Tetrimino(bool fill, int type)
{
  //cout<<"Tetrimino Constructor Called!"<<endl;
  // Setup Initial Tetrimino and store it in Next Container (not visible yet)
  if (fill) spawn(type);    // only fill the pieces if bool fill = true
  // TODO: add system to prevent the first active tetrimino and the first next tetrimino from being the same
  rotationsLeft = 0;
  rotationsRight = 0;
}

Tetrimino::~Tetrimino()
{
  //cout<<"Tetrimino Destructor Called!"<<endl;
  pieces.clear();
}

bool Tetrimino::moveLeft(Board* myBoard)
{
  if ( getDimension( xMin, blocks ) > 0 && !myBoard->checkMoveCollision( this, left ) )
  {
    for ( int b = 0; b < 4; b++ )
    {
      pieces[b].box.x -= 1 * BLOCK_SIZE;
    }
    Locator::getAudio()->playSound("Tetris.app/Contents/Resources/audio/tmove.wav", 25);
    return true;
  }
  return false;
}

bool Tetrimino::moveRight(Board* myBoard)
{
  if ( getDimension( xMax, blocks ) < 9 && !myBoard->checkMoveCollision( this, right ) )
  {
    for ( int b = 0; b < 4; b++ )
    {
      pieces[b].box.x += 1 * BLOCK_SIZE;;
    }
    Locator::getAudio()->playSound("Tetris.app/Contents/Resources/audio/tmove.wav", 25);
    return true;
  }
  return false;
}

bool Tetrimino::moveDown(Board* myBoard, bool gravity)
{
  if ( getDimension( yMax, blocks ) < 21 && !myBoard->checkMoveCollision( this, down ) )
  {
    for ( int b = 0; b < 4; b++ )
    {
      pieces[b].box.y += 1 * BLOCK_SIZE;
    }
    if ( gravity == false) Locator::getAudio()->playSound("Tetris.app/Contents/Resources/audio/tmove.wav", 25);
    return true;
  }
  return false;
}

void Tetrimino::hardDrop(Board* myBoard, int& score )
{
  // Move down until it can't anymore
  while(moveDown(myBoard, true)) score += 2;  // HardDrops are worth ( number of lines they dropped * 2 ) points
  Locator::getAudio()->playSound("Tetris.app/Contents/Resources/audio/harddrop.wav", 75);
}

void Tetrimino::spawn(int type)
{
  
  //cout<<"Tetrimino spawn type: "<<type<<"\n";
  switch ( type ) {
    case 1:   // I piece, blockType = 1 (cyan)
      pieces.push_back(Block(4, 2, 1));  // put the pivot block first
      pieces.push_back(Block(3, 2, 1));
      pieces.push_back(Block(5, 2, 1));
      pieces.push_back(Block(6, 2, 1));
      pieceOrigins = pieces;
      break;
    case 2:   // J piece, blockType = 2 (blue)
      pieces.push_back(Block(4, 3, 2));  // put the pivot block first
      pieces.push_back(Block(3, 3, 2));  
      pieces.push_back(Block(3, 2, 2));
      pieces.push_back(Block(5, 3, 2));
      pieceOrigins = pieces;
      break;
    case 3:   // L piece, blockType = 3 (orange)
      pieces.push_back(Block(4, 3, 3)); // put the pivot block first
      pieces.push_back(Block(5, 3, 3));  
      pieces.push_back(Block(5, 2, 3));
      pieces.push_back(Block(3, 3, 3));
      pieceOrigins = pieces;
      break;
    case 4:   // O piece, blockType = 4 (yellow)
      pieces.push_back(Block(4, 2, 4));
      pieces.push_back(Block(5, 2, 4));
      pieces.push_back(Block(4, 3, 4));
      pieces.push_back(Block(5, 3, 4));
      pieceOrigins = pieces;
      break;
    case 5:   // S piece, blockType = 5 (green)
      pieces.push_back(Block(4, 3, 5));
      pieces.push_back(Block(4, 2, 5));
      pieces.push_back(Block(5, 2, 5));
      pieces.push_back(Block(3, 3, 5));
      pieceOrigins = pieces;
      break;
    case 6:   // T piece, blockType = 6 (purple)
      pieces.push_back(Block(4, 3, 6));
      pieces.push_back(Block(4, 2, 6));
      pieces.push_back(Block(3, 3, 6));
      pieces.push_back(Block(5, 3, 6));
      pieceOrigins = pieces;
      break;
    case 7:   // Z piece, blockType = 7 (red)
      pieces.push_back(Block(4, 3, 7));
      pieces.push_back(Block(3, 2, 7));
      pieces.push_back(Block(4, 2, 7));
      pieces.push_back(Block(5, 3, 7));
      pieceOrigins = pieces;
      break;
  }
}

void Tetrimino::rotate(int direction, Board* myBoard)
{
  int pX, pY, translateX, translateY, originalX, originalY, rotatedX, rotatedY;
  double PI = 4.0*atan(1.0);
  bool rotationFailed = false; // create a flag for testing rotate collision
  
  std::vector<Block> rPieces;
  
  if ( pieces[0].blockType != 4) // no need to rotate the O piece
  {
    // calculate pivot point based on rotate block (first block in vector)
    if ( pieces[0].blockType == 1 )   // If tetrinome is an I piece, handle it specially
    {
      pX = pieces[0].box.x;
      pY = pieces[0].box.y;
    }
    else    // Handle all other blocks
    {
      pX = pieces[0].box.x;
      pY = pieces[0].box.y;
      // cout<<"Pivot X: "<<pX<<endl;
      // cout<<"Pivot Y: "<<pY<<endl;
    }
  

    if( direction == right ){
      for ( int i = 0; i < 4; i++)
      {
        originalX = pieces[i].box.x;
        originalY = pieces[i].box.y;
        translateX = originalX - pX;
        translateY = originalY - pY;
      
        rotatedX = Maths::round(translateX * cos(PI/2) - translateY * sin(PI/2));
        rotatedY = Maths::round(translateX * sin(PI/2) - translateX * cos(PI/2));
      
        rotatedX += pX;
        rotatedY += pY;
        
        rPieces.push_back(Block(rotatedX / 16, rotatedY / 16, pieces[i].blockType));
      }
    
      
    } else if ( direction == left ){
      for ( int i = 0; i < 4; i++)
      {
        originalX = pieces[i].box.x;
        originalY = pieces[i].box.y;
        translateX = originalX - pX;
        translateY = originalY - pY;
        
        rotatedX = Maths::round(translateX * cos(-PI/2) - translateY * sin(-PI/2));
        rotatedY = Maths::round(translateX * sin(-PI/2) - translateX * cos(-PI/2));
        
        rotatedX += pX;
        rotatedY += pY;
        
        rPieces.push_back(Block(rotatedX / 16, rotatedY / 16, pieces[i].blockType));
  
      }
    }
    
    // check if any of the blocks in their rotated form would cause collision
    for ( int i = 0; i < rPieces.size(); i++ )
    {
      if ( myBoard->checkBlockCollision( rPieces[i] ) )
      {
        rotationFailed = true;
      }
    }
    
    // as long as the rotation didn't fail due to collision detection, update the tetrimino pieces with the rotated pieces data
    if ( rotationFailed == false )
    {
      for ( int i = 0; i < pieces.size(); i++ )
      {
        pieces[i].box.x = rPieces[i].box.x;
        pieces[i].box.y = rPieces[i].box.y;
      }
      
      Locator::getAudio()->playSound("Tetris.app/Contents/Resources/audio/trotate.wav", 50);
      if (direction == right ) rotationsRight++;
      if (direction == left ) rotationsLeft++;
      
    }
    // if the rotation did fail then check if there are any suitable wall kick positions
    else
    {
      // attempt a wallkick
      if ( wallKick( rPieces, myBoard, direction ) )
      {
        cout<<"applying Kick!!"<<endl;
        for ( int i = 0; i < pieces.size(); i++ )
        {
          pieces[i].box.x = rPieces[i].box.x;
          pieces[i].box.y = rPieces[i].box.y;
        }
        
        if (direction == right ) rotationsRight++;
        if (direction == left ) rotationsLeft++;
        Locator::getAudio()->playSound("Tetris.app/Contents/Resources/audio/trotate.wav", 50);
      }
    }
    // clear the rPieces vector so it can be used again
    rPieces.clear();
    
  }
}

int Tetrimino::getCurrentRotationState()
{
  //cout<<"rotationsRight: "<<rotationsRight<<" rotationsLeft: "<<rotationsLeft<<" curState: "<< (rotationsRight - rotationsLeft ) % 4 << endl;
  return ( rotationsRight - rotationsLeft ) % 4;
}

bool Tetrimino::wallKickTest( int stateTransition, std::vector<Block>& rPieces, Board* myBoard, bool isI )
{
  bool failed = false;
  
  if ( isI == true )  // if we are testing kicks for I
  {
    
    for ( int i = 0; i < 4; i++ ) // for each test
    {
      //cout<<"testing wallKickTestsI["<<stateTransition<<"]["<<i<<"]: "<< wallKickTestsI[stateTransition][i].x <<","<< wallKickTestsI[stateTransition][i].y <<endl;
      failed = false;
      // create testPiece based on rPieces
      for ( int b = 0; b < 4; b++ )
      {
        if ( myBoard->checkBlockCollision( Block( ( rPieces[b].box.x / 16 ) + ( wallKickTestsI[stateTransition][i].x), ( rPieces[b].box.y / 16 ) + ( wallKickTestsI[stateTransition][i].y), rPieces[b].blockType ) ) )
        {
          failed = true;
        }
      }
      
      if ( failed == false )
      {
        // this test fully passed, return true
        for ( int b = 0; b < 4; b++ )
        {
          rPieces[b].box.x += ( wallKickTestsI[stateTransition][i].x * 16 );
          rPieces[b].box.y += ( wallKickTestsI[stateTransition][i].y * 16 );
        }
        cout<<"Found a suitable wall kick!"<<endl;
        return true;
      }
    }
    
    
  }
  else
  {    // if we are testing kicks for any piece other than I
  
  
    for ( int i = 0; i < 4; i++ ) // for each test
    {
      //cout<<"testing wallKickTests["<<stateTransition<<"]["<<i<<"]: "<< wallKickTests[stateTransition][i].x <<","<< wallKickTests[stateTransition][i].y <<endl;
      failed = false;
      // create testPiece based on rPieces
      for ( int b = 0; b < 4; b++ )
      {
        if ( myBoard->checkBlockCollision( Block( ( rPieces[b].box.x / 16 ) + ( wallKickTests[stateTransition][i].x), ( rPieces[b].box.y / 16 ) + ( wallKickTests[stateTransition][i].y), rPieces[b].blockType ) ) )
        {
          failed = true;
        }
      }
      
      if ( failed == false )
      {
        // this test fully passed, return true
        for ( int b = 0; b < 4; b++ )
        {
          rPieces[b].box.x += ( wallKickTests[stateTransition][i].x * 16 );
          rPieces[b].box.y += ( wallKickTests[stateTransition][i].y * 16 );
        }
        cout<<"Found a suitable wall kick!"<<endl;
        return true;
      }
    }
    
  }
  
return false;
}


bool Tetrimino::wallKick( std::vector<Block>& rPieces, Board* myBoard, int direction )
{
  int curState = getCurrentRotationState();
  
  switch ( direction )
  {
    
    case right:
      switch ( curState )
      {
      case 0:   // 0->R
          if ( wallKickTest( 0, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
          break;
      case 1:   // R->2
          if ( wallKickTest( 2, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
          break;
      case 2:   // 2->L
          if ( wallKickTest( 4, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
          break;
      case 3:   // L->0
          if ( wallKickTest( 6, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
          break;
      }
      break;
    
    case left:
      switch ( curState )
      {
      case 0:   // 0->L
         if ( wallKickTest( 7, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
        break;
      case 1:   // L->2
         if ( wallKickTest( 5, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
        break;
      case 2:   // 2->R
        if ( wallKickTest( 3, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
        break;
      case 3:   // R->0
        if ( wallKickTest( 1, rPieces, myBoard, (rPieces[0].blockType == 1) ) ) return true;
        break;
      }
    break;
    default:
      return false;
      break;
  }
}

void Tetrimino::resetPosition(){
  pieces.clear();
  pieces = pieceOrigins;
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

int Tetrimino::getPixelWidth()
{
  if ( pieces.size() == 0 ) return 0;
  
  vector <int> xValues;
  // get x values
  for ( int b = 0; b < 4; b++ )
  {
    xValues.push_back(pieceOrigins[b].box.x);
  }
  
  // sort in Descending Order
  bubbleSort( xValues );
  // return adjusted width (add 16 to the largest value)
  return ( ( xValues.back() + 16 ) - xValues.front() );

}

int Tetrimino::getPixelHeight()
{
  if ( pieces.size() == 0 ) return 0;
  
  vector <int> yValues;
  // get y values
  for ( int b = 0; b < 4; b++ )
  {
    yValues.push_back(pieceOrigins[b].box.y);
  }
  
  // sort in Descending Order
  bubbleSort(yValues);
  
  // return adjusted width (add 16 to the largest value)
  return ((yValues.back() + 16) - yValues.front());
}

int Tetrimino::getDimension(int dimension, int unit)   // Calculate furthest position to the left on our board
{
  // store our values in vectors
  vector <int> xValues;
  vector <int> yValues;
  int returnValue = 0;

  for ( int b = 0; b < 4; b++ )   // for each block in the tetrimino, store the x and y in their respective vectors
  {
    xValues.push_back(pieces[b].box.x);
    yValues.push_back(pieces[b].box.y);
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