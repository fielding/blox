//
//  Constants.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "Constants.h"

// Game Loop Timing
const int TICKS_PER_SECOND = 30;  // how many times the game is updated per second (independent of the rendering frame rate)
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND; // calculation used to determine how many ticks to wait between updating
const int MAX_FRAMESKIP = 5;  // Max amount of frames we can skip if the framerate takes a dip
const int FRAMES_PER_SECOND = 60; // used if I need to set a specific framerate for testing, currently unused, but might implement for testing how the game will run at lower framerates


// Screen Attributes
const int SCREEN_WIDTH = 432;
const int SCREEN_HEIGHT = 496;
const int SCREEN_BPP = 32;

// Board Attributes

const int BLOCK_SIZE = 16;    // Block size in pixels
const int BOARD_BLOCK_WIDTH = 10;   // Board width in blocks
const int BOARD_BLOCK_HEIGHT = 22;  // Board height in blocks
const int BOARD_WIDTH = BOARD_BLOCK_WIDTH * BLOCK_SIZE;   // Board width in pixels
const int BOARD_HEIGHT = BOARD_BLOCK_HEIGHT * BLOCK_SIZE;   // Board height in pixels

const int BOARD_ORIGIN_X = 136;   // X-origin position the board appears on the screen
const int BOARD_ORIGIN_Y = 32;   // Y-origin position the board appears on the screen

const int NC_ORIGIN_X = BOARD_ORIGIN_X + 176;    // X-origin for the next container
const int NC_ORIGIN_Y = BOARD_ORIGIN_Y + 31;   // Y-origin for the next container

const int HC_ORIGIN_X = BOARD_ORIGIN_X - 88; // X-origin for the held container
const int HC_ORIGIN_Y = BOARD_ORIGIN_Y + 31; // Y-origin for the held container

const int CONTAINER_WIDTH = 72;
const int CONTAINER_HEIGHT = 48;

// Logic/Gameplay Settings
const int LOCK_DELAY_MAX = 2000;
const int DAS_DELAY_TIME = 200;
const int AUTO_REPEAT_RATE = 50;


