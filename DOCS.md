# Notes

## Structure 

- logic.h / logic.cpp

All of the classes, helper functions 

- Main loop 

The tick function, of the grid, is upodated every '1.5'(updTime) secs to give the tetris effect

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

-> screens, menu, different game over  

-> Main Menu ?

## Doing

-> Game Over , after screens ?


## ERRORS 

- Pieces clash on empty spaces sometimes, "int** Coords" not updating correctly perhaps  


## Check Out 

## Plan

Menu :
    menu.h menu.cpp

menu.cpp :
    menu loop

Game :
    game.h game.cpp

game.cpp :
    game loop