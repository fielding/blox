# Blox
A tetronimo game

## Game Play

### Features
* Lock Delay (non-infinity)
* DAS (Delayed Auto Shift)
* SRS Rotation System

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
			
