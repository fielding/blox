//
//  Audio.h
//  Tetris
//
//  Based on Jeffrey Carpenter's audio.h
//  Created by Fielding Johnston on 3/31/13.
//

#ifndef __Tetris__Audio__
#define __Tetris__Audio__

#include <iostream>

#include "SDL.h"
#include "SDL_mixer.h"

class Audio {
public:
  Audio();  // Constructor
  ~Audio(); // Destructor

  bool Init();
  
  bool LoadSoundTrack( std::string filename );
  bool PlaySoundTrack();
  void SetSoundLooping( signed int loops );

  bool LoadMusicTrack( std::string filename );
  bool PlayMusicTrack();
  void SetMusicLooping( signed int loops );
  
  bool toggleMusic();

private:
  unsigned int audio_rate;
  Uint16 audio_format;
  unsigned int audio_channels;
  unsigned int audio_buffers;

  // -1 for infinity
  signed int aTrack_loops;
  signed int mTrack_loops;

  Mix_Chunk *aTrack;
  Mix_Music *mTrack;
};



#endif /* defined(__Tetris__Audio__) */
