//
//  Bag.h
//  Tetris
//
//  Created by Fielding Johnston on 3/23/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Bag__
#define __Tetris__Bag__

#include <iostream>
#include <vector>

class Bag{

public:
  Bag();    // Constructor
  ~Bag();   // Destructor
  
  void listContent();   // list contents of bag (mainly used for debug)
  int getNextPiece();   // get next piece from bag and refill bag if needed; will feed the deque
  
private:
  void create();  // create initial ordered bag (needs to be shuffled)
  void shuffle(); // shuffle the bag
  void refill();  // refill bag when it runs out with a newly shuffled set of 7 pieces
  
  std::vector<int> content;   // vector to store pieces in
  
};


#endif /* defined(__Tetris__Bag__) */
