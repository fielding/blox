//
//  GameEngine.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include <iostream>

#include "GameEngine.h"
#include "GameState.h"
#include "SDLAudio.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

GameEngine::GameEngine(const char* title, int width, int height, int bpp, bool fullscreen, bool noframe)
{
  int flags = 0;
  
  // seed for random();
  srandom((unsigned)time(NULL));
  
  // Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
    std::cout<<"Failed to initialize SDL"<<std::endl;
  }
  
  // Initialize SDL font library
  if( TTF_Init() == -1 )
  {
    std::cout<<"Failed to initialize the SDL Font library"<<std::endl;
  }
  
  Locator::initialize();
  SDLAudio *audio = new SDLAudio();
  Locator::provide(audio);
    
  // Set the window caption
  SDL_WM_SetCaption( title, title );
  
  // if noframe = true then set the noframe flag
  if ( noframe )
  {
    flags = SDL_NOFRAME;
  }
  
  
  // if fullscreen = true then set the fullscreen flag
  if ( fullscreen )
  {
    flags = SDL_FULLSCREEN;
  }
  
  
  // Set up the screen
  screen = SDL_SetVideoMode( width, height, bpp, flags );
  
  // unfinished experimenting with transparency
  //#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  //screen = SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
  //#else
  //screen = SDL_CreateRGBSurface(SDL_HWSURFACE,width,height,32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
  //#endif
  
  // Check for error while starting screen
  if ( screen == NULL )
  {
    std::cout<<"Failed to create the screen surface"<<std::endl;
  }
  
  this->fullscreen = fullscreen;
  this->running = true;
  
  globalTimer.start();
  
  std::cout<<"GameEngine Init"<<std::endl;
  
}

GameEngine::~GameEngine()
{
  // cleanup all of the states
  while ( !states.empty() )
  {
    states.pop_back();
  }
  
  // if we were in fullscreen, switch back to windowed mode
  if ( this->fullscreen )
  {
    screen = SDL_SetVideoMode(640, 480, 0 ,0);
  }
  
  std::cout<<"GameEngine Cleanup"<<std::endl;
  
  // Quit SDL_ttf
  TTF_Quit();
  
  // Quit SDL
  SDL_Quit();
  
}

void GameEngine::ChangeState( std::unique_ptr<GameState> state )
{
  // cleanup the current state
  if ( !states.empty() )
  {
    states.pop_back();
  }
  
  // store the new state
  states.push_back( std::move( state ) );
  
}

void GameEngine::PushState( std::unique_ptr<GameState> state )
{
  // pause current state
  if ( !states.empty() )
  {
    states.back()->Pause();
  }

  // store the new state
  states.push_back( std::move( state ) );
}

void GameEngine::PopState()
{
  // cleanup the current state
  if ( !states.empty() )
  {
    states.pop_back();
  }
  
  // resume previous state
  if ( !states.empty () )
  {
    states.back()->Resume();
  }
  
}

void GameEngine::PopStateThenChangeState( std::unique_ptr<GameState> state )
{
  // cleanup the current state
  if ( !states.empty() )
  {
    states.pop_back();
  }
  
  // 
  if ( !states.empty () )
  {
    states.back()->ChangeState( this, std::move( state ) );
  }
  
}

void GameEngine::HandleEvents()
{
  // let the state handle events
  states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
  states.back()->Update(this);
}

void GameEngine::Draw( float interpolation )
{
  // let the state draw the scene
  states.back()->Draw(this);
}

SDL_Surface *GameEngine::load_image( std::string filename )
{
  // pointer for initial load of image
  SDL_Surface *loadedImage = NULL;
  
  // pointer for optimized surface that the function will return
  SDL_Surface *optimizedImage = NULL;
  
  // load the image
  loadedImage = IMG_Load( filename.c_str() );
  
  // Check that the image loaded correctly
  if ( loadedImage != NULL )
  {
    // Create optimzed version
    optimizedImage = SDL_DisplayFormat( loadedImage );
    
    // Free original pointer
    SDL_FreeSurface( loadedImage);
  }
  // Return the optmized version
  return optimizedImage;
}

void GameEngine::apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip )
{
  // Store and get offsets
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  // Blit
  SDL_BlitSurface( source, clip, destination, &offset );
}