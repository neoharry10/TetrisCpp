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

	Vector2 GridRatio = {10,20};

	
	//	Main game loop
	while (!WindowShouldClose()){

		
		BeginDrawing();

		
		DrawFPS(10, 10);
		ClearBackground(BLACK);

		MakeGrid(GridRatio);

		EndDrawing();

	}

	return 0;
}