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
#include "SoundAssetCache.h"

class SDLAudio : public IAudio
{
public:
  SDLAudio();
  ~SDLAudio();
  
  void playSound ( std::string filename, int volume = 100, int looping = 0 ); // play a sound, at specified volume as a percent (default: 100) and loop specified amount of times (-1 infinite, otherwise integer is literal; default: 0)
  void playMusic ( std::string filename, int volume = 100, int looping = 0 ); // play music, at specified volume as a percent (default: 100) and loop specified amount of times (-1 infinite, otherweise integer is literal; default: 0)
  
  void stopAllSounds ( );
  void stopMusic ( );
  void stopEverything ( );
  
  // ADD public function for getting and setting the volume of a sound using the filename
  // virtual void setSoundVolume ( std::string filename, volAsPercent );
  // virtual int  getSoundVolume ( std::string filename );
  
  // ADD public function for getting and setting the volume of music using the filename
  // virtual void getMusicVolume ( std::string filename, volAsPercent);
  // virtual int setMusicVolume ( std::string filename );
  
  void setChannelVolume ( int channel, int volAsPercent );  // set the sound volume by percent
  int  getChannelVolume ( int channel ); // return the current sound volume as a percent
  
  void toggleMusic ( );   // returns true or false based on if the music was currently playing ( true if it was, false if it was muted );
  
  bool isSoundPlaying ( std::string filename );
  bool isMusicPlaying ( );

  bool isMusicPaused ( );
  
  static void soundFinished( int channel );
  
private:
  static const int MAX_SOUND_CHANNELS = 8;  // this will raise the amount of channels allocated by SDL. This only effects how many sounds can be played at the same time.
  
  void setSoundVolume ( Mix_Chunk* sound, int volAsPercent ); // set the sound volume by percent
  int  getSoundVolume ( Mix_Chunk* sound ); // get the sound volume by percent
  
  void setMusicVolume ( int volAsPercent );  // set the music volume by percent
  int  getMusicVolume ( ); // return the current music volume as a percent
  
  SoundAssetCache soundAssetCache;
  Mix_Chunk* currentSounds[MAX_SOUND_CHANNELS];  // create an array the size of the number of chunk channels sdl_mixer has provided (8)
  std::string currentMusicName;
};

#endif /* defined(__Tetris__SDLAudio__) */
