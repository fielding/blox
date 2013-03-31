# Blox
## A Tetronimo game

### Todo
* Finish menuState
* Increase forcetime based on level in marathon mode
* Holding down movement keys
* Audio
* “Juice”
* T-Spin scoring

### Consider
* Changing playTimer (timer that is displayed as part of the UI) to a float
* Breaking up PlayState class in to IO (rendering/key events) and game logic, instead of one big class
* Revisit the rotation function, some of the pivot points seem off a bit

### Someday/Maybe
* Finding work around for shaped windows in SDL. SDL doesn’t currently support SDL_CreateShapedWindow for OS X, afaik. Revisit this when it does, or look at alternative to SDL. This is definitely not a limitation I want any future games to have.

### Bugs
* Rotation ignores block collision
* Rotation ignores left, right and bottom board boundaries.
* Menu stays visible when MenuState is called while in PauseState. For the time being, I’m disabling MenuState while in PauseState and GameOverState. Might look in to fixing the redraw issue later.
* First Tetrimino seems to be ignoring the random generation algorithm, or getting around it some how... need to look in to and do analysis on the random generation of the tetrominos.

## Game Play

### Scoring
#### Scoring Values Of Each Move

Awarded points are always a function of the current level. The scoring system is designed to reward advanced moves. For example, a Double is worth more than twice a Single.

<table>
	<tr>
		<th>Action</th><th>Awarded Points</th>
	</tr>
	<tr>
		<td>Single</td><td>100 * Level</td>
	</tr>
	<tr>
		<td>Double</td><td>300 * Level</td>
	</tr>
	<tr>
		<td>Triple</td><td>500 * Level</td>
	</tr>
	<tr>
		<td>Tetris</td><td>800 * Level</td>
	</tr>
	<tr>
		<td>Back-to-Back Bonus</td><td>Action Total + (.5 * Action Total)</td>
	</tr>
	<tr>
		<td>Soft Drop</td><td>1 * n</td>
	</tr>
	<tr>
		<td>Hard Drop</td><td> 2 * m</td>
	</tr>
</table>

* _Action Total equals the number of performed sequential moves._
* _n equals the number of lines you allow the Tetrimino to Soft Drop._
* _m equals the total distance of the Hard Drop._


#### Line Clear Value Of Each Move

In order to advance a level, you must clear a certain number of lines. This line goal is determined by the current level. Each level has a goal equal to the level number * 5. For instance, level 1 takes 5 lines to complete, and, likewise, level 3 takes 15 lines to complete.
	
It is important to understand that certamin moves are worth more than the raw number of lines they clear. A double only clears two lines, but since the scoring system favors more difficult moves, a double awards 3 line clears toward your current goal.

<table>
	<tr>
		<th>Action</th><th>Awarded Line Clears</th>
	</tr>
	<tr>
		<td>Single</td><td>1</td>
	</tr>
	<tr>
		<td>Double</td><td>3</td>
	</tr>
	<tr>	
		<td>Triple</td><td>5</td>
	</tr>
	<tr>	
		<td>Tetris</td><td>8</td>
	</tr>
	<tr>
		<td>Back-to-Back Bonus</td><td>0.5 * Total Line Clears</td>
	</tr>
</table>
			
