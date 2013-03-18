//
//  Game.h
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Game__
#define __Tetris__Game__

#include <iostream>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Constants.h"
#include "Timer.h"
#include "Block.h"
#include "Tetrimino.h"
#include "Board.h"

using namespace std;



// Tetris Board Attributes

class Game
{

public:
  // Constructor/Destructor
  Game();
  ~Game();
  
  // public functions
  int start();
  void drawBlock( Block block, bool activeTetrimino);
  void drawBoard();
  void drawNextContainer();
  void drawActiveTetrimino();
  void drawNextTetrimino();
  int isMovePossible(int x, int y);

private:
  Board *myBoard;
  Tetrimino *tetrimino;
  Timer globalTimer;
  Timer playTimer;
  Timer fps;
  Timer update;

  void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
  bool check_collision( SDL_Rect A, SDL_Rect B );
  void clean_up();
  bool init();
  bool load_files();
  SDL_Surface *load_image( string filename );
  
  // Surfaces
  SDL_Surface *screen = NULL;
  SDL_Surface *background = NULL;
  SDL_Surface *boardSurface = NULL;
  SDL_Surface *boardTile = NULL;
  
  // Surfaces for block images
  SDL_Surface *cyanBlock = NULL;
  SDL_Surface *blueBlock = NULL;
  SDL_Surface *orangeBlock = NULL;
  SDL_Surface *yellowBlock = NULL;
  SDL_Surface *greenBlock = NULL;
  SDL_Surface *purpleBlock = NULL;
  SDL_Surface *redBlock = NULL;
  
  // Message Surfaces
  SDL_Surface *seconds = NULL;
  SDL_Surface *startStop = NULL;
  SDL_Surface *pauseMessage = NULL;
  SDL_Surface *mainMessage = NULL;
  
  // Event Structure
  SDL_Event event;
  
  // Font, font fg color and font bg color
  TTF_Font *font = NULL;
  SDL_Color fontFgColor = { 0, 0, 0 };
  SDL_Color fontBgColor = { 255, 255, 255 };
  
};


#endif /* defined(__Tetris__Game__) */
