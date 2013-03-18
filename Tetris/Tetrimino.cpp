//
//  Tetrimino.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "Tetrimino.h"


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

void Tetrimino::spawn(std::vector<Block>* target){
  // randomize the Tetrimino chosen
  int rando = (random() % 7 + 1);
  
  cout<<"Tetrimino spawn type: "<<rando<<"\n";
  switch ( rando ) {
    case 1:   // I piece, blockType = 1 (cyan)
      target->push_back(Block(0, 0, 1));
      target->push_back(Block(1, 0, 1));
      target->push_back(Block(2, 0, 1));
      target->push_back(Block(3, 0, 1));
      break;
    case 2:   // J piece, blockType = 2 (blue)
      target->push_back(Block(0, 0, 2));
      target->push_back(Block(1, 0, 2));
      target->push_back(Block(2, 0, 2));
      target->push_back(Block(2, 1, 2));
      break;
    case 3:   // L piece, blockType = 3 (orange)
      target->push_back(Block(0, 0, 3));
      target->push_back(Block(1, 0, 3));
      target->push_back(Block(2, 0, 3));
      target->push_back(Block(0, 1, 3));
      break;
    case 4:   // O piece, blockType = 4 (yellow)
      target->push_back(Block(1, 0, 4));
      target->push_back(Block(2, 0, 4));
      target->push_back(Block(1, 1, 4));
      target->push_back(Block(2, 1, 4));
      break;
    case 5:   // S piece, blockType = 5 (green)
      target->push_back(Block(1, 0, 5));
      target->push_back(Block(2, 0, 5));
      target->push_back(Block(0, 1, 5));
      target->push_back(Block(1, 1, 5));
      break;
    case 6:   // T piece, blockType = 6 (purple)
      target->push_back(Block(1, 0, 6));
      target->push_back(Block(0, 1, 6));
      target->push_back(Block(1, 1, 6));
      target->push_back(Block(2, 1, 6));
      break;
    case 7:   // Z piece, blockType = 7 (red)
      target->push_back(Block(0, 0, 7));
      target->push_back(Block(1, 0, 7));
      target->push_back(Block(1, 1, 7));
      target->push_back(Block(2, 1, 7));
      break;
  }
}