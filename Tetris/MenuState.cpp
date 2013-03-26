//
//  MenuState.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "MenuState.h"

MenuState MenuState::menustate;

void MenuState::Init( GameEngine* game )
{
  loadAssets( game );
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
          case SDLK_1:
            game->PopStateThenChangeState( PlayState::Instance() );
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
  game->apply_surface( BOARD_ORIGIN_X + 40, BOARD_ORIGIN_Y + 32, interfaceMenu, game->screen);
  SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void MenuState::loadAssets( GameEngine* game )
{
  interfaceMenu = game->load_image("Tetris.app/Contents/Resources/img/menu.png");
  Uint32 colorkey = SDL_MapRGB( interfaceMenu->format, 0xFF, 0, 0xFF);
  SDL_SetColorKey( interfaceMenu, SDL_SRCCOLORKEY, colorkey);
}

