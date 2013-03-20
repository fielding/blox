# Tetris

### Todo
* Hold tetrinome functionality
* Score system/Displaying score
* Create/Polish UI
* Piece Silhouette (outline showing where the piece will land based on current position)
* Holding down movement keys

### Consider
* Changing playTimer (timer that is displayed as part of the UI) to a float
* Breaking up Game class in to IO (rendering/key events) and Game (game logic only)
* Revisit the rotation function, some of the pivot points seem off a bit

### Bugs
* Rotation ignores block collision
* Rotation ignores left, right and bottom board boundaries. (Ignores top as well, but I restricted the drawing above the board to continue to allow it to ignore the top boundary)