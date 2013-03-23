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
  aTetrimino = new Tetrimino(true);
  nTetrimino = new Tetrimino(true);
  hTetrimino = new Tetrimino(false);
  
  globalTimer.start();
  update.start();
  quit = false;
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
  int force_time = 500;
  int linesCleared = 0;
  // Game Loop
  cout<<"Starting the game"<<endl;
  gameState = Playing;
  playTimer.start();
  holdUsed = false; // CONSIDER: Is this the best places for this??
  
  while ( quit == false )
  {
    
    while ( gameState == Playing && quit == false )
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
      end_time = playTimer.get_ticks();
      if ( end_time - start_time > force_time )
      {
        if (aTetrimino->moveDown(myBoard))
        {
          start_time = playTimer.get_ticks();
        }
        else
        {
          // add tetrimino to grid
          storeTetrimino();
          
          // check for game over
          if ( isGameOver() )
          {
            gameState = GameOver;
            break;
          }
          
          nextTetrimino();
          holdUsed = false;
          
          linesCleared = checkLines();
          cout<<"Lines Cleared: "<<linesCleared<<endl;
          start_time = playTimer.get_ticks();
        }
      }
      
      // Game Loop: Rendering
    
      // Fill the screen white
      SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
      // Display game timer
      displayTimer( playTimer.get_ticks(), ( SCREEN_WIDTH / 2 ), 10);

      // Draw the board and next container
      drawInterface();
      drawBoard();
      //drawNextContainer();
      //drawHeldContainer();
      
      // Draw the active and next tetrimino
      drawActiveTetrimino();
      drawNextTetrimino();
      drawHeldTetrimino();
      
      // Update the screen
      updateScreen();
      
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
    }
    
    while ( gameState != Playing && quit == false )
    {
      
      while ( SDL_PollEvent( &event ) )
      {
        interfaceInput();
      }
      
      
      if ( gameState == GameOver )
      {

        apply_surface( BOARD_ORIGIN_X + BLOCK_SIZE, BOARD_ORIGIN_Y + ( BLOCK_SIZE * 9 ), interfaceMessageGameOver, screen );
      }
      
      if ( gameState == Paused )
      {
        apply_surface( BOARD_ORIGIN_X + BLOCK_SIZE, BOARD_ORIGIN_Y + ( BLOCK_SIZE * 9), interfaceMessagePaused, screen );
      }
      
      if ( gameState == Menu )
      {
        apply_surface( BOARD_ORIGIN_X + 40, BOARD_ORIGIN_Y + 32, interfaceMenu, screen);
      }
      
      updateScreen();
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
    if (aTetrimino->pieces[i].box.y >= 0) {
    drawBlock( aTetrimino->pieces[i], active);
    }
  }
}

void Game::drawBlock( Block block, int type, int xOffset, int yOffset )
{
  
  if ( type == active)
  {
    block.box.x += BOARD_ORIGIN_X;
    block.box.y += BOARD_ORIGIN_Y;
  } else if ( type == next )
  {
    block.box.x += NC_ORIGIN_X - (BLOCK_SIZE * 3) + xOffset;
    block.box.y += NC_ORIGIN_Y + yOffset;
  } else if ( type == fixed )
  {
    block.box.x += BOARD_ORIGIN_X;
    block.box.y += BOARD_ORIGIN_Y;
  } else if ( type == held )
  {
    block.box.x += HC_ORIGIN_X - (BLOCK_SIZE * 3) + xOffset;
    block.box.y += HC_ORIGIN_Y + yOffset;
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

void Game::drawHeldContainer()
{
  int xOffset = BOARD_ORIGIN_X - (BLOCK_SIZE * 6);  // place the container 6 blocks over from our main game board (resulting in 2 block margin)
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
  
  int xOffset = ( CONTAINER_WIDTH - nTetrimino->getPixelWidth() ) / 2;
  int yOffset = ( CONTAINER_HEIGHT - nTetrimino->getPixelHeight() ) / 2;
  
  for ( int i = 0; i < 4; i++)
  {
    drawBlock( nTetrimino->pieceOrigins[i], next, xOffset, yOffset);
  }
}

void Game::drawHeldTetrimino()
{
  int xOffset = ( CONTAINER_WIDTH - hTetrimino->getPixelWidth() ) / 2;
  int yOffset = ( CONTAINER_HEIGHT - hTetrimino->getPixelHeight() ) / 2;
  
  for ( int i = 0; i < hTetrimino->pieceOrigins.size(); i++)
    {
      drawBlock( hTetrimino->pieceOrigins[i], held, xOffset, yOffset );
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
    
    // If T is pressed
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
    
    // If P is pressed
    if ( event.key.keysym.sym == SDLK_p )
    {
      // If playTimer is paused
      if ( gameState == Paused )
      {
        // unpause playTimer
        playTimer.unpause();
        gameState = Playing;
        cout<<"Game State: "<< gameStateNames[gameState] <<endl;
      }
      else if ( gameState != Paused)
      {
        // pause playTimer
        playTimer.pause();
        gameState = Paused;
        cout<<"Game State: "<< gameStateNames[gameState] <<endl;
      }
    }
  
    // if ESCAPE is pressed
    
    if ( event.key.keysym.sym == SDLK_ESCAPE )
    {
      if ( gameState != Menu )
      {
        if ( gameState != Paused ) { playTimer.pause(); }
        previousGameState = gameState;
        gameState = Menu;
        cout<<"Game State: "<< gameStateNames[gameState] <<endl;
      }
      else if ( gameState == Menu )
      {
        if ( previousGameState != Paused ) { playTimer.unpause(); }
        gameState = previousGameState;
        cout<<"Game State: "<< gameStateNames[gameState] <<endl;
      }
    }
  
    if ( gameState == Menu) {
      if ( event.key.keysym.sym == SDLK_3 )
      {
        quit = true;
      }
    }
    
    
    // end event.type == SDL_KEYDOWN
  }
  
  if ( event.type == SDL_QUIT )
  {
    // Quit the progam
    quit = true;
  }
}

bool Game::isGameOver()
{
  for ( int w = 0; w < BOARD_BLOCK_WIDTH; w++ )
  {
    if (myBoard->mBoard[w][0] != 0) { return true; }
  }
  
  return false;
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
  
  boardTile = load_image("Tetris.app/Contents/Resources/img/boardtile.png");
  boardOutline = load_image("Tetris.app/Contents/Resources/img/boardoutline.png");
  
  interfaceMessageGameOver = load_image("Tetris.app/Contents/Resources/img/gameover.png");
  interfaceMessagePaused = load_image("Tetris.app/Contents/Resources/img/paused.png");
  
  interfaceMenu = load_image("Tetris.app/Contents/Resources/img/menu.png");
  /*
  if ( boardOutline == NULL )
  {
    cout<<IMG_GetError()<<endl;
  }
  */
  
  // Load font
  font = TTF_OpenFont( "Tetris.app/Contents/Resources/font/HelveticaNeueCondensedBold.ttf", 28);
  
  
  
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
      case SDLK_DOWN:   // Soft Drop
        aTetrimino->moveDown(myBoard);
        break;
      case SDLK_LEFT:   // Move Left
        aTetrimino->moveLeft(myBoard);
        break;
      case SDLK_RIGHT:  // Move Right
        aTetrimino->moveRight(myBoard);
        break;
      case SDLK_LSHIFT:
      case SDLK_c:    // Hold Tetrimino
        holdTetrimino();
        break;
      case SDLK_RCTRL: // Rotate Left
      case SDLK_z:  // Rotate Left
        aTetrimino->rotate("left");
        break;
      case SDLK_UP: // Rotate Right
      case SDLK_x:  // Rotate Right
        aTetrimino->rotate("right");
        break;
      case SDLK_SPACE:
        aTetrimino->hardDrop(myBoard);
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
    int xPos = aTetrimino->pieces[b].box.x / 16;
    int yPos = aTetrimino->pieces[b].box.y / 16;
    int blockType = aTetrimino->pieces[b].blockType;
    
    cout<<"Storing blocktype "<< blockType <<" at ("<< xPos <<", "<<yPos<<")\n";
    myBoard->updateBlock(xPos, yPos, blockType);
  }
}

int Game::checkLines()
{
  int linesCleared = 0;
  
  for ( int h = 0; h < BOARD_BLOCK_HEIGHT; h++ )
  {
    if ( lineIsFull( h ) )
    {
      cout<<"Line "<<h<<" is full! Deleting it!\n";
      deleteLine( h );
      dropLines( h );
      linesCleared++;
    }
  }
  
  return linesCleared;
}

bool Game::lineIsFull( int y )
{
  for ( int x = 0; x < BOARD_BLOCK_WIDTH; x++ )
  {
    if ( myBoard->mBoard[x][y] == 0 )
      return false;
  }
  
  return true;
}

void Game::deleteLine( int y )
{
  for ( int x = 0; x < BOARD_BLOCK_WIDTH; x++ )
  {
    myBoard->updateBlock( x, y, 0 );
  }
}

void Game::dropLines( int y )
{
  for ( int x = 0; x < BOARD_BLOCK_WIDTH; x++ )
  {
    for ( int h = y; h > 0; h-- )
    {
      myBoard->mBoard[x][h] = myBoard->mBoard[x][h-1];
    }
  }
}

void Game::displayTimer( int time, int x, int y )
{
  SDL_Surface *timer = NULL;
  // Timer's time as string
  stringstream timeString;
  
  // Convert the timer's time to a string
  timeString << "Timer: " << time / 1000;
  
  // Render the time surface
  timer = TTF_RenderText_Shaded( font, timeString.str().c_str(), fontFgColor, fontBgColor );
  
  // Apply the time surface
  apply_surface( ( x - ( timer->w / 2 ) ) , ( y - ( timer->h / 2 ) ) , timer, screen );
  
  // Free the time surface
  SDL_FreeSurface ( timer );
}

void Game::displayText(string text, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB)
{
 
  SDL_Color foreground = { fR, fG, fB };  // Text foreground color
  SDL_Color background = { bR, bG, bB };  // Text background color
  
  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, text.c_str(), foreground, background); // Render our text to temporary text surface

  apply_surface( ( x - ( textSurface->w / 2 ) ) , ( y - ( textSurface->h / 2 ) ), textSurface, screen);  // call apply_surface function using our newly setup text surface
  
  SDL_FreeSurface(textSurface); // Free dem memories!
}

bool Game::updateScreen()  // This function is kind of pointless lol
{
  if ( SDL_Flip( screen ) == -1 )
  {
    return 1;
  }
  return 0;
}

void Game::drawInterface()
{
  apply_surface(BOARD_ORIGIN_X - 96 , BOARD_ORIGIN_Y - 45, boardOutline, screen);
}

void Game::holdTetrimino()
{
  if ( holdUsed == false )
  {
    if (hTetrimino->pieces.size() == 0)
    {
        hTetrimino = aTetrimino;
        nextTetrimino();
        holdUsed = true;
    }
    else if (hTetrimino->pieces.size() > 0)
    {
        bTetrimino = hTetrimino;  // store currently heldTetrimino as bufferTetrimino
        hTetrimino = aTetrimino;  // move activeTetrimino to heldTetrimino
        aTetrimino = bTetrimino;  // move bufferTetrimino to activeTetrimino
        aTetrimino->resetPosition();
        holdUsed = true;
        cout<<"Swapping held and active Tetrimino"<<endl;
    }
  }
}

void Game::nextTetrimino()
{
  // move next to active and spawn a new next
  aTetrimino = nTetrimino;
  nTetrimino = new Tetrimino(true);
}