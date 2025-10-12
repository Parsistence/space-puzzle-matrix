## Puzzle Panel
### Basics
Tap one tile to flip the surrounding tiles. You have a limited number of flips to match the reference matrix, and the number of flips increases with difficulty. Based on [this game from New Super Mario Bros DS](https://www.youtube.com/watch?v=6mqAMbGBhQw&t=5s).
### Code Implementation
1. Generate a Grid
   * Use a clear pattern for easier skill levels
   * Use a randomized grid for more skilled user
2. Computer randomly picks 1-3 tiles to apply a flip to
   * Make sure the computer never flips the same tile twice in a row
   * For easier levels: Don't worry about overlap between flipped squares
   * For harder levels: Make sure every flip overlaps at least a little with previous ones
3. Player is given 1-3 turns to make flips. Display shows the desired result, lives left, turns left, etc.
## Flow
### Basics
Connect several pipes to allow water to flow from them. Each pipe has two endpoints on the matrix, and the player connects the endpoints by pushing adjacent buttons to create a path.
### Code Implementation
## Minesweeper
### Basics
Several mines will be placed on the matrix that the player cannot see. When a player taps on a tile, it lights up, and its color indicates the number of mines adjacent to it.
### Code Implementation
## Navigator
### Basics
A maze randomly generates on the matrix, and the player has to draw a path from the start to the finish to succeed. In higher difficulties the player's path must be the shortest possible path in order to succeed.
### Code Implementation
## Simon Says
### Basics
One button will light up, then the player must push that button. Then, a sequence of two buttons will light up on after the other, and the player must push those buttons in the order they appeared. This is essentially just a normal game of simon says, played on a larger matrix.
### Code Implementation
Harder difficulties will have longer patterns, faster patterns, or more colors/panels active
