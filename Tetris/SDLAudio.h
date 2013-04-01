//
//  File.h
//  Tetris
//
//  Created by Fielding Johnston on 4/1/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__SDLAudio__
#define __Tetris__SDLAudio__

#include <iostream>

#include "IAudio.h"

#include "SDL.h"
#include "SDL_mixer.h"

class SDLAudio : public IAudio
{
public:
  SDLAudio();
  ~SDLAudio();
  
  void playSound ( std::string filename, int looping = 0 );
  void playSong ( std::string filename, int looping = 0 );
  void stopAllSounds ( );

  bool isSoundPlaying ( );
  bool isSongPlaying ( );

private:
  Mix_Chunk *sound;
  Mix_Music *music;
};

#endif /* defined(__Tetris__SDLAudio__) */
