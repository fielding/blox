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
  
  void playSound ( std::string filename, int channel = -1, int looping = 0 );
  void playSong ( std::string filename, int looping = 0 );
  void stopAllSounds ( );

  void setMusicVolume ( int volAsPercent );  // set the music volume by percent
  int  getMusicVolume ( ); // return the current music volume as a percent
  
  void setChannelVolume ( int channel, int volAsPercent );  // set the sound volume by percent
  int  getChannelVolume ( int channel ); // return the current sound volume as a percent
  
  void toggleMusic ( );   // returns true or false based on if the music was currently playing ( true if it was, false if it was muted );
  
  bool isSongPlaying ( );
  bool isSoundPlaying ( );
  
  bool isSongPaused ( );
  bool isSoundPaused ( );

  
private:
  Mix_Chunk *sound;
  Mix_Music *music;
};

#endif /* defined(__Tetris__SDLAudio__) */
