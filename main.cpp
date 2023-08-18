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


void MenuLoop(){

	int buttonWidth = 300, buttonHeight = 50;

	float buttonX = (GetScreenWidth() - buttonWidth) / 2;
	float buttonY = (GetScreenHeight() - buttonHeight) / 2;
	Button st = Button(buttonX, buttonY, buttonWidth, buttonHeight, "Start");

	while (!WindowShouldClose()){

		if(st.IsClicked()){
			GameSt = Game;
			break;
		}

		BeginDrawing();
		
		DrawFPS(10, 10);
		ClearBackground(BLACK);

		st.Draw();
		DrawText("Close the game using 'ESC'", buttonX, buttonY - 50, 20, WHITE);

		EndDrawing();

	}
}

int GameLoop(){

	const int MaxPieces = 200;
	Grid mainGrid(Gratio, MaxPieces);

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
		
		if(mainGrid.isGameOver()){
			GameSt = Over;
			break;
		}

	}

	return mainGrid.GetScore();
}


void GameOverLoop(int Score){
 	
	int buttonWidth = 300, buttonHeight = 50;
	float buttonX = (GetScreenWidth() - buttonWidth) / 2;
	float buttonY = (GetScreenHeight() - buttonHeight) / 2;
    
    char scoreText[100];
    snprintf(scoreText, sizeof(scoreText), "Final Score: %d", Score);

	Button st = Button(buttonX, buttonY, buttonWidth, buttonHeight, "Play Again");

	while (!WindowShouldClose()){

		if(st.IsClicked()){
			GameSt = Game;
			break;
		}

		BeginDrawing();
		
		DrawFPS(10, 10);
		ClearBackground(BLACK);

		st.Draw();
    	DrawText(scoreText, buttonX, buttonY - 50, 20, WHITE);

		EndDrawing();

	}
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

	int score;

	while(!WindowShouldClose()){


		if(GameSt == Game){
			score = GameLoop();
		}
		else if(GameSt == Over){
			GameOverLoop(score);
		}
	}

	return 0;
}