//
//  PlayState.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include <iostream>

#include "PlayState.h"

using namespace std;

PlayState PlayState::playstate;

void PlayState::Init( GameEngine* game )
{
  loadAssets( game );
  
  myBoard = new Board( BOARD_BLOCK_WIDTH, BOARD_BLOCK_HEIGHT );
  bag = new Bag();
  
  hTetrimino = new Tetrimino(false, 0);  // create hTetrimino, but don't spawn blocks yet
  
  fillQueue();  // fill the tetrmino queue
  nextTetrimino();  // callling this initially to get the first active Tetrimino
  
  
  cout<<"PlayState Init"<<endl;
  
  playTimer.start();
  holdUsed = false; // CONSIDER: Is this the best places for this??
  start_time = playTimer.get_ticks();
  
  
 /* 
      // Start frame timer and play timer
      fps.start();
      // Game Loop: Events

      

      

      
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
  */
  
}

void PlayState::Cleanup()
{
  cout<<"PlayState Cleanup"<<endl;
  
  // Free the image surfaces
  SDL_FreeSurface(cyanBlock);
  SDL_FreeSurface(blueBlock);
  SDL_FreeSurface(orangeBlock);
  SDL_FreeSurface(yellowBlock);
  SDL_FreeSurface(greenBlock);
  SDL_FreeSurface(purpleBlock);
  SDL_FreeSurface(redBlock);
  
  SDL_FreeSurface(boardTile);
  SDL_FreeSurface(boardOutline);
  
  // Close the font and quit SDL_ttf
  TTF_CloseFont( font );
}

void PlayState::Pause()
{
  playTimer.pause();
  cout<<"PlayState Paused"<<endl;
}

void PlayState::Resume()
{
  playTimer.unpause();
  cout<<"PlayState Resumed"<<endl;
}

void PlayState::HandleEvents( GameEngine* game )
{
  while ( SDL_PollEvent( &event ) )
  {
    // Watch for keybord events
    movementInput();
    interfaceInput(game);
  }
}

void PlayState::Update( GameEngine* game )
{
  
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
        game->ChangeState( GameOverState::Instance() );
      }
      
      nextTetrimino();
      holdUsed = false;
      
      linesCleared = checkLines();
      cout<<"Lines Cleared: "<<linesCleared<<endl;
      start_time = playTimer.get_ticks();
    }
  }
}

void PlayState::Draw( GameEngine* game )
{
  // Game Loop: Rendering
  
  // Fill the screen white
  SDL_FillRect( game->screen, &game->screen->clip_rect, SDL_MapRGB( game->screen->format, 0xFF, 0xFF, 0xFF ) );
  
  // Display game timer
  displayTimer(game, playTimer.get_ticks(), ( SCREEN_WIDTH / 2 ), 10);
  
  // Draw the board and next container
  drawInterface(game);
  drawBoard(game);
  
  // Draw the active and next tetrimino
  drawActiveTetrimino(game);
  drawTetriminoQueue(game);
  drawHeldTetrimino(game);
  
  // Update the screen
  SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void PlayState::drawActiveTetrimino(GameEngine* game)
{
  for ( int i = 0; i < 4; i++)
  {
    if (aTetrimino->pieces[i].box.y >= 0) {
      drawBlock(game, aTetrimino->pieces[i], active);
    }
  }
}

void PlayState::drawBlock(GameEngine* game, Block block, int type, int xOffset, int yOffset )
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
      game->apply_surface( block.box.x, block.box.y, cyanBlock, game->screen );
      break;
    case 2:
      game->apply_surface( block.box.x, block.box.y, blueBlock, game->screen );
      break;
    case 3:
      game->apply_surface( block.box.x, block.box.y, orangeBlock, game->screen );
      break;
    case 4:
      game->apply_surface( block.box.x, block.box.y, yellowBlock, game->screen );
      break;
    case 5:
      game->apply_surface( block.box.x, block.box.y, greenBlock, game->screen );
      break;
    case 6:
      game->apply_surface( block.box.x, block.box.y, purpleBlock, game->screen );
      break;
    case 7:
      game->apply_surface( block.box.x, block.box.y, redBlock, game->screen );
    default:
      break;
  }
  
}

void PlayState::drawBoard(GameEngine* game)
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
        game->apply_surface( BOARD_ORIGIN_X + offset.x, BOARD_ORIGIN_Y + offset.y, boardTile, game->screen );
      } else {
        int blockType = myBoard->mBoard[x][y];
        int xPos = x * BLOCK_SIZE + BOARD_ORIGIN_X;
        int yPos = y * BLOCK_SIZE + BOARD_ORIGIN_Y;
        
        switch ( blockType )
        {
          case 1:
            game->apply_surface( xPos, yPos, cyanBlock, game->screen );
            break;
          case 2:
            game->apply_surface( xPos, yPos, blueBlock, game->screen );
            break;
          case 3:
            game->apply_surface( xPos, yPos, orangeBlock, game->screen );
            break;
          case 4:
            game->apply_surface( xPos, yPos, yellowBlock, game->screen );
            break;
          case 5:
            game->apply_surface( xPos, yPos, greenBlock, game->screen );
            break;
          case 6:
            game->apply_surface( xPos, yPos, purpleBlock, game->screen );
            break;
          case 7:
            game->apply_surface( xPos, yPos, redBlock, game->screen );
          default:
            break;
        }
      }
    }
  }
}

void PlayState::drawNextContainer(GameEngine* game)
{
  int xOffset = BOARD_ORIGIN_X + BOARD_WIDTH + (BLOCK_SIZE * 2);  // place the container 4 blocks over from our main game board
  int yOffset = BOARD_ORIGIN_Y + (BLOCK_SIZE * 2); // place the container down from where our main board starts by n number of blocks
  
  for (int x = 0; x < 4; x++ )
  {
    for ( int y = 0; y < 4; y++ )
    {
      game->apply_surface( xOffset + ( x * BLOCK_SIZE ), yOffset + ( y * BLOCK_SIZE ), boardTile, game->screen );
    }
  }
}

void PlayState::drawTetriminoQueue(GameEngine* game)
{
  for (int i = 0; i < 5; i++)
  {
    drawNextTetrimino(game, i);
  }
}

void PlayState::drawNextTetrimino(GameEngine* game, int whichTetrimino)
{
  nTetrimino = new Tetrimino(true, queue[whichTetrimino]);
  int xOffset = ( CONTAINER_WIDTH - nTetrimino->getPixelWidth() ) / 2;
  int yOffset = ( CONTAINER_HEIGHT - nTetrimino->getPixelHeight() ) / 2;
  
  for ( int i = 0; i < 4; i++)
  {
    drawBlock( game, nTetrimino->pieceOrigins[i], next, xOffset, yOffset + (whichTetrimino * 56));
  }
  delete(nTetrimino);
}

void PlayState::drawHeldTetrimino(GameEngine* game)
{
  int xOffset = ( CONTAINER_WIDTH - hTetrimino->getPixelWidth() ) / 2;
  int yOffset = ( CONTAINER_HEIGHT - hTetrimino->getPixelHeight() ) / 2;
  
  for ( int i = 0; i < hTetrimino->pieceOrigins.size(); i++)
  {
    drawBlock(game, hTetrimino->pieceOrigins[i], held, xOffset, yOffset );
  }
}

bool PlayState::isGameOver()
{
  for ( int w = 0; w < BOARD_BLOCK_WIDTH; w++ )
  {
    if (myBoard->mBoard[w][0] != 0) { return true; }
  }
  
  return false;
}

bool PlayState::loadAssets( GameEngine* game )
{
  // background image load
  // placeholder for when I decide on a background image
  
  // Load images
  cyanBlock = game->load_image("Tetris.app/Contents/Resources/img/cyanblock.png");
  blueBlock = game->load_image("Tetris.app/Contents/Resources/img/blueblock.png");
  orangeBlock = game->load_image("Tetris.app/Contents/Resources/img/orangeblock.png");
  yellowBlock = game->load_image("Tetris.app/Contents/Resources/img/yellowblock.png");
  greenBlock = game->load_image("Tetris.app/Contents/Resources/img/greenblock.png");
  purpleBlock = game->load_image("Tetris.app/Contents/Resources/img/purpleblock.png");
  redBlock = game->load_image("Tetris.app/Contents/Resources/img/redblock.png");
  
  boardTile = game->load_image("Tetris.app/Contents/Resources/img/boardtile.png");
  boardOutline = game->load_image("Tetris.app/Contents/Resources/img/boardoutline.png");
  
  
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

void PlayState::movementInput()
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

void PlayState::storeTetrimino()
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

int PlayState::checkLines()
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

bool PlayState::lineIsFull( int y )
{
  for ( int x = 0; x < BOARD_BLOCK_WIDTH; x++ )
  {
    if ( myBoard->mBoard[x][y] == 0 )
      return false;
  }
  
  return true;
}

void PlayState::deleteLine( int y )
{
  for ( int x = 0; x < BOARD_BLOCK_WIDTH; x++ )
  {
    myBoard->updateBlock( x, y, 0 );
  }
}

void PlayState::dropLines( int y )
{
  for ( int x = 0; x < BOARD_BLOCK_WIDTH; x++ )
  {
    for ( int h = y; h > 0; h-- )
    {
      myBoard->mBoard[x][h] = myBoard->mBoard[x][h-1];
    }
  }
}

void PlayState::displayTimer( GameEngine* game, int time, int x, int y )
{
  SDL_Surface *timer = NULL;
  // Timer's time as string
  stringstream timeString;
  
  // Convert the timer's time to a string
  timeString << "Timer: " << time / 1000;
  
  // Render the time surface
  timer = TTF_RenderText_Shaded( font, timeString.str().c_str(), fontFgColor, fontBgColor );
  
  // Apply the time surface
  game->apply_surface( ( x - ( timer->w / 2 ) ) , ( y - ( timer->h / 2 ) ) , timer, game->screen );
  
  // Free the time surface
  SDL_FreeSurface ( timer );
}

void PlayState::displayText(GameEngine* game, string text, Sint16 x, Sint16 y, Uint8 fR, Uint8 fG, Uint8 fB, Uint8 bR, Uint8 bG, Uint8 bB)
{
  
  SDL_Color foreground = { fR, fG, fB };  // Text foreground color
  SDL_Color background = { bR, bG, bB };  // Text background color
  
  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, text.c_str(), foreground, background); // Render our text to temporary text surface
  
  game->apply_surface( ( x - ( textSurface->w / 2 ) ) , ( y - ( textSurface->h / 2 ) ), textSurface, game->screen);  // call apply_surface function using our newly setup text surface
  
  SDL_FreeSurface(textSurface); // Free dem memories!
}

void PlayState::drawInterface(GameEngine* game)
{
  game->apply_surface(BOARD_ORIGIN_X - 96 , BOARD_ORIGIN_Y - 45, boardOutline, game->screen);
}

void PlayState::holdTetrimino()
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

void PlayState::nextTetrimino()
{
  // move next to active and spawn a new next
  //aTetrimino = nTetrimino;
  //nTetrimino = new Tetrimino(true);
  
  aTetrimino = new Tetrimino( true, queue.front() );
  queue.pop_front();
  queue.push_back( bag->getNextPiece() );
  
}

void PlayState::fillQueue()
{
  for ( int i = 0; i < 5; i++ ){
    queue.push_back( bag->getNextPiece() );
  }
}

void PlayState::interfaceInput(GameEngine* game)
{
  switch (event.type)
  {
    case SDL_QUIT:
      game->Quit();
      break;
      
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          game->PushState( MenuState::Instance() );
          break;
        case SDLK_p:
          game->PushState( PauseState::Instance() );
          break;
      }
      break;
  }
}