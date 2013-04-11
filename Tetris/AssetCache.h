//
//  AssetCache.h
//  Tetris
//
//  Created by Fielding Johnston on 4/9/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__AssetCache__
#define __Tetris__AssetCache__

#include <iostream>
#include <map>

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class AssetCache
{
public:
  AssetCache( void );
  ~AssetCache( void );

  // Audio
  Mix_Chunk* getSound( std::string filename ) const;
  Mix_Music* getMusic( std::string filename ) const;
  
  // Graphics
  SDL_Surface* getImage( std::string filename ) const;
  TTF_Font* getFont( std::string filename, int pointSize ) const;
  

private:
  static std::map< std::string, Mix_Chunk* > soundCache;
  static std::map< std::string, Mix_Music* > musicCache;
  static std::map< std::string, SDL_Surface* > imageCache;
  static std::map< std::string, TTF_Font* > fontCache;

  template < typename T >
    struct Deallocator
    {
      void operator()( const std::pair< std::string, T > &p )
      {
        delete p.second;
      }
    };

};

class NotFoundException : public std::runtime_error
{
public:
  NotFoundException( std::string const& msg ): std::runtime_error( msg ) {}
};

#endif /* defined(__Tetris__AssetCache__) */
