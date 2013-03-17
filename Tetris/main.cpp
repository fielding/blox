//
//  main.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/14/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Timer.h"

using namespace std;

// Screen Attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 20;

// Tetris Board Attributes
const int BLOCK_SIZE = 16;    // Block size in pixels
const int BOARD_BLOCK_WIDTH = 10;   // Board width in blocks
const int BOARD_BLOCK_HEIGHT = 20;  // Board height in blocks
const int BOARD_WIDTH = BOARD_BLOCK_WIDTH * BLOCK_SIZE;   // Board width in pixels    
const int BOARD_HEIGHT = BOARD_BLOCK_HEIGHT * BLOCK_SIZE;   // Board height in pixels

const int BOARD_ORIGIN_X = 560;   // X- origin position the board appears on the screen
const int BOARD_ORIGIN_Y = 224;   // Y-origin position the board appears on the screen

// Surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *board = NULL;
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

SDL_Surface *load_image( string filename );

// Event Structure
SDL_Event event;

// Font, font fg color and font bg color
TTF_Font *font = NULL;
SDL_Color fontFgColor = { 0, 0, 0 };
SDL_Color fontBgColor = { 255, 255, 255 };

// Block Class
class Block
{
  
public:
  Block( int x, int y, int bType );
  
  // Watch key events and adjsut velocity
  void handle_input();
  
  // move the object
  void move();
  
  // Shows the oject on the screen
  void show();
  
private:
  // The collision box of the square; object's x/y coordinates and dimensions are held inside a SDL_Rect
  SDL_Rect box;
  
  // Velocity
  int xVel, yVel;
  
  // Define type (mainly used to determine the block color
  int blockType;

  
};

class Board
{
public:
  
  // Constructor
  Board( int blockWidth, int blockHeight );
  
  // Functions
  void draw();
  void updateBlock(int x, int y, int status);
  
private:
  int mBoard[BOARD_BLOCK_WIDTH][BOARD_BLOCK_HEIGHT];
  
};

// Tetromino Class
class Tetrimino
{
public:
  
  // Constructor
  Tetrimino();
  
  // public classes
  void spawn( Board &myBoard );

private:
  
};

// Function definitions
void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
bool check_collision( SDL_Rect A, SDL_Rect B );
void clean_up();
bool init();
bool load_files();

int main ( int argc, char **argv )
{
  // Exit flag
  bool exit = false;
  
  // framerate variables
  int frame = 0;
  bool cap = true;
  
  // Initialize
  if ( init() == false )
  {
    return 1;
  }
  
  // Load files
  if ( load_files() == false )
  {
    return 1;
  }
  
  // Creat Game Board Object
  Board myBoard( BOARD_BLOCK_WIDTH, BOARD_BLOCK_HEIGHT );
  
  // Create Tetrimino
  Tetrimino tetrimino;
  // spawn a tetrimino
  tetrimino.spawn( myBoard );
  
  
  // Create timer objects
  Timer::Timer globalTimer;  // global timer
  Timer::Timer playTimer;   // Time game has been in play
  Timer::Timer fps;      // Timer used to calculate the frames per second
  Timer::Timer update;   // Timer to update fps caption
  
  // Start overall timers
  globalTimer.start();
  playTimer.start();
  update.start();
  
  // Game Loop
  while ( exit == false )
  {
    // Start the frame timer
    fps.start();
    
    // Game Loop: Events
    while ( SDL_PollEvent( &event ) )
    {
      // Watch for keybord events
      //square.handle_input();
      
      // If a key was pressed
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
        
        // If F was pressed
        if ( event.key.keysym.sym == SDLK_f )
        {
          // Turn fps cap off
          cap = ( !cap );
        }
        
      }
      
      // Check if the user x's out of the window
      if ( event.type == SDL_QUIT )
      {
        // Quit the progam
        exit = true;
      }
    }
    
    // Game Loop: Logic
    // Move the square
    // mySquare.move();
    
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

    // Draw the board
    myBoard.draw();
    
    // Draw the square to the screen
    // mySquare.show();
  
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
    if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
    {
      // Sleep the remaining time
      SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    }
  }
  
  // Clean up
  clean_up();
  
  return 0;
}

SDL_Surface *load_image( string filename )
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

// Block class function definitons

Block::Block(int x, int y, int bType)
{
  // Initialize offsets
  box.x = x * BLOCK_SIZE + BOARD_ORIGIN_X;
  box.y = y * BLOCK_SIZE + BOARD_ORIGIN_Y;
  
  // Set the square's dimensions
  box.w = BLOCK_SIZE;
  box.h = BLOCK_SIZE;
  
  // Type (used for color)
  blockType = bType;
  
  // Initialize velocity
  xVel = 0;
  yVel = 0;
  
}

void Block::handle_input()
{
  if ( event.type == SDL_KEYDOWN )      // If a key was presed
  {
    switch ( event.key.keysym.sym )
    {
      case SDLK_UP:
        yVel -= BLOCK_SIZE / 2;
        break;
      case SDLK_DOWN:
        yVel += BLOCK_SIZE / 2;
        break;
      case SDLK_LEFT:
        xVel -= BLOCK_SIZE / 2;
        break;
      case SDLK_RIGHT:
        xVel += BLOCK_SIZE / 2;
        break;
      default:
        break;
    }
  }
  else if ( event.type == SDL_KEYUP )   // If a key was released
  {
    switch ( event.key.keysym.sym )
    {
      case SDLK_UP:
        yVel += BLOCK_SIZE / 2;
        break;
      case SDLK_DOWN:
        yVel -= BLOCK_SIZE / 2;
        break;
      case SDLK_LEFT:
        xVel += BLOCK_SIZE / 2;
        break;
      case SDLK_RIGHT:
        xVel -= BLOCK_SIZE / 2;
        break;
      default:
        break;
    }
  }
}

void Block::move()
{

  box.x += xVel;      // Move left or right
  
  if ( ( box.x < 0 ) || ( box.x + BLOCK_SIZE > SCREEN_WIDTH ) )     // Check x-axis screen bounds
  {
    box.x -= xVel;    // Move back
  }

  box.y += yVel;      // Move the square up or down
  
  if ( ( box.y < 0 ) || (box.y + BLOCK_SIZE > SCREEN_HEIGHT) )     // Check y-axis screen bounds
  {
    box.y -= yVel;    // Move Back
  }
  
}

void Block::show()
{
  switch ( blockType )
  {
    case 1:
      apply_surface( box.x, box.y, cyanBlock, screen );
      break;
    case 2:
      apply_surface( box.x, box.y, blueBlock, screen );
      break;
    case 3:
      apply_surface( box.x, box.y, orangeBlock, screen );
      break;
    case 4:
      apply_surface( box.x, box.y, yellowBlock, screen );
      break;
    case 5:
      apply_surface( box.x, box.y, greenBlock, screen );
      break;
    case 6:
      apply_surface( box.x, box.y, purpleBlock, screen );
      break;
    case 7:
      apply_surface( box.x, box.y, redBlock, screen );
    default:
      break;
  }
}

// Timer class function definitions



// Board class function definitions
Board::Board( int blockWidth, int blockHeight )
{
  // populate the board grid with empty blocks
  for ( int x = 0; x < blockWidth; x++ )
  {
    for ( int y = 0; y < blockHeight; y++)
    {
      mBoard[x][y] = 0;
    }
  }
}

void Board::draw(){
  for ( int x = 0; x < BOARD_WIDTH / BLOCK_SIZE; x++ )
  {
    for ( int y = 0; y < BOARD_HEIGHT / BLOCK_SIZE; y++ )
    {
      // If block is empty then use a board tile
      if ( mBoard[x][y] == 0 )
      {
        SDL_Rect offset;
        offset.x = x * BLOCK_SIZE;
        offset.y = y * BLOCK_SIZE;
        apply_surface( BOARD_ORIGIN_X + offset.x, BOARD_ORIGIN_Y + offset.y, boardTile, screen );
      } else {
        int blockType = mBoard[x][y];
        Block block( x, y, blockType);
        block.show();
        //SDL_Rect offset;
        //offset.x = x * BLOCK_SIZE;
        //offset.y = y * BLOCK_SIZE;
        //apply_surface( BOARD_ORIGIN_X + offset.x, BOARD_ORIGIN_Y + offset.y, square, screen );
      }
    }
  }
}

void Board::updateBlock( int x, int y, int status )
{
  mBoard[x][y] = status;
}

Tetrimino::Tetrimino() {
  
}

void Tetrimino::spawn( Board &myBoard ){
  // randomize the Tetrimino chosen
  int rando = 0;
  srandom((unsigned)time(NULL));
  rando = (random() % 7 + 1);
  
  cout<<"Tetrimino spawn type: "<<rando<<"\n";
  cout<<((unsigned)time(NULL))<<endl;
  
  switch ( rando ) {
    case 1:   // I piece, blockType = 1 (cyan)
      myBoard.updateBlock(3, 0, 1);
      myBoard.updateBlock(4, 0, 1);
      myBoard.updateBlock(5, 0, 1);
      myBoard.updateBlock(6, 0, 1);
      break;
    case 2:   // J piece, blockType = 2 (blue)
      myBoard.updateBlock(3, 0, 2);
      myBoard.updateBlock(4, 0, 2);
      myBoard.updateBlock(5, 0, 2);
      myBoard.updateBlock(5, 1, 2);
      break;
    case 3:   // L piece, blockType = 3 (orange)
      myBoard.updateBlock(3, 0, 3);
      myBoard.updateBlock(4, 0, 3);
      myBoard.updateBlock(5, 0, 3);
      myBoard.updateBlock(3, 1, 3);
      break;
    case 4:   // O piece, blockType = 4 (yellow)
      myBoard.updateBlock(4, 0, 4);
      myBoard.updateBlock(5, 0, 4);
      myBoard.updateBlock(4, 1, 4);
      myBoard.updateBlock(5, 1, 4);
      break;
    case 5:   // S piece, blockType = 5 (green)
      // update the blocks
      myBoard.updateBlock(4, 0, 5);
      myBoard.updateBlock(5, 0, 5);
      myBoard.updateBlock(3, 1, 5);
      myBoard.updateBlock(4, 1, 5);
      break;
    case 6:   // T piece, blockType = 6 (purple)
      myBoard.updateBlock(4, 0, 6);
      myBoard.updateBlock(3, 1, 6);
      myBoard.updateBlock(4, 1, 6);
      myBoard.updateBlock(5, 1, 6);
      break;
    case 7:   // Z piece, blockType = 7 (red)
      myBoard.updateBlock(3, 0, 7);
      myBoard.updateBlock(4, 0, 7);
      myBoard.updateBlock(4, 1, 7);
      myBoard.updateBlock(5, 1, 7);
      break;
  }
}


// Functions

void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip )
{
  // Store and get offsets
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  // Blit
  SDL_BlitSurface( source, clip, destination, &offset );
}

bool check_collision( SDL_Rect A, SDL_Rect B )
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
  return true;
}

void clean_up()
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

bool load_files()
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

bool init()
{
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