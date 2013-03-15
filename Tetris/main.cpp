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

using namespace std;

// Screen Attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 20;

// Square Attributes
const int SQUARE_HEIGHT = 16;
const int SQUARE_WIDTH = 16;

// Surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *square = NULL;

// Message Surfaces
SDL_Surface *seconds = NULL;
SDL_Surface *startStop = NULL;
SDL_Surface *pauseMessage = NULL;
SDL_Surface *mainMessage = NULL;

SDL_Surface *load_image( string filename );

// Wall objct
SDL_Rect wall;

// Event Structure
SDL_Event event;

// Font, font fg color and font bg color
TTF_Font *font = NULL;
SDL_Color fontFgColor = { 0, 0, 0 };
SDL_Color fontBgColor = { 255, 255, 255 };

// Square Class 
class Square
{
  
public:
  Square();
  
  // Watch key events and adjsut velocity
  void handle_input();
  
  // move the object
  void move();
  
  // Shows the oject on the screen
  void show();
  
private:
  // The collision box of the square; object's x/y coordinates and dimensions are held inside a SDL_Rect
  SDL_Rect box;
  
  //The velocity
  int xVel, yVel;
  
};

// Timer Class
class Timer
{
  
public:
  // Constructor, Initializes variables
  Timer();
  
  // Various clock functions
  void start();
  void stop();
  void pause();
  void unpause();
  
  // Get timer's time in milliseconds
  int get_ticks();
  
  // Check timer's status, returns true or false
  bool is_started();
  bool is_paused();
  
private:
  // The clock when the timer started
  int startTicks;
  
  // The ticks stored when the timer was paused
  int pausedTicks;
  
  // Timer status
  bool paused;
  bool started;
  
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
  
  // Create a square object
  Square mySquare;

  // Create timer objects
  Timer globalTimer;  // global timer
  Timer playTimer;   // Time game has been in play
  Timer fps;      // Timer used to calculate the frames per second
  Timer update;   // Timer to update fps caption
  
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
  
  // framerate variables
  int frame = 0;
  bool cap = true;
  
  // Generate timer messages
  startStop = TTF_RenderText_Shaded( font, "Press T to start or stop the timer", fontFgColor, fontBgColor);
  pauseMessage = TTF_RenderText_Shaded( font, "Press P to start or stop the timer", fontFgColor, fontBgColor);
  //mainMessage = TTF_RenderText_Shaded( font, "", fontFgColor, fontBgColor);
  
  // Start overall timers
  globalTimer.start();
  playTimer.start();
  update.start();
  
  // Set the wall attributes
  wall.x = 616;
  wall.y = 48;
  wall.w = 48;
  wall.h = 400;
  
  // Game Loop
  while ( exit == false )
  {
    // Start the frame timer
    fps.start();
    
    // Game Loop: Events
    while ( SDL_PollEvent( &event ) )
    {
      // Watch for keybord events
      mySquare.handle_input();
      
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
    mySquare.move();
    
    // Game Loop: Rendering
    // Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
    // Apply the background if I'm using a background image
    // apply_surface( 0, 0, background, screen );
    
    // Apply the messages
    apply_surface( ( SCREEN_WIDTH - startStop->w ) / 2, 500, startStop, screen );
    apply_surface( ( SCREEN_WIDTH - pauseMessage->w) / 2, 550, pauseMessage, screen);
    //apply_surface( (SCREEN_WIDTH - mainMessage->w) / 2, ( (SCREEN_HEIGHT + mainMessage->h * 2 ) / FRAMES_PER_SECOND ) * ( frame % FRAMES_PER_SECOND ) - mainMessage->h, mainMessage, screen );
    
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
  
    // Draw the wall
    SDL_FillRect( screen, &wall, SDL_MapRGB( screen-> format, 255, 122, 0 ) );
    
    // Draw the square to the screen
    mySquare.show();
  
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

// Square class function definitons

Square::Square()
{
  // Initialize offsets
  box.x = 0;
  box.y = 0;
  
  // Set the square's dimensions
  box.w = SQUARE_WIDTH;
  box.h = SQUARE_HEIGHT;
  
  // Initialize velocity
  xVel = 0;
  yVel = 0;
  
}

void Square::handle_input()
{
  if ( event.type == SDL_KEYDOWN )      // If a key was presed
  {
    switch ( event.key.keysym.sym )
    {
      case SDLK_UP:
        yVel -= SQUARE_HEIGHT / 2;
        break;
      case SDLK_DOWN:
        yVel += SQUARE_HEIGHT / 2;
        break;
      case SDLK_LEFT:
        xVel -= SQUARE_WIDTH / 2;
        break;
      case SDLK_RIGHT:
        xVel += SQUARE_WIDTH / 2;
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
        yVel += SQUARE_HEIGHT / 2;
        break;
      case SDLK_DOWN:
        yVel -= SQUARE_HEIGHT / 2;
        break;
      case SDLK_LEFT:
        xVel += SQUARE_WIDTH / 2;
        break;
      case SDLK_RIGHT:
        xVel -= SQUARE_WIDTH / 2;
        break;
      default:
        break;
    }
  }
}

void Square::move()
{

  box.x += xVel;      // Move left or right
  
  if ( ( box.x < 0 ) || ( box.x + SQUARE_WIDTH > SCREEN_WIDTH ) || (check_collision( box, wall ) ) )     // Check x-axis screen bounds and collision with wall
  {
    box.x -= xVel;    // Move back
  }

  box.y += yVel;      // Move the square up or down
  
  if ( ( box.y < 0 ) || (box.y + SQUARE_HEIGHT > SCREEN_HEIGHT) || (check_collision( box, wall ) ) )     // Check y-axis screen bounds and collision with wall
  {
    box.y -= yVel;    // Move Back
  }
  
}

void Square::show()
{
  // Draw object on the screen
  apply_surface( box.x, box.y, square, screen );
}

// Timer class function definitions

Timer::Timer()
{
  // Constructor function, initalizes the variables
  startTicks = 0;
  pausedTicks = 0;
  paused = false;
  started = false;
}

void Timer::start()
{
  // Start the timer
  started = true;
  
  // Unpause the timer
  paused = false;
  
  // Get the current clock time
  startTicks = SDL_GetTicks();
}

void Timer::stop()
{
  // Stop the timer
  started = false;
  // Unpause the timer
  paused = false;
}

void Timer::pause()
{
  // If the timer is already running and isn't already paused
  if ( (started == true ) && ( paused == false ) )
  {
    // Pause the timer
    paused = true;
    
    // Calculate the paused ticks
    pausedTicks = SDL_GetTicks() - startTicks;
  }
}

void Timer::unpause()
{
  // If the timer is paused
  if ( paused == true )
  {
    // Unpause
    paused = false;
    
    // Reset the starting ticks
    startTicks = SDL_GetTicks() - pausedTicks;
    
    // Reset the paused ticks
    pausedTicks = 0;
  }
}

int Timer::get_ticks()
{
  // If the timer is running
  if( started == true )
  {
    // If the timer is paused
    if ( paused == true )
    {
      // Return the number of ticks when the timer was paused
      return pausedTicks;
    }
    else
    {
      // Return current time minus the start time
      return SDL_GetTicks() - startTicks;
    }
  }
  
  // If the timer isn't running
  return 0;
}

bool Timer::is_started()
{
  return started;
}

bool Timer::is_paused()
{
  return paused;
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
  SDL_FreeSurface(square);
  
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
  
  // Load the square's image
  square = load_image("Tetris.app/Contents/Resources/greensquare.png");
  
  // Load font
  font = TTF_OpenFont( "Tetris.app/Contents/Resources/HelveticaNeueCondensedBold.ttf", 28);

  // Check if images loaded properly
  if ( square == NULL ) {
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