//
//  GameOverState.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "GameOverState.h"

GameOverState::GameOverState( GameEngine* game )
{
  loadAssets();
  std::cout<<"GameOverState Init"<<std::endl;
}

GameOverState::~GameOverState()
{
  SDL_FreeSurface(interfaceMessageGameOver);
  std::cout<<"GameOverState Cleanup"<<std::endl;
}

void GameOverState::Pause()
{
  std::cout<<"GameOverState Pause"<<std::endl;
}

void GameOverState::Resume()
{
  std::cout<<"GameOverState Resume"<<std::endl;
}

void GameOverState::HandleEvents( GameEngine* game)
{
	SDL_Event event;
  
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
		}
	}
}

void GameOverState::Update( GameEngine* game)
{
  game->PushState( std::unique_ptr<MenuState>( new MenuState( game ) ) );
}

void GameOverState::Draw( GameEngine* game )
{
  apply_surface( BOARD_ORIGIN_X + BLOCK_SIZE, BOARD_ORIGIN_Y + ( BLOCK_SIZE * 9 ), interfaceMessageGameOver, game->screen );
  SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void GameOverState::loadAssets()
{
  interfaceMessageGameOver = load_image("Tetris.app/Contents/Resources/img/gameover.png");
}

SDL_Surface *GameOverState::load_image( std::string filename )
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

void GameOverState::apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip )
{
  // Store and get offsets
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  // Blit
  SDL_BlitSurface( source, clip, destination, &offset );
}
