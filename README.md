# Blox
## A Tetronimo game

### Todo
* Finish menuState
* Holding down movement keys
* “Juice”
* T-Spin scoring
* Analyze the forcetime increments per level (too fast or too slow)
* Lock delay

### Consider
* Change the pieces to spawn at y=0 instead of y=2; This causes them to spawn out of view, but is more inline with T-compliance. 
* Displaying playTimer ? If I do then float or int?
* Creating a renderer service, similar to the audio service and how audio is handled.
* Double check the pivot points/pivot algorithm again (already revisted once and corrected some errors)

### Someday/Maybe
* Finding work around for shaped windows in SDL. SDL doesn’t currently support SDL_CreateShapedWindow for OS X, afaik. Revisit this when it does, or look at alternative to SDL. This is definitely not a limitation I want any future games to have.
* Menu stays visible when MenuState is called while in PauseState. For the time being, I’m disabling MenuState while in PauseState, and forcing menuState when it goes to gameOver state. Will look in to a more elegant solution later, but due to the nature that I implemented drawing/redrawing in each gamestate, I don’t predict an easy solution.
* Revamp the sound effects. Here is a list of potential (keyword) sound additions
	* Different sounds, perhaps just higher pitch, for line clears based on the number of lines cleared.
	* T-spin sounds
	* Wall Kick Sounds
	* Interface sounds
	* Level change sound
	* Hold sound

### Bugs

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
			
