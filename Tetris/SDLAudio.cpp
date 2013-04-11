//
//  File.cpp
//  Tetris
//
//  Created by Fielding Johnston on 4/1/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "SDLAudio.h"
#include "SoundAssetCache.h"

//
// Public Methods
//

SDLAudio::SDLAudio() : currentMusicName("")     // Constructor
{
  if ( Mix_OpenAudio( 44100, AUDIO_S16, 2, 4096) == -1 )
  {
    std::cerr << "ERROR: " << Mix_GetError << std::endl;
  }
  
  Mix_AllocateChannels(MAX_SOUND_CHANNELS);
}

SDLAudio::~SDLAudio()                           // Destructor
{
  stopEverything();
  Mix_CloseAudio();
}

void SDLAudio::playSound( std::string filename, int volume, int looping )     // Play a sound, at specified volume as a percent (default: uses the setting last set for the sound, or 100 if not changed since sound struct was constructed )
{                                                                           // and loop specified amount of times (-1 infinite, otherwise integer is literal; default: 0)

  
  int availChannel = -1;
  
  // let's find a channel that isn't currently playing anything
  for ( int i = 0; i < MAX_SOUND_CHANNELS; i++ )
  {
    if (Mix_Playing( i ) == 0 )
        {
          availChannel = i;
          break;
        }
  }
  
  // if we found a free channel (availChannel should be set to something other than -1)
  if ( availChannel != -1 )
  {
    try
    {
      currentSounds[availChannel] = soundAssetCache.getSound(filename);
      setSoundVolume( currentSounds[availChannel], volume );
      Mix_PlayChannel( availChannel, currentSounds[availChannel], 0 );
    }
    
    catch( SoundNotFoundException& ex)
    {
      // Error, file was not found
      std::cerr<<ex.what()<<std::endl;
    }
  }
  
}

void SDLAudio::playMusic( std::string filename, int volume, int looping )     // Play music, at specified volume as a percent (default: uses the setting last set for the sound, or 100 if not changed since sound struct was constructed )
{                                                                           // and loop specified amount of times (-1 infinite, otherweise integer is literal; default: 0)
  Mix_Music* current;
  
  // attempt to load the file in to the cache, or retrieve a pointer to it if it exists
  try
  {
    current = soundAssetCache.getMusic( filename );
  }
  catch( SoundNotFoundException& ex)
  {
    // We couldn't find the selected song, report that and then exit
    std::cerr<<ex.what()<<std::endl;
    return;
  }
  
  // See if a song is still playing, if so, stop it
  if (currentMusicName != "")
  {
    try
    {
      if ( Mix_PlayingMusic() == true )
      {
        std::cerr<<"Stopping the currently playing music"<<std::endl; // debugging REMOVE
        Mix_HaltMusic();
      }
    }
    catch( SoundNotFoundException& )
    {
      // Couldn't stop previous song
    }
    
  }
  
  // set currentMusicName to the name of the music that is now playing
  currentMusicName = filename;
  // play the song!
  Mix_PlayMusic(current, looping);

}

void SDLAudio::stopAllSounds()      // Stop all sounds being played on any channel (does not stop the music)
{
  for( int i = 0; i < MAX_SOUND_CHANNELS; i++ )
  {
    Mix_HaltChannel(i);
  }
}

void SDLAudio::stopMusic()          // Stop just the music that is currently playing (does not stop any sounds)
{
  Mix_HaltMusic();
}

void SDLAudio::stopEverything()     // Stops both sound and music being played.
{
  for( int i = 0; i < MAX_SOUND_CHANNELS; i++ )
  {
    Mix_HaltChannel(i);
  }
  
  Mix_HaltMusic();
}

void SDLAudio::setSoundVolume ( std::string filename, int volAsPercent )      // Public version of setSoundVolume that takes filename as parameter and the volume as a percent
{
  Mix_Chunk* sound = soundAssetCache.getSound( filename );
  setSoundVolume(sound, volAsPercent); // call the private version of this function using the pointer to the sound struct
}

int SDLAudio::getSoundVolume ( std::string filename )                         // Public version of getSoundVolume that takes filename as parameter and returns the volume as a percent
{
  Mix_Chunk* sound = soundAssetCache.getSound( filename );
  return getSoundVolume(sound);
}

void SDLAudio::setMusicVolume(int volAsPercent)     // Set the music volume by percent
{
  Mix_VolumeMusic( ceil( MIX_MAX_VOLUME * ( volAsPercent / 100.f ) ) );  // set the music volume based on the percent passed to the method
}

int SDLAudio::getMusicVolume()                      // Return the current music volume as a percent
{
  return floor( ( Mix_VolumeMusic(-1) / 128.f ) * 100 );    // return the current music volume as a percent
} 

void SDLAudio::setChannelVolume(int channel, int volAsPercent)            // set the sound volume by percent
{
  Mix_Volume(channel, ceil( MIX_MAX_VOLUME * ( volAsPercent / 100.f ) ) );  // set the music volume based on the percent passed to the method
}

int SDLAudio::getChannelVolume(int channel)                               // return the current sound volume as a percent
{
  return floor( ( Mix_Volume(channel, -1 ) / 128.f ) * 100 );    // return the current music volume as a percent
}

void SDLAudio::toggleMusic()      // returns true or false based on if the music was currently playing ( true if it was, false if it was muted );
{
  if ( Mix_PausedMusic() == 1 )
  {
    Mix_ResumeMusic();
  }
  else
  {
    Mix_PauseMusic();
  }
}

bool SDLAudio::isSoundPlaying( std::string filename )     // Checks if a sound is playing based on it's filename
{
  for ( int i = 0; i < MAX_SOUND_CHANNELS; i++ )
  {
    if ( soundAssetCache.getSound(filename) == currentSounds[i] )
    {
      if ( Mix_Playing( i ) )
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
  return false;
}

bool SDLAudio::isMusicPlaying()                           // Checks to see if music is playing
{
  if ( Mix_PlayingMusic() ) return true;
  
  return false;
}

bool SDLAudio::isMusicPaused()                            // Checks to see if the music is currently paused.
{
  if ( Mix_PausedMusic() == 1 ) return true;
  
  return false;
}

//
// Private Methods
//

void SDLAudio::setSoundVolume(Mix_Chunk* sound, int volAsPercent )      // Private version of setSoundVolume that takes a pointer to the sound struct as parameter and the volume as a percent
{
  Mix_VolumeChunk(sound, ceil( MIX_MAX_VOLUME * ( volAsPercent / 100.f) ) );
}

int SDLAudio::getSoundVolume( Mix_Chunk* sound)                         // Private version of getSoundVolume that takes a pointer to the sound struct as parameter and returns the volume as a percent
{
  return floor( ( Mix_VolumeChunk(sound, -1) / 128.f ) * 100 );   // return the current sound volume as a percent
}