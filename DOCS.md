# Notes

## Structure 
- 3 States / Loop - Screens

Menu, Game, GameOver 

Menu is the welcome screen
Game is the main screen
GameOver is when you lose, get your score and select if you'll play again

### Game Loop 

- logic.h / logic.cpp

All of the classes, helper functions 

- Coordinate system and positions

The local coords in the grid is a 2d int array, ratio.x * ratio.y, global coords is raylib coords.
(I have functions to convert between the two: GetLocalPos, GetGlobalPos ) 

* GstPos (GLOBAL init in main), which is the top-left anchor of the grid.
* Gscale (GLOBAL init in main), is the length of each 'box' in the grid. (Increasing the scale will make the grid larger)
* Offset (Piece specific), is the length from top-left to the middle, from there spawns each piece 

-- Classes
- Grid

The grid has a ratio, x * y, used for the local grid. (0,x-1)*(0,y-1) are the usable grid places 


## TODO


-> Leadboard ?
-> Online ??

## Doing



## ERRORS / UGS

- ( Pieces clash on empty spaces sometimes, "int** Coords" not updating correctly perhaps )




# Releases

## Current : V1

## V1 

-> All the functionality of a game that is similar to tetris
