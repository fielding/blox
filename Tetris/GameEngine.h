//
//  GameEngine.h
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__GameEngine__
#define __Tetris__GameEngine__

#include "Timer.h"
#include "IAudio.h"
#include "Locator.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <vector>

class GameState;

class GameEngine
{
public:
  
  GameEngine(const char* title, int width=640, int height=480, int bpp=0, bool fullscreen=false, bool noframe=false);
  ~GameEngine();
  
  void ChangeState( std::unique_ptr<GameState> state );
  void PushState( std::unique_ptr<GameState> state );
  void PopState();
  void PopStateThenChangeState( std::unique_ptr<GameState> state );
  
  void HandleEvents();
  void Update();
  void Draw( float interpolation );
  
  bool Running() { return running; }
  void Quit() { running = false; }
  
  SDL_Surface *load_image( std::string filename );
  void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
  
  SDL_Surface* screen;
  
  // Timers
  Timer globalTimer;
  Timer updateTimer;
  
private:
  // state stack
  std::vector<std::unique_ptr<GameState>> states;
  
  bool running;
  bool fullscreen;
};


#endif /* defined(__Tetris__GameEngine__) */
