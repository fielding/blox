//
//  File.cpp
//  Tetris
//
//  Created by Fielding Johnston on 4/1/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include <iostream>
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
  std::cout<<"Loading file: "<<filename.c_str()<<std::endl;
  
  music = Mix_LoadMUS( filename.c_str() );
  
  if ( music == NULL ) std::cout<<"Failed to load "<<filename.c_str()<<std::endl;
  
  Mix_PlayMusic( music, looping );
  
}

void SDLAudio::stopAllSounds()
{
  
}

bool SDLAudio::isSoundPlaying()
{
  return true;
}

bool SDLAudio::isSongPlaying()
{
  return true;
}