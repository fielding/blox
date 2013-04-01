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
    std::cout << "ERR: " << Mix_GetError << std::endl;
  }

}

SDLAudio::~SDLAudio()
{
  Mix_FreeChunk( sound );
  Mix_HaltMusic();
  Mix_FreeMusic( music );
  Mix_CloseAudio();
}

void SDLAudio::playSound( std::string filename, int looping )
{
  sound = Mix_LoadWAV ( filename.c_str() );
  Mix_PlayChannel( -1, sound, looping);
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

void SDLAudio::setMusicVolume(int volAsPercent)
{
  
  Mix_VolumeMusic( ceil(MIX_MAX_VOLUME * ( volAsPercent / 100.f )) );  // set the music volume based on the percent passed to the method
}

int SDLAudio::getMusicVolume()
{
  
  return floor( ( Mix_VolumeMusic(-1) / 128.f ) * 100 );    // return the current music volume as a percent
}

bool SDLAudio::isSoundPlaying()
{
  return true;
}

bool SDLAudio::isSongPlaying()
{
  return true;
}