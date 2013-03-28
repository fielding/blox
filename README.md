# Tetris

### Todo
* Score system/Displaying score
* Create/Polish UI
* Holding down movement keys
* Wall kicks!

### Consider
* Changing playTimer (timer that is displayed as part of the UI) to a float
* Breaking up PlayState class in to IO (rendering/key events) and game logic, instead of one big class
* Revisit the rotation function, some of the pivot points seem off a bit

### Bugs
* Rotation ignores block collision
* Rotation ignores left, right and bottom board boundaries. (Ignores top as well, but I restricted the drawing above the board to continue to allow it to ignore the top boundary)
* Menu stays visible when MenuState is called while in PauseState. For the time being, I’m disabling MenuState while in PauseState and GameOverState. Might look in to fixing the redraw issue later.
* Movement while a tetrimino has any block with a y < 0 is really restricted/non-working
* 