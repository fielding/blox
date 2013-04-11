//
//  iAudio.h
//  Tetris
//
//  Created by Fielding Johnston on 3/31/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef Tetris_iAudio_h
#define Tetris_iAudio_h

class IAudio
{
public:
  virtual ~IAudio() {}
  virtual void playSound( std::string filename, int volume = 100, int looping = 0 ) = 0;  // play a sound, at specified volume as a percent (default: 100) and loop specified amount of times (-1 infinite, otherwise integer is litera; default: 0)
  virtual void playMusic( std::string filename, int volume = 100, int looping = 0 ) = 0;
  
  virtual void stopAllSounds() = 0;
  virtual void stopMusic() = 0;
  virtual void stopEverything() = 0;
  
  // add public getter and setters for SoundVolume
  // virtual void setSoundVolume ( std::string filename, volAsPercent ) = 0;
  // virtual int  getSoundVolume ( std::string filename ) = 0;
  
  //virtual void setMusicVolume ( int volAsPercent ) = 0;
  //virtual int  getMusicVolume ( ) = 0;
  
  virtual void setChannelVolume ( int channel, int volAsPercent ) = 0;
  virtual int  getChannelVolume ( int channel ) = 0;
  
  virtual void toggleMusic ( ) = 0;
  
  virtual bool isSoundPlaying( std::string filename ) = 0;
  virtual bool isMusicPlaying() = 0;

  virtual bool isMusicPaused() = 0;

};

#endif
