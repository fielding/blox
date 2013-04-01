//
//  Locator.h
//  Tetris
//
//  Created by Fielding Johnston on 4/1/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Locator__
#define __Tetris__Locator__

#include <iostream>

#include "IAudio.h"

class Locator
{
public:
  static IAudio* getAudio() { return audioService; }
  
  static void provide (IAudio* service)
  {
    audioService = service;
  }

private:
  static IAudio* audioService;

};




#endif /* defined(__Tetris__Locator__) */
