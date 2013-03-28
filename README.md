# Blox
## A Tetronimo game



### Todo
* Score system/Displaying score
* Create/Polish UI
* Holding down movement keys
* Wall kicks!

### Consider
* Changing playTimer (timer that is displayed as part of the UI) to a float
* Breaking up PlayState class in to IO (rendering/key events) and game logic, instead of one big class
* Revisit the rotation function, some of the pivot points seem off a bit
* Finding work around for shaped windows in SDL. SDL doesn’t currently support SDL_CreateShapedWindow for OS X, afaik. Revisit this when it does, or look at alternative to SDL. This is definitely not a limitation I want any future games to have.

### Bugs
* Rotation ignores block collision
* Rotation ignores left, right and bottom board boundaries. (Ignores top as well, but I restricted the drawing above the board to continue to allow it to ignore the top boundary)
* Menu stays visible when MenuState is called while in PauseState. For the time being, I’m disabling MenuState while in PauseState and GameOverState. Might look in to fixing the redraw issue later.
* Movement while a tetrimino has any block with a y < 0 is really restricted/non-working


## Game Play
### Scoring

| Action | Points |
| ——— | ——— |
| Single | 100 x Level |
| Double | 300 x Level | 
| Triple | 500 x Level |
| Tetris | 800 x Level; considered “difficult” |
| Back to back difficult line clears | ((score)x3) / 2 (example: back to back tetris is 1200 x level) |





