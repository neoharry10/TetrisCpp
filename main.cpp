#include <iostream>
#include "raylib.h"

#include "logic.h"
#include "menu.h"


const int screenWidth = 800;
const int screenHeight = 600;


//Classes globals for the active grid
Vector2 GstPos = Vector2{0, 0};
Vector2 Gratio = Vector2{0, 0};
int Gscale = 0;

States GameSt = Menu;

//Classes static
int Piece::offset = 0;


void GameLoop(){

	const int MaxPieces = 200;
	Grid mainGrid(Gratio, MaxPieces);

	float time, prevtime = GetTime();
	int updTime = 1;

	//	Main game loop
	while (!WindowShouldClose() && GameSt == Game){

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

}


void MenuLoop(){
	Button st = Button(GetScreenWidth()/2, GetScreenHeight()/2, 300, 50, "Start");

	while (!WindowShouldClose() && GameSt == Menu){

		if(st.IsClicked()){
			std::cout << "Pressed Start \n";
		}

		BeginDrawing();
		
		DrawFPS(10, 10);
		ClearBackground(BLACK);

		st.Draw();

		EndDrawing();
	}
}

void GameOverLoop(){

}


int main(){

	//	Initialization 
	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);

	//Game Initializatin
	//srand(time(NULL));
	// Global Parameters
	Vector2 GridRatio = {10,20};
	int Scale = 20;
	

	//Get the top left pivot of the grid
	Vector2 st = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
    Vector2 nst = {(float)(GridRatio.x*Scale)/2, (float)(GridRatio.y*Scale)/2};
    st.x = st.x - nst.x;
    st.y = st.y - nst.y;

	//Pass the initial parameters to our classes
	GstPos = st;
	Gscale = Scale;
	Gratio = GridRatio;

	//Used for centering the spawn point of the pieces
	Piece::offset = ((int)(GridRatio.x / 2) - 1);


	MenuLoop();

	MenuStart();
	// while(!WindowShouldClose()){

	// 	switch (GameSt){
	// 		case Menu:
	// 			MenuLoop();
	// 			break;
	// 		case Game:
	// 			GameLoop();
	// 			break;
	// 		case Over:
	//			GameOverLoop();
	// 			break;
			
	// 		default:
	// 			break;
	// 	}
	// }

	return 0;
}