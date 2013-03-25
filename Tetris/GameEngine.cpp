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

#include "SDL.h"
#include "SDL_ttf.h"

void GameEngine::Init(const char* title, int width, int height, int bpp, bool fullscreen)
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
  
  // Set the window caption
  SDL_WM_SetCaption( title, title );
  
  // if fullscreen = true then set the fullscreen flag
  if ( fullscreen )
  {
    flags = SDL_FULLSCREEN;
  }
  
  // Set up the screen
  screen = SDL_SetVideoMode( width, height, bpp, flags );
  
  // Check for error while starting screen
  if ( screen == NULL )
  {
    std::cout<<"Failed to create the screen surface"<<std::endl;
  }
  
  this->fullscreen = fullscreen;
  this->running = true;
  
  std::cout<<"GameEngine Init"<<std::endl;
  

}

void GameEngine::Cleanup()
{
  // cleanup all of the states
  while ( !states.empty() )
  {
    states.back()->Cleanup();
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

void GameEngine::ChangeState( GameState* state )
{
  // cleanup the current state
  if ( !states.empty() )
  {
    states.back()->Cleanup();
    states.pop_back();
  }
  
  // store and init the new state
  states.push_back( state );
  states.back()->Init();
  
}

void GameEngine::PushState( GameState* state )
{
  // pause current state
  if ( !states.empty () )
  {
    states.back()->Pause();
  }

  // store and init the new state
  states.push_back(state);
  states.back()->Init();
}

void GameEngine::PopState()
{
  // cleanup the current state
  if ( !states.empty() )
  {
    states.back()->Cleanup();
    states.pop_back();
  }
  
  // resume previous state
  if ( !states.empty () )
  {
    states.back()->Resume();
  }
  
}

void GameEngine::HandleEvents()
{
  
}

void GameEngine::Update()
{
  
}

void GameEngine::Draw()
{
  
}