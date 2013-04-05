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

SDLAudio::SDLAudio()
{
  
  if ( Mix_OpenAudio( 22050, AUDIO_S16, 2, 4096) == -1 )
  {
    std::cerr << "ERR: " << Mix_GetError << std::endl;
  }

}

SDLAudio::~SDLAudio()
{
  Mix_HaltMusic();  // to be safe
  Mix_FreeMusic( music );
  Mix_CloseAudio();
}

void SDLAudio::playSound( std::string filename, int channel, int looping )
{
  sound = Mix_LoadWAV ( filename.c_str() );

  if ( sound == NULL ) std::cerr <<"Failed to load "<<filename.c_str()<<std::endl;
  
  Mix_PlayChannel( channel, sound, looping);
  
  Mix_ChannelFinished(soundFinished);
  
}

void SDLAudio::soundFinished( int channel )
{
  Mix_FreeChunk( Mix_GetChunk( channel ) );
}

void SDLAudio::playSong(std::string filename, int looping )
{
  music = Mix_LoadMUS( filename.c_str() );
  
  if ( music == NULL ) std::cout<<"Failed to load "<<filename.c_str()<<std::endl;
  
  Mix_PlayMusic( music, looping );
}

void SDLAudio::stopAllSounds()
{
  
}

void SDLAudio::stopMusic()
{
  Mix_HaltMusic();  // to be safe
  Mix_FreeMusic( music ); // this should call Mix_HaltMusic for us
}


void SDLAudio::setMusicVolume(int volAsPercent)
{
  
  Mix_VolumeMusic( ceil(MIX_MAX_VOLUME * ( volAsPercent / 100.f )) );  // set the music volume based on the percent passed to the method
}

int SDLAudio::getMusicVolume()
{
  
  return floor( ( Mix_VolumeMusic(-1) / 128.f ) * 100 );    // return the current music volume as a percent
}

void SDLAudio::setChannelVolume(int channel, int volAsPercent)
{
  
  Mix_Volume(channel, ceil( MIX_MAX_VOLUME * ( volAsPercent / 100.f )) );  // set the music volume based on the percent passed to the method
}

int SDLAudio::getChannelVolume(int channel)
{
  
  return floor( ( Mix_Volume(channel, -1 ) / 128.f ) * 100 );    // return the current music volume as a percent
}

bool SDLAudio::isSongPlaying()
{
  if ( Mix_PlayingMusic() ) return true;
  
  return false;
}

bool SDLAudio::isSoundPlaying()
{
  return true;
}

bool SDLAudio::isSongPaused()
{
  if ( Mix_PausedMusic() == 1 ) return true;
  
  return false;
}

bool SDLAudio::isSoundPaused()
{
  return false;
}

void SDLAudio::toggleMusic()
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