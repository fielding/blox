//
//  SoundAssetCache.h
//  Tetris
//
//  Created by Fielding Johnston on 4/9/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__SoundAssetCache__
#define __Tetris__SoundAssetCache__

#include <iostream>
#include <map>

#include "SDL_mixer.h"

class SoundAssetCache
{
public:
  SoundAssetCache(void);
  ~SoundAssetCache(void);

  Mix_Chunk* getSound( std::string filename ) const;
  Mix_Music* getMusic( std::string filename ) const;

private:
  static std::map<std::string, Mix_Chunk*> sounds;
  static std::map<std::string, Mix_Music*> music;

  template <typename T>
    struct Deallocator{
      void operator()( const std::pair<std::string, T> &p )
      {
        delete p.second;
      }
    };

};

class SoundNotFoundException : public std::runtime_error
{
public:
  SoundNotFoundException(std::string const& msg): std::runtime_error(msg) {}
};

#endif /* defined(__Tetris__SoundAssetCache__) */
