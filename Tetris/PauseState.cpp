//
//  PauseState.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "PauseState.h"

PauseState PauseState::pausestate;

void PauseState::Init( GameEngine* game )
{
  loadAssets();
  std::cout<<"PauseState Init"<<std::endl;
}

void PauseState::Cleanup()
{
  SDL_FreeSurface(interfaceMessagePaused);
  std::cout<<"PauseState Cleanup"<<std::endl;
}

void PauseState::Pause()
{
  std::cout<<"PauseState Pause"<<std::endl;
}

void PauseState::Resume()
{
  std::cout<<"PauseState Resume"<<std::endl;
}

void PauseState::HandleEvents( GameEngine* game)
{
	SDL_Event event;
  
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
        
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_p:
						game->PopState();
						break;
				}
				break;
		}
	}
}

void PauseState::Update( GameEngine* game)
{
  
}

void PauseState::Draw( GameEngine* game )
{
  apply_surface( BOARD_ORIGIN_X + BLOCK_SIZE, BOARD_ORIGIN_Y + ( BLOCK_SIZE * 9), interfaceMessagePaused, game->screen );
  SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void PauseState::loadAssets()
{
  interfaceMessagePaused = load_image("Tetris.app/Contents/Resources/img/paused.png");
}

SDL_Surface *PauseState::load_image( std::string filename )
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

void PauseState::apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip )
{
  // Store and get offsets
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  // Blit
  SDL_BlitSurface( source, clip, destination, &offset );
}
