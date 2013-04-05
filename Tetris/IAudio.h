//
//  iAudio.h
//  Tetris
//
//  Created by Fielding Johnston on 3/31/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef Tetris_iAudio_h
#define Tetris_iAudio_h

#include <string>

class IAudio
{
public:
  virtual ~IAudio() {}
  virtual void playSound( std::string filename, int channel = -1, int looping = 0 ) = 0;
  virtual void playSong( std::string filename, int looping ) = 0;
  
  virtual void stopAllSounds() = 0;
  virtual void stopMusic() = 0;
  
  virtual void setMusicVolume ( int volAsPercent ) = 0;
  virtual int  getMusicVolume ( ) = 0;
  
  virtual void setChannelVolume ( int channel, int volAsPercent ) = 0;
  virtual int  getChannelVolume ( int channel ) = 0;
  
  virtual void toggleMusic ( ) = 0;
  
  virtual bool isSongPlaying() = 0;
  virtual bool isSoundPlaying() = 0;

  virtual bool isSongPaused() = 0;
  virtual bool isSoundPaused() = 0;

};

#endif
