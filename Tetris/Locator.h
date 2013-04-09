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
#include "NullAudio.h"

class Locator
{
public:
  static void initialize() { audioService = &nullService; }
  
  static IAudio* getAudio() { return audioService; }
  
  static void provide (IAudio* service)
  {
    if ( service == NULL )
    {
      // use null service
      audioService = &nullService;
    }
    else
    {
      audioService = service;
    }
  }

private:
  static IAudio* audioService;
  static NullAudio nullService;
  
};




#endif /* defined(__Tetris__Locator__) */
