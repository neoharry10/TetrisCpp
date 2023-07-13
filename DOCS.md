# Notes

## Structure 

Two core files, logic.cpp, graphics.cpp
Each is called in main.cpp inside a game loop in the order logic->graphics

- logic.cpp


Input
Collisions (Check if a box is in bounds : box.x > st.x && box.x < st.x + ratio.x*scale , *same for y*)
Game states

- graphics.cpp

Updates the graphics given information from logic

## TODO 

-> Merge testing into main

-> pieces

-> tick

-> score

-> Make a super class called drawable, with specs for a Draw function. Every drawable's Draw will be called from the main game loop every frame. It will be its class' job to decide when to draw.

## Doing

Figure out how to handle collisions
and handle the spawn, move and place loop using the tick