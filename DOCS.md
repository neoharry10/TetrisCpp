# Notes

## Structure 

- logic.cpp


Input
Collisions (Check if a box is in bounds : box.x > st.x && box.x < st.x + ratio.x*scale , *same for y*)
Game states

- Main loop 

I update the 'logic' every 1.5 secs from the tick function in the grid

- Coordinate system and positions

The coords in the grid is a 2d int array, ratio.x * ratio.y

* GstPos (GLOBAL init in main), which is the top-left anchor of the grid.
* Gscale (GLOBAL init in main), is the length of each 'box' in the grid. (Increasing the scale will make the grid larger)
* Offset (Piece specific), is the length from top-left to the middle, from there spawns each piece 

## TODO


-> Rotation
-> score
-> Game Over screen 

-> Main Menu ?

## Doing

Rotations, find a way to 'autorotate' the cubes without manually writing every cube cord. maybe with cos/sin




## ERRORS 



## Check Out 

