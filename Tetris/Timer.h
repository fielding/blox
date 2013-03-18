//
//  Timer.h
//  Tetris
//
//  Created by Fielding Johnston on 3/15/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Timer__
#define __Tetris__Timer__

#include <iostream>
#include "SDL.h"

class Timer
{
  
public:
  // Constructor, Initializes variables
  Timer();
  
  // Various clock functions
  void start();
  void stop();
  void pause();
  void unpause();
  
  // Get timer's time in milliseconds
  int get_ticks();
  
  // Check timer's status, returns true or false
  bool is_started();
  bool is_paused();
  
private:
  // The clock when the timer started
  int startTicks;
  
  // The ticks stored when the timer was paused
  int pausedTicks;
  
  // Timer status
  bool paused;
  bool started;
  
};

#endif /* defined(__Tetris__Timer__) */

