# space-puzzle-matrix

A puzzle matrix module designed for a space panel to be used by the Christa McAuliffe Space Center.

## Overview

![alt text](<Mario Matrix Idea.png>)

The matrix module will be a matrix of 6x6 LED buttons that will allow different puzzles to be played. The matrix will also have a small LCD display and 3 additional buttons for added functionality. The games will be played on the button matrix and encourage problem-solving and critical thinking skills.

## Games

The games will be programmed with scalable difficulty. A few games that will be implemented:

- **Puzzle Panel**: Tap one tile to flip the surrounding tiles. You have a limited number of flips to match the reference matrix, and the number of flips increases with difficulty. Based on [this game from NSMBDS](https://www.youtube.com/watch?v=6mqAMbGBhQw&t=35s).
- **Simon Says**: One button will light up, then the player must push that button. Then, a sequence of two buttons will light up on after the other, and the player must push those buttons in the order they appeared. This is essentially just a normal game of simon says, played on a larger matrix.
- **Minesweeper**: Several mines will be placed on the matrix that the player cannot see. When a player taps on a tile, it lights up, and its color indicates the number of mines adjacent to it.
- **Flow**: Connect several pipes to allow water to flow from them. Each pipe has two endpoints on the matrix, and the player connects the endpoints by pushing adjacent buttons to create a path.
- **Maze**: A maze randomly generates on the matrix, and the player has to draw a path from the start to the finish to succeed. In higher difficulties the player's path must be the shortest possible path in order to succeed.

## Design Process

...

## Hardware

...

## Software

...
