//
//  Audio.cpp
//  Tetris
//
//  Based on Jeffrey Carpenter's audio.cpp
//  Created by Fielding Johnston on 3/31/13.
//

#include "OLDAudio.h"

Audio::Audio()
{
  this->audio_rate = 22050;
  this->audio_format = AUDIO_S16;
  
  this->audio_channels = 2;
  
  this->audio_buffers = 4096;
  this->aTrack_loops = 0;
  this->mTrack_loops = 0;
  this->aTrack = NULL;
  this->mTrack = NULL;
  
}

Audio::~Audio()
{
  Mix_FreeChunk( aTrack );
  
  Mix_HaltMusic();
  Mix_FreeMusic( mTrack );
  Mix_CloseAudio();
}

bool Audio::Init()
{
  if ( Mix_OpenAudio( audio_rate, audio_format, audio_channels, audio_buffers) == -1 )
  {
    std::cout << "ERR: " << Mix_GetError << std::endl;
    return false;
  }
  
  return true;
}

bool Audio::LoadSoundTrack( std::string filename )
{
  aTrack = Mix_LoadWAV ( filename.c_str() );
  return true;
}

bool Audio::PlaySoundTrack()
{
  Mix_PlayChannel( -1, aTrack, this->aTrack_loops);
  return true;
}

void Audio::SetSoundLooping( signed int loops )
{
  this->aTrack_loops = loops;
}

bool Audio::LoadMusicTrack( std::string filename )
{
  mTrack = Mix_LoadMUS ( filename.c_str() );
  return true;
}

bool Audio::PlayMusicTrack()
{
  Mix_PlayMusic( mTrack, this->mTrack_loops );
  return true;
}

void Audio::SetMusicLooping( signed int loops )
{
  this->mTrack_loops = loops;
}

bool Audio::toggleMusic()
{
  if ( Mix_PausedMusic() == 1 )
  {
    Mix_ResumeMusic();
  }
  else
  {
    Mix_PauseMusic();
  }
  return true;
}

