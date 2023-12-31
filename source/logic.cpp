#include <raylib.h>
#include <cmath>
#include "logic.h"

#include <iostream>


//Class Cube

Cube::Cube(){}
Cube::Cube(Vector2 st) : Cube(st, Vector2{(float)Gscale,(float)Gscale}) {}
Cube::Cube(Vector2 st, Vector2 sz) : pos(st), size(sz), cl(RED), active(1) {}

Cube::~Cube() {
}

void Cube::SetPos(Vector2 ps){
    pos = ps;
}

Vector2 Cube::GetPos(){
    return pos;
}

void Cube::Draw(){

    //if(!tmpPos || tmpPos != pos)
    if(active){ 
        DrawRectangleV(pos, size, cl);
    }
}

void Cube::Move(){

    pos.y += Gscale;
}

void Cube::Left(){

    pos.x -= Gscale;
}

void Cube::Right(){

    pos.x += Gscale;
}

void Cube::Destroy(){

    //SetPos(Vector2{800,600});
    active = 0;
    this->~Cube();
}


//Class Piece

Piece::Piece(): Piece((pType)GetRandomValue(0,4)) {}
Piece::Piece(pType p){
    type = p;

    //Spawn points 
    Vector2 sps[4];

    cubes = new Cube[4];
    
    // I make 'local cords' for the cubes, when drawn they will need to be *scale and + global starting point
    switch (type)
    {
    case L:
        sps[0] = {0,0};
        sps[1] = {1,0};
        sps[2] = {2,0};
        sps[3] = {2,1};
        break;
    case T:
        sps[0] = {0,0};
        sps[1] = {1,0};
        sps[2] = {2,0};
        sps[3] = {1,1};
        break;
    case I:
        sps[0] = {0,0};
        sps[1] = {1,0};
        sps[2] = {2,0};
        sps[3] = {3,0};
        break;
    case S:
        sps[0] = {0,0};
        sps[1] = {1,0};
        sps[2] = {0,1};
        sps[3] = {1,1};
        break;
    case X:
        sps[0] = {1,0};
        sps[1] = {2,0};
        sps[2] = {0,1};
        sps[3] = {1,1};
        break;
    default:
        break;
    }
    
    for (int i = 0; i < 4; i++){

        sps[i].x += offset;

        cubes[i] = Cube(GetGlobalPos(sps[i])); 
    }
    
}

Piece::~Piece(){

}

void Piece::Draw(){

    for (int i = 0; i < 4; i++){
        if(&cubes[i]){
            cubes[i].Draw();
        }
    }
}

Vector2* Piece::GetCubes(){
    
    Vector2* localPos = new Vector2[4];

    for(int i = 0; i < 4; i++){
        if(&cubes[i]){
            localPos[i] = GetLocalPos(cubes[i].GetPos());
        }
        else{
            localPos[i] = Vector2{-1,-1};
        }
    }


    return localPos;
}

void Piece::Move(){

    for(int i = 0; i < 4; i++){
        cubes[i].Move();
    }
}

void Piece::Left(){

    for(int i = 0; i < 4; i++){
        cubes[i].Left();
    }
}

void Piece::Right(){

    for(int i = 0; i < 4; i++){
        cubes[i].Right();
    }
}

Cube* Piece::GetCube(int i){
    return cubes+i;
}

void Piece::Rotate(){
    

    switch (type){
    case L: 
    case T:
    case I:
    case X:
    {
        Vector2 *sps = GetCubes();

        //Get one of the cubes as anchor to rotate around
        Vector2 anchor = GetLocalPos(cubes[1].GetPos());

        float angleRad = 90 * PI/180.0f, x, y;

        //Used to check if any point is outside the grid to not apply that rotation
        bool inBounds = true;

        for (int i = 0; i < 4; i++) {

            sps[i].x -= anchor.x;
            sps[i].y -= anchor.y; 

            x = sps[i].x;
            y = sps[i].y;

            sps[i].x = x * cos(angleRad) - y * sin(angleRad);
            sps[i].y = x * sin(angleRad) + y * cos(angleRad);

            sps[i].x += anchor.x;
            sps[i].y += anchor.y;

            sps[i].x = round(sps[i].x);
            sps[i].y = round(sps[i].y);

            if(!(sps[i].x >= 0 && sps[i].x < Gratio.x)
            // Check the sps[i].y for other cubes 
            ){
                inBounds = false;
            }
        }

        if(inBounds){
            for(int i = 0; i < 4; i++){
                cubes[i].SetPos(GetGlobalPos(sps[i]));
            }
        }
        delete[] sps;
    }
        break;
    case S:
    default:
        break;
    }

}


//Class Grid

Grid::Grid(Vector2 ratio, int mx): rt(ratio), MaxPieces(mx){

    pieces = new Piece*[MaxPieces];
    actp = nullptr;
    ap = 0;
    tmp = 0;
    score = 0;
    isGO = false;

    Coords = new int*[(int)ratio.x];
    for (int i = 0; i < ratio.x; i++){
        Coords[i] = new int[(int)ratio.y];
    }

    for (int x = 0; x < ratio.x; x++){
        for(int y = 0; y < ratio.y; y++){
            Coords[x][y] = 0;
        }
    }


    Ccoords = new Cube**[(int)ratio.x];
    for (int i = 0; i < ratio.x; i++){
        Ccoords[i] = new Cube*[(int)ratio.y];
    }

    for (int x = 0; x < ratio.x; x++){
        for(int y = 0; y < ratio.y; y++){
            Ccoords[x][y] = NULL;
        }
    }

    xPos = GstPos.x + (rt.x/2 - 2) * Gscale;
    yPos = GstPos.y - 2*Gscale;
}


Grid::~Grid(){

    for (int i = 0; i < ap; i++){
        delete[] pieces[i];
    }
    delete[] pieces;


    for (int i = 0; i < rt.x; ++i) {
        delete[] Coords[i];
        delete[] Ccoords[i];
    }
    delete[] Coords;
    delete[] Ccoords;
}

void Grid::Draw(){

    for(int i = 0; i < ap; i++){
        pieces[i]->Draw();
    }

    int dist = Gscale;
    for (int i = 0; i <= rt.y; i++){
        DrawLine(GstPos.x, GstPos.y + i*dist, GstPos.x + rt.x*Gscale, GstPos.y + i*dist, BLUE); 
    }

    for (int i = 0; i <= rt.x; i++){
        DrawLine(GstPos.x + i*dist, GstPos.y, GstPos.x + i*dist, GstPos.y + rt.y*Gscale, BLUE);
    }


    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    DrawText(scoreText, xPos, yPos, 20, WHITE);
}

void Grid::Tick(){

    //We spawn a new piece
    if (col){
        pieces[ap] = new Piece();
        actp = pieces[ap];
        ap += 1;
    }
    else {
        actp->Move();
    }
    col = CheckforCol(*actp);
    CheckforPoints();

}


bool Grid::CheckforCol(Piece p){

    Vector2* pos = p.GetCubes();
    

    int floorCord = rt.y;
    for(int i = 0; i < 4; i++){

        //Hit Ceiling
        if((pos[i].y == 0 || pos[i].y == 1) && Coords[(int)pos[i].x][(int)pos[i].y + 1]){
            delete[] pos;
            isGO = true;
            return true; //Will never be called 
        }

        //Hit other pieces 
        if( Coords[(int)pos[i].x][(int)pos[i].y + 1] ||
        //Hit floor 
        pos[i].y + 1 >= floorCord ){

            UpdateGrid(p);
            delete[] pos;
            return true;
        }
    }

    delete[] pos;
    return false;
}

void Grid::UpdateGrid(Piece p){
    Vector2* pos = p.GetCubes();

    for(int i = 0; i < 4; i++){
        if(pos[i].x >= 0){ //Check that there is an active cube
            Coords[(int)pos[i].x][(int)pos[i].y] = 1;
            Ccoords[(int)pos[i].x][(int)pos[i].y] = p.GetCube(i);
        }
    }

    delete[] pos;
}

void Grid::CheckforInputs(){
    
    //tmp = 0;
    
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
       //actp->FastMove();
        tmp = ap;
    }

    if(tmp == ap){
        Tick();
    }
    else {
        tmp = 0;

        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
            if(CheckforBoundsL(*actp))
                actp->Left();

        }
        else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
            if(CheckforBoundsR(*actp))
                actp->Right();
        }

        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
            //MAY NEED TO CHECK FOR COLLISIONS HERE

            actp->Rotate();
        }
    }
}

bool Grid::CheckforBoundsL(Piece p){
    Vector2* pos = p.GetCubes();

    for(int i = 0; i < 4; i++){
        if ( pos[i].x -1 < 0 ){
            delete[] pos;
            return false;
        }
    }

    delete[] pos;
    return true;
}

bool Grid::CheckforBoundsR(Piece p){
    Vector2* pos = p.GetCubes();

    for(int i = 0; i < 4; i++){
        if ( pos[i].x  +1 >= rt.x ){
            delete[] pos;
            return false;
        }
    }

    delete[] pos;
    return true;
}

void Grid::CheckforPoints(){

    int lines = 0;
    bool isFull;
    for(int y = rt.y -1 ; y >= 0; y--){
        isFull = true;
        for(int x = 0; x < rt.x; x++){

            if(!Coords[x][y])
                isFull = false;
        }

        if(isFull){
            
            lines++;
            for(int x = 0; x < rt.x; x++){
                Coords[x][y] = 0;
                Ccoords[x][y]->Destroy();
                Ccoords[x][y] = NULL;
            }

            Gravity(y);
        }
    }

    if(lines){

        ChangeScore(lines);
    }
}

void Grid::ChangeScore(int l){


    score += l*10;

} 

int Grid::GetScore(){
    return score;
}

void Grid::Gravity(int l){

    Cube* tmp;
    

    for(int j = l; j >= 0; j--){
        for(int i = 0; i < rt.x; i++){

            if(Coords[i][j]){

                Ccoords[i][j]->Move();

                tmp = Ccoords[i][j];

                Ccoords[i][j] = NULL;
                Coords[i][j] = 0;
            
                Ccoords[i][j+1] = tmp;
                Coords[i][j+1] = 1;
            }
        }
    }

}

bool Grid::isGameOver(){
    return isGO;
}

Vector2 GetLocalPos(Vector2 pos){

    pos.x -= GstPos.x;
    pos.y -= GstPos.y;
    pos.x /= Gscale;
    pos.y /= Gscale;

    return pos;
}

Vector2 GetGlobalPos(Vector2 pos){

    pos.x *= Gscale;
    pos.y *= Gscale;
    pos.x += GstPos.x;
    pos.y += GstPos.y;

    return pos;

}

