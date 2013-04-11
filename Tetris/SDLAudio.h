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
#include "AssetCache.h"

class SDLAudio : public IAudio
{
public:
  SDLAudio();   // Constructor
  ~SDLAudio();  // Destructor
  
  void playSound ( std::string filename, int volume = -1, int looping = 0 );      // play a sound, at specified volume as a percent (default: uses the setting last set for the sound, or 100 if not changed since sound struct was constructed )
                                                                                  // and loop specified amount of times (-1 infinite, otherwise integer is literal; default: 0)
  void playMusic ( std::string filename, int volume = -1, int looping = 0 );      // play music, at specified volume as a percent (default: uses the setting last set for the sound, or 100 if not changed since sound struct was constructed )
                                                                                  // and loop specified amount of times (-1 infinite, otherweise integer is literal; default: 0)
  
  
  void stopAllSounds ( );       // Stop all sounds being played on any channel (does not stop the music)
  void stopMusic ( );           // Stop just the music that is currently playing (does not stop any sounds)
  void stopEverything ( );      // Stops both sound and music being played.

  void setSoundVolume ( std::string filename, int volAsPercent );     // Public version of setSoundVolume that takes filename as parameter and the volume as a percent
  int  getSoundVolume ( std::string filename );                       // Public version of getSoundVolume that takes filename as parameter and returns the volume as a percent
  
  void setMusicVolume ( int volAsPercent );     // set the music volume by percent
  int  getMusicVolume ( );                      // return the current music volume as a percent
  
  void setChannelVolume ( int channel, int volAsPercent );      // set the sound volume by percent
  int  getChannelVolume ( int channel );                        // return the current sound volume as a percent
  
  void toggleMusic ( );     // returns true or false based on if the music was currently playing ( true if it was, false if it was muted );
  
  bool isSoundPlaying ( std::string filename );     // Checks if a sound is playing based on it's filename
  bool isMusicPlaying ( );                          // Checks to see if music is playing

  bool isMusicPaused ( );                           // Checks to see if the music is currently paused.
  
private:
  static const int MAX_SOUND_CHANNELS = 8;      // this will raise the amount of channels allocated by SDL. This only effects how many sounds can be played at the same time.
  
  void setSoundVolume ( Mix_Chunk* sound, int volAsPercent );     // Private version of setSoundVolume that takes a pointer to the sound struct as parameter and the volume as a percent
  int  getSoundVolume ( Mix_Chunk* sound );                       // Private version of getSoundVolume that takes a pointer to the sound struct as parameter and returns the volume as a percent
  
  AssetCache assetCache;                  // instance of the AssetCache
  Mix_Chunk* currentSounds[MAX_SOUND_CHANNELS];     // create an array the size of the number of chunk channels sdl_mixer has provided (8)
  std::string currentMusicName;                     // string that the filename of current music is stored in
};

#endif /* defined(__Tetris__SDLAudio__) */
