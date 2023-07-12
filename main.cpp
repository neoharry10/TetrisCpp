#include <iostream>
#include "raylib.h"

#include "logic.h"
#include "graphics.h"


const int screenWidth = 800;
const int screenHeight = 600;

Vector2 GstPos = Vector2{0, 0};
int Gscale = 0;

int main(){

	//	Initialization 

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);

	//srand(time(NULL));
	// Global Parameters
	Vector2 GridRatio = {10,20};
	int Scale = 20;

	Piece *pc;

	//Get the top left pivot of the grid
	Vector2 st = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
    Vector2 nst = {(float)(GridRatio.x*Scale)/2, (float)(GridRatio.y*Scale)/2};
    st.x = st.x - nst.x;
    st.y = st.y - nst.y;

	//Pass the initial parameters to our classes
	GstPos = st;
	Gscale = Scale;



	pc = new Piece[5];

	pc[0] = Piece(L);
	pc[1] = Piece(T);
	pc[2] = Piece(I);
	pc[3] = Piece(S);
	pc[4] = Piece(X);

	//	Main game loop
	while (!WindowShouldClose()){

		
		BeginDrawing();

		
		DrawFPS(10, 10);
		ClearBackground(BLACK);


		for(int i = 0; i < 5; i++){
			(pc+i)->Draw();

		}

		MakeGrid(GridRatio, Scale);

		EndDrawing();

	}
	delete(pc);

	return 0;
}