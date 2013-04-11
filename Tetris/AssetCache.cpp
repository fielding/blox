//
//  AssetCache.cpp
//  Tetris
//
//  Created by Fielding Johnston on 4/9/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "AssetCache.h"

AssetCache::AssetCache( void ) {}

AssetCache::~AssetCache( void )
{
  std::for_each( soundCache.begin(), soundCache.end(), Deallocator< Mix_Chunk* >() );
  std::for_each( musicCache.begin(), musicCache.end(), Deallocator< Mix_Music* >() );
  std::for_each( imageCache.begin(), imageCache.end(), Deallocator< SDL_Surface* >() );
  std::for_each( fontCache.begin(), fontCache.end(), Deallocator< TTF_Font* >() );
}

Mix_Chunk* AssetCache::getSound(std::string filename) const
{
  // create a pointer to a Mix_Chunk object that will be used to point to the sound we are going to play
  Mix_Chunk* sound;
  
  // check for filename existing in cache, if it exists, then itr will point to it, if not it will point to sounds.end()
  std::map< std::string, Mix_Chunk* >::iterator itr = soundCache.find(filename);
  
  
  // if our find function was unable to find the filename existing in the sounds cache map then...
  if ( itr == soundCache.end() )
  {
    // attempt to load the sound and set the sound pointer equal to the pointer that Mix_LoadWAV returns
    sound = Mix_LoadWAV( filename.c_str() );
    
    // if Mix_LoadWAV returned null then our sound failed to load
    if ( sound == NULL )
    {
      // Free the sound object and throw and exception indicating that the file was not found
      Mix_FreeChunk(sound);
      throw NotFoundException( filename + " could not be loaded from file in call to AssetCache::getSound." );
    }
    
    // Store the new sound in the cache, so it can be retrieved when needed
    std::map< std::string,Mix_Chunk* >::iterator res = soundCache.insert( std::pair< std::string,Mix_Chunk* >( filename, sound ) ).first;
    
    // Return the value part of the stored pair ( the pointer to the sound object )
    return res->second;
  }
  else
  {
    // Return the value part of the pair we located in the cache (the pointer to the sound object we need )
    return itr->second;
  }
  
  // if we got this far then something went wrong, throw an exception
  throw NotFoundException( filename + " was not found in call to AssetCache::getSound." );
}

Mix_Music* AssetCache::getMusic( std::string filename ) const
{
  std::map< std::string, Mix_Music* >::iterator itr = musicCache.find( filename );
  
  if ( itr == musicCache.end() )
  {
    
    Mix_Music* music;
    music = Mix_LoadMUS( filename.c_str() );
    
    if ( music == NULL )
    {
      Mix_FreeMusic(music);
      throw NotFoundException( filename + " was not found in call to AssetCache::getMusic" );
    }
    else
    {
      std::map< std::string, Mix_Music* >::iterator res = musicCache.insert( std::pair< std::string, Mix_Music* >( filename, music ) ).first;
      return res->second;
    }
  
  }
  else
  {
    return itr->second;
  }
  
  throw NotFoundException( filename + " was not found in call to AssetCache::getMusic" );
  
}

SDL_Surface* AssetCache::getImage( std::string filename ) const
{
  // create a pointer to a SDL_Surface object that will be used to point to the image surface
  SDL_Surface *image = NULL;
  
  // create a pointer for optimized surface ( the end result) that the function will return
  SDL_Surface *optimizedImage = NULL;
  
  // check if the filemame exists in cache, if it exists, then itr will point to it, if not it will point to sounds.end()
  std::map< std::string, SDL_Surface* >::iterator itr = imageCache.find(filename);
  
  // if our find function was unable to find the filename in the image cache map then...
  if ( itr == imageCache.end() )
  {
    // attempt to load the image and set the image pointer equal to the pointer IMG_Load returns
    image = IMG_Load( filename.c_str() );
    
    // if IMG_Load returned null then our image failed to load
    if ( image == NULL )
    {
      // Free the surface and throw an exception indicating that the file was not found
      SDL_FreeSurface( image );
      throw NotFoundException( filename + " could not be loaded from file in call to AssetCache::getImage.");
    }
    // Before we store the newly loaded image in to the cache, we create an optimized version based on the current display format
    optimizedImage = SDL_DisplayFormat( image);
    
    // Store the optimized version in the cache, so it can be retrieved when needed
    std::map< std::string, SDL_Surface* >::iterator res = imageCache.insert( std::pair< std::string, SDL_Surface* >(filename, optimizedImage ) ).first;
    
    // Return the value part of the stored pair ( the pointer to our image surface )
    return res->second;
  }
  else
  {
    // Return the value part of the pair we located in the cache ( the pointer to the image surface we need )
    return itr->second;
  }
  
  // if we got this far then something went wrong, throw an exception
  throw NotFoundException( filename + " was not found in the call to AssetCache::getImage.");
}

TTF_Font* AssetCache::getFont( std::string filename, int pointSize) const
{
  // create a pointer to a TTF_font object that will be used to point to the image surface
  TTF_Font* font;
  
  // check if the filename exists in cache, if it exists, then itr will point to it, if not it will point to sounds.end()
  std::map< std::string, TTF_Font* >::iterator itr = fontCache.find( filename );
  
  // if our find function was unable to find the filename in the font cache then...
  if ( itr == fontCache.end() )
  {
    // attempt to load the font and set the font pointer equal to the pointer that TTF_OpenFont returns
    font = TTF_OpenFont( filename.c_str(), pointSize );
    
    // if TTF_OpenFont returned null then our font failed to load
    if ( font == NULL )
    {
      // Free the object andt throw an exception indicating that the file was not found
      TTF_CloseFont( font );
      throw NotFoundException( filename + " could not be loaded from file in call to AssetCache::getFont.");
    }
    
    // Store the font in the cache, so it can be retrieved when needed
    std::map< std::string, TTF_Font* >::iterator res = fontCache.insert( std::pair< std::string, TTF_Font* >( filename, font ) ).first;
    
    // Return the value part of the stored pair ( the pointer to our font )
    return res->second;
  }
  else
  {
    // Return the value part of the pair we located in the cache ( the pointer to the font object we need ).
    return itr->second;
  }
  
  // if we got this far then something went wrong, throw an exception
  throw NotFoundException( filename + " was not found in the call to AssetCache::getFont.");
}

std::map< std::string, Mix_Chunk* > AssetCache::soundCache;
std::map< std::string, Mix_Music* > AssetCache::musicCache;
std::map< std::string, SDL_Surface* > AssetCache::imageCache;
std::map< std::string, TTF_Font* > AssetCache::fontCache;
