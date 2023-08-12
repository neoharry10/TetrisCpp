#include <iostream>
#include "raylib.h"

#include "logic.h"


const int screenWidth = 800;
const int screenHeight = 600;

//Classes globals
Vector2 GstPos = Vector2{0, 0};
int Gscale = 0;
//Classes static
int Piece::offset = 0;


int main(){

	//	Initialization 
	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);


	//srand(time(NULL));
	// Global Parameters
	Vector2 GridRatio = {10,20};
	int Scale = 20;
	const int MaxPieces = 200;


	//Get the top left pivot of the grid
	Vector2 st = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
    Vector2 nst = {(float)(GridRatio.x*Scale)/2, (float)(GridRatio.y*Scale)/2};
    st.x = st.x - nst.x;
    st.y = st.y - nst.y;

	//Pass the initial parameters to our classes
	GstPos = st;
	Gscale = Scale;

	//Used for centering the spawn point of the pieces
	Piece::offset = ((int)(GridRatio.x / 2) - 1);

	Grid mainGrid(GridRatio, MaxPieces);

	float time, prevtime = GetTime();
	int updTime = 1;

	//	Main game loop
	while (!WindowShouldClose()){

		time = GetTime();
		if(time - prevtime >= updTime){
			prevtime = time;

			//Every updTime the piece falls
			mainGrid.Tick();
		}
		
		mainGrid.CheckforInputs();

		BeginDrawing();
		
		DrawFPS(10, 10);
		ClearBackground(BLACK);

		mainGrid.Draw();

		EndDrawing();
	}


	return 0;
}