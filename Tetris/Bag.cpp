//
//  Bag.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/23/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "Bag.h"

Bag::Bag(){   // Constructor
  create();
  shuffle();
  std::cout<<"Bag Constructor called!"<<std::endl;
}

Bag::~Bag(){  // Destructor
  content.clear();
  std::cout<<"Bag Destructor called!"<<std::endl;
}

void Bag::listContent()
{
  for ( int i = 0; i <= 6; i++ )
  {
    std::cout<<content[i];
  }
  std::cout<<std::endl;
}

int Bag::getNextPiece()   // returns int representation of tetrimino
{
  int piece;
  
  if ( content.empty() ) refill();    // if the bag is empty, refill
  
  piece = content.back();
  content.pop_back();
  
  return piece;
}

void Bag::create()
{
  for ( int i = 1; i <= 7; i++ )
  {
    content.push_back(i);
  }
}

void Bag::shuffle()
{
  for ( int i = 7; i > 0; i-- )
  {
    int swapIndex = rand() % 7;         // get a random number to use as the index of the number to swap with
    int buffer = content[i-1];          // store current number in a buffer
    content[i-1] = content[swapIndex];  // replace current position with randomly chose position
    content[swapIndex] = buffer;        // move original to the place of the random index
  }
}

void Bag::refill()
{
  create();
  shuffle();
}