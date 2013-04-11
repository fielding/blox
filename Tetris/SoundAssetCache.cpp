//
//  SoundAssetCache.cpp
//  Tetris
//
//  Created by Fielding Johnston on 4/9/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "SoundAssetCache.h"

SoundAssetCache::SoundAssetCache(void) {}

SoundAssetCache::~SoundAssetCache(void)
{
  std::for_each(sounds.begin(), sounds.end(), Deallocator<Mix_Chunk*>() );
  std::for_each(music.begin(), music.end(), Deallocator<Mix_Music*>() );
}

Mix_Chunk* SoundAssetCache::getSound(std::string filename) const
{
  std::map< std::string, Mix_Chunk* >::iterator itr = sounds.find(filename);
  Mix_Chunk* sound;
  
  if ( itr == sounds.end() )
  {
    sound = Mix_LoadWAV( filename.c_str() );
    if ( sound == NULL )
    {
      Mix_FreeChunk(sound);
      throw SoundNotFoundException( filename + " was not found in call to SoundAssetCache::getSound" );
    }
    
    std::map< std::string,Mix_Chunk* >::iterator res = sounds.insert(std::pair< std::string,Mix_Chunk* >(filename, sound)).first;
    return sound;
  }
  else
  {
    return itr->second;
  }
  
  throw SoundNotFoundException( filename + " was not found in call to SoundAssetCache::getSound" );
}

Mix_Music* SoundAssetCache::getMusic( std::string filename ) const
{
  std::map< std::string, Mix_Music* >::iterator itr = this->music.find( filename );
  if ( itr == this->music.end() )
  {
    
    Mix_Music* music;
    music = Mix_LoadMUS( filename.c_str() );
    
    if ( music == NULL )
    {
      Mix_FreeMusic(music);
      throw SoundNotFoundException( filename + " was not found in call to SoundAssetCache::getMusic" );
    }
    else
    {
      std::map< std::string, Mix_Music* >::iterator res = this->music.insert( std::pair< std::string, Mix_Music* >( filename, music ) ).first;
      return res->second;
    }
  
  }
  else
  {
    return itr->second;
  }
  
  throw SoundNotFoundException( filename + " was not found in call to SoundAssetCache::getMusic" );
  
}

std::map< std::string, Mix_Chunk* > SoundAssetCache::sounds;
std::map< std::string, Mix_Music* > SoundAssetCache::music;
