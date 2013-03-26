//
//  MenuState.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "MenuState.h"

MenuState MenuState::menustate;

void MenuState::Init()
{
  loadAssets();
  std::cout<<"MenuState Init"<<std::endl;
}

void MenuState::Cleanup()
{
  SDL_FreeSurface(interfaceMenu);
  std::cout<<"MenuState Cleanup"<<std::endl;
}

void MenuState::Pause()
{
  std::cout<<"MenuState Pause"<<std::endl;
}

void MenuState::Resume()
{
  std::cout<<"MenuState Resume"<<std::endl;
}

void MenuState::HandleEvents( GameEngine* game)
{
	SDL_Event event;
  
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
        
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game->PopState();
						break;
          case SDLK_3:
            game->Quit();
            break;
				}
				break;
		}
	}
}

void MenuState::Update( GameEngine* game)
{
  
}

void MenuState::Draw( GameEngine* game )
{
  apply_surface( BOARD_ORIGIN_X + 40, BOARD_ORIGIN_Y + 32, interfaceMenu, game->screen);
  SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void MenuState::loadAssets()
{
  interfaceMenu = load_image("Tetris.app/Contents/Resources/img/menu.png");
  Uint32 colorkey = SDL_MapRGB( interfaceMenu->format, 0xFF, 0, 0xFF);
  SDL_SetColorKey( interfaceMenu, SDL_SRCCOLORKEY, colorkey);
}

SDL_Surface *MenuState::load_image( std::string filename )
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

void MenuState::apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip )
{
  // Store and get offsets
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  // Blit
  SDL_BlitSurface( source, clip, destination, &offset );
}
