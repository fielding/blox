//
//  NullAudio.h
//  Tetris
//
//  Created by Fielding Johnston on 4/9/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef Tetris_NullAudio_h
#define Tetris_NullAudio_h

#include "IAudio.h"

class NullAudio : public IAudio
{
public:
  
  virtual ~NullAudio() {}
  virtual void playSound( std::string filename, int volume = 100, int looping = 0 )   { /* Do nothing */}
  virtual void playMusic( std::string filename, int volume = 100, int looping = 0 )   { /* Do nothing */}
  
  virtual void stopAllSounds()                                                        { /* Do nothing */}
  virtual void stopMusic()                                                            { /* Do nothing */}
  virtual void stopEverything()                                                       { /* Do nothing */}
  
  virtual void setMusicVolume ( int volAsPercent )                                    { /* Do nothing */}
  virtual int  getMusicVolume ( )                                                     { /* Do nothing */}
  
  virtual void setChannelVolume ( int channel, int volAsPercent )                     { /* Do nothing */}
  virtual int  getChannelVolume ( int channel )                                       { /* Do nothing */}
  
  virtual void toggleMusic ( )                                                        { /* Do nothing */}
  
  virtual bool isSoundPlaying( std::string filename )                                 { /* Do nothing */}
  virtual bool isMusicPlaying()                                                       { /* Do nothing */}
  
  virtual bool isMusicPaused()                                                        { /* Do nothing */}
};


#endif
