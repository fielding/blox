//
//  Game.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "SDL.h"
#include "Game.h"

Game::Game()
{
  // Initialize game
  cout<<"Initializing the game"<<endl;
  if ( init() == false )
  {
    cout<<"Failed to initialize the game"<<endl;
  }
  
  
  cout<<"Loading Files"<<endl;
  if ( load_files() == false )
  {
    cout<<"Failed to load game files"<<endl;
  }
  
  myBoard = new Board( BOARD_BLOCK_WIDTH, BOARD_BLOCK_HEIGHT );
  tetrimino = new Tetrimino;
  
  
  globalTimer.start();
  update.start();
}

Game::~Game()
{
  // Clean up
}

int Game::start()
{
  int frame = 0;
  int start_time = 0;
  int end_time = 0;
  int force_time = 1000;
  
  // Game Loop
  cout<<"Starting the game"<<endl;
  playing = true;
  playTimer.start();
  
  while ( playing )
  {
    // Start frame timer and play timer
    fps.start();
    // Game Loop: Events
    while ( SDL_PollEvent( &event ) )
    {
      // Watch for keybord events
      movementInput();
      interfaceInput();
    }
  
  // Game Loop: Logic
  
  
  // Game Loop: Rendering
  
  // Fill the screen white
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
  
  // Timer's time as string
  stringstream time;
  
  // Convert the timer's time to a string
  time << "Timer: " << playTimer.get_ticks() / 1000.f;
  
  // Render the time surface
  seconds = TTF_RenderText_Shaded( font, time.str().c_str(), fontFgColor, fontBgColor );
  
  // Apply the time surface
  apply_surface( ( SCREEN_WIDTH - seconds->w ) / 2, 0, seconds, screen );
  
  // Free the time surface
  SDL_FreeSurface ( seconds );
  
  // Draw the board and next container
  drawBoard();
  drawNextContainer();
  
  // Draw the active and next tetrimino
  drawActiveTetrimino();
  drawNextTetrimino();
        
  // Update the screen
  if ( SDL_Flip( screen ) == -1 )
  {
    return 1;
  }
  
  // Increment the frame counter
  frame++;
  
  // If a second has passed since the fps caption was last updated
  if( update.get_ticks() > 1000 )
  {
    // The frame rate as a string
    stringstream caption;
    
    // Calculate the frame per second and create the string
    caption << "Fielding's Tetris - Avg FPS: " << frame / ( globalTimer.get_ticks() / 1000.f );
    
    // Reset the caption
    SDL_WM_SetCaption( caption.str().c_str(), NULL );
    
    // Restart the update timer
    update.start();
  }
  
  // If we want to cap the frame rate
  if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
  {
    // Sleep the remaining time
    SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
  }
    
  end_time = playTimer.get_ticks();
  if ( end_time - start_time > force_time )
  {
    if ( isMovePossible(0, 1) == 0)
    {
      tetrimino->move(0, 1);
      start_time = playTimer.get_ticks();
    } else {
      cout<<"Collision Detected"<<endl;
      
      // check for game over
      if ( isGameOver() )
      {
        playing = false;
        cout<<"GAME OVER BITCHES!"<<endl;
        break;
      }
      
      // add tetrimino to grid
      storeTetrimino();
      tetrimino->next();
      start_time = playTimer.get_ticks();
    }
  }
}
  
  return 0;
}

void Game::apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip )
{
  // Store and get offsets
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  // Blit
  SDL_BlitSurface( source, clip, destination, &offset );
}

bool Game::check_collision( SDL_Rect A, SDL_Rect B )
{
  // The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;
  
  // Calculate sides of rect A
  leftA = A.x;
  rightA = A.x + A.w;
  topA = A.y;
  bottomA = A.y + A.h;
  
  // Calculate sides of rect B
  leftB = B.x;
  rightB = B.x + B.w;
  topB = B.y;
  bottomB = B.y + B.h;
  
  // If any of the sides from A are outside of B
  if ( bottomA <= topB )
  {
    return false;
  }
  
  if ( topA >= bottomB )
  {
    return false;
  }
  
  if ( rightA <= leftB )
  {
    return false;
  }
  
  if ( leftA >= rightB )
  {
    return false;
  }
  
  // If none of the sides from A are outside of B
  clean_up();
  return true;
}

void Game::clean_up()
{
  // Free the surface
  SDL_FreeSurface(cyanBlock);
  SDL_FreeSurface(blueBlock);
  SDL_FreeSurface(orangeBlock);
  SDL_FreeSurface(yellowBlock);
  SDL_FreeSurface(greenBlock);
  SDL_FreeSurface(purpleBlock);
  SDL_FreeSurface(redBlock);
  
  // Close the font and quit SDL_ttf
  TTF_CloseFont( font );
  TTF_Quit();
  
  // Quit SDL
  SDL_Quit();
}

void Game::drawActiveTetrimino()
{
  for ( int i = 0; i < 4; i++)
  {
    drawBlock( tetrimino->activeTetrimino[i], "active");
  }
}

void Game::drawBlock( Block block, string type )
{
  
  if ( type == "active")
  {
    block.box.x += BOARD_ORIGIN_X;
    block.box.y += BOARD_ORIGIN_Y;
  } else if ( type == "next")
  {
    block.box.x += NC_ORIGIN_X - (BLOCK_SIZE * 3);
    block.box.y += NC_ORIGIN_Y;
  } else if (type == "static")
  {
    block.box.x += BOARD_ORIGIN_X;
    block.box.y += BOARD_ORIGIN_Y;
  }
  
  switch ( block.blockType )
  {
    case 1:
      apply_surface( block.box.x, block.box.y, cyanBlock, screen );
      break;
    case 2:
      apply_surface( block.box.x, block.box.y, blueBlock, screen );
      break;
    case 3:
      apply_surface( block.box.x, block.box.y, orangeBlock, screen );
      break;
    case 4:
      apply_surface( block.box.x, block.box.y, yellowBlock, screen );
      break;
    case 5:
      apply_surface( block.box.x, block.box.y, greenBlock, screen );
      break;
    case 6:
      apply_surface( block.box.x, block.box.y, purpleBlock, screen );
      break;
    case 7:
      apply_surface( block.box.x, block.box.y, redBlock, screen );
    default:
      break;
  }
  
}

void Game::drawBoard()
{
  for ( int x = 0; x < BOARD_WIDTH / BLOCK_SIZE; x++ )
  {
    for ( int y = 0; y < BOARD_HEIGHT / BLOCK_SIZE; y++ )
    {
      // If block is empty then use a board tile
      if ( myBoard->mBoard[x][y] == 0 )
      {
        SDL_Rect offset;
        offset.x = x * BLOCK_SIZE;
        offset.y = y * BLOCK_SIZE;
        apply_surface( BOARD_ORIGIN_X + offset.x, BOARD_ORIGIN_Y + offset.y, boardTile, screen );
      } else {
        int blockType = myBoard->mBoard[x][y];
        int xPos = x * BLOCK_SIZE + BOARD_ORIGIN_X;
        int yPos = y * BLOCK_SIZE + BOARD_ORIGIN_Y;
        
        switch ( blockType )
        {
          case 1:
            apply_surface( xPos, yPos, cyanBlock, screen );
            break;
          case 2:
            apply_surface( xPos, yPos, blueBlock, screen );
            break;
          case 3:
            apply_surface( xPos, yPos, orangeBlock, screen );
            break;
          case 4:
            apply_surface( xPos, yPos, yellowBlock, screen );
            break;
          case 5:
            apply_surface( xPos, yPos, greenBlock, screen );
            break;
          case 6:
            apply_surface( xPos, yPos, purpleBlock, screen );
            break;
          case 7:
            apply_surface( xPos, yPos, redBlock, screen );
          default:
            break;
        }
      }
    }
  }
}

void Game::drawNextContainer()
{
  int xOffset = BOARD_ORIGIN_X + BOARD_WIDTH + (BLOCK_SIZE * 2);  // place the container 4 blocks over from our main game board
  int yOffset = BOARD_ORIGIN_Y + (BLOCK_SIZE * 2); // place the container down from where our main board starts by n number of blocks
  
  for (int x = 0; x < 4; x++ )
  {
    for ( int y = 0; y < 4; y++ )
    {
      apply_surface( xOffset + ( x * BLOCK_SIZE ), yOffset + ( y * BLOCK_SIZE ), boardTile, screen );
    }
  }
}

void Game::drawNextTetrimino()
{
  for ( int i = 0; i < 4; i++)
  {
    drawBlock( tetrimino->nextTetrimino[i], "next" );
  }
}

bool Game::init()
{
  // seed for random();
  srandom((unsigned)time(NULL));
  
  // Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
    return false;
  }
  
  // Set up the screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  
  // Check for error while starting screen
  if ( screen == NULL )
  {
    return false;
  }
  
  // Initialize SDL font library
  if( TTF_Init() == -1 )
  {
    return false;
  }
  
  // Set the window caption
  SDL_WM_SetCaption( "Fielding's Tetris", NULL );
  
  // everything initialized
  return true;
}

void Game::interfaceInput()
{
  if( event.type == SDL_KEYDOWN )
  {
    
    // If T was pressed
    if ( event.key.keysym.sym  == SDLK_t )
    {
      // If playTimer is running
      if (playTimer.is_started() == true)
      {
        // stop playTimer
        playTimer.stop();
      }
      else
      {
        // Start playTimer
        playTimer.start();
      }
    }
    
    // If P was pressed
    if ( event.key.keysym.sym == SDLK_p )
    {
      // If playTimer is paused
      if ( playTimer.is_paused() == true )
      {
        // unpause playTimer
        playTimer.unpause();
      } else
      {
        // pause playTimer
        playTimer.pause();
      }
    }
  }
  
  if ( event.type == SDL_QUIT )
  {
    // Quit the progam
    playing = false;
  }
}

bool Game::isGameOver(){
  for ( int w = 0; w < BOARD_BLOCK_WIDTH; w++ )
  {
    if (myBoard->mBoard[w][0] != 0) { return true; }
  }
  
  return false;
}

int Game::isMovePossible( int x, int y )
{
  int status = 0;
  for ( int b = 0; b < 4; b++ )
  {
    int xPos = tetrimino->activeTetrimino[b].box.x / 16 + x;
    int yPos = tetrimino->activeTetrimino[b].box.y / 16 + y;
    if( xPos < 0 || xPos > 9 || yPos < 0 || yPos > 19 ) {
      status++;
    } else {
      status += myBoard->mBoard[xPos][yPos];
    }
  }
  return status;
}

bool Game::load_files()
{
  // background image load
  // placeholder for when I decide on a background image
  
  // Load images
  cyanBlock = load_image("Tetris.app/Contents/Resources/img/cyanblock.png");
  blueBlock = load_image("Tetris.app/Contents/Resources/img/blueblock.png");
  orangeBlock = load_image("Tetris.app/Contents/Resources/img/orangeblock.png");
  yellowBlock = load_image("Tetris.app/Contents/Resources/img/yellowblock.png");
  greenBlock = load_image("Tetris.app/Contents/Resources/img/greenblock.png");
  purpleBlock = load_image("Tetris.app/Contents/Resources/img/purpleblock.png");
  redBlock = load_image("Tetris.app/Contents/Resources/img/redblock.png");
  
  boardTile = load_image("Tetris.app/Contents/Resources/img/boardTile.png");
  
  // Load font
  font = TTF_OpenFont( "Tetris.app/Contents/Resources/font/HelveticaNeueCondensedBold.ttf", 28);
  
  // Check if images loaded properly
  if ( greenBlock == NULL || blueBlock == NULL || purpleBlock == NULL) {
    return false;
  }
  
  // Check if font loaded properly
  if ( font == NULL ) {
    return false;
  }
  
  return true;
  
}

SDL_Surface *Game::load_image( string filename )
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

void Game::movementInput()
{
  if ( event.type == SDL_KEYDOWN )      // If a key was presed
  {
    switch ( event.key.keysym.sym )
    {
      case SDLK_DOWN:
        if ( !isMovePossible( 0, 1 ) ) { tetrimino->move( 0, 1 ); }
        break;
      case SDLK_LEFT:
        if ( !isMovePossible( -1, 0 ) ) { tetrimino->move( -1, 0 ); }
        break;
      case SDLK_RIGHT:
        if ( !isMovePossible( 1, 0 ) ) { tetrimino->move( 1, 0 ); }
        break;
      case SDLK_LSHIFT || SDLK_RSHIFT:
        // Drop tetrimino
      default:
        break;
    }
  }
  // FUTURE USE: I plan to allow holding down keys for movement
  else if ( event.type == SDL_KEYUP )   // If a key was released
  {
    switch ( event.key.keysym.sym )
    {
      case SDLK_DOWN:
        break;
      case SDLK_LEFT:
        break;
      case SDLK_RIGHT:
        break;
      default:
        break;
    }
  }
}

void Game::storeTetrimino()
{
  for( int b = 0; b < 4; b++ )
  {
    int xPos = tetrimino->activeTetrimino[b].box.x / 16;
    int yPos = tetrimino->activeTetrimino[b].box.y / 16;
    int blockType = tetrimino->activeTetrimino[b].blockType;
    
    cout<<"Storing blocktype "<< blockType <<" at ("<< xPos <<", "<<yPos<<")\n";
    myBoard->updateBlock(xPos, yPos, blockType);
  }
}






