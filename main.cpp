#include <iostream>
#include "raylib.h"

#include "logic.h"
#include "graphics.h"


const int screenWidth = 800;
const int screenHeight = 600;


int main(){

	//	Initialization 

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);

	//srand(time(NULL));
	// Global Parameters
	Vector2 GridRatio = {10,20};
	int Scale = 20;

	cube *cb;

	Vector2 st;
	
	//	Main game loop
	while (!WindowShouldClose()){

		
		BeginDrawing();

		
		DrawFPS(10, 10);
		ClearBackground(BLACK);

		st = MakeGrid(GridRatio, Scale);

		// Cube testing
		cb = new cube(st, Vector2{(float)Scale, (float)Scale});


		EndDrawing();

	}

	return 0;
}