//
//  Constants.cpp
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#include "Constants.h"

// Screen Attributes
const int SCREEN_WIDTH = 432;
const int SCREEN_HEIGHT = 496;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 30;

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