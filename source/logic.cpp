#include <raylib.h>
#include "logic.h"

#include <iostream>


//Class Cube

Cube::Cube(){}
Cube::Cube(Vector2 st) : Cube(st, Vector2{(float)Gscale,(float)Gscale}) {}
Cube::Cube(Vector2 st, Vector2 sz) : pos(st), size(sz), cl(RED) {}

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
    DrawRectangleV(pos, size, RED);
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


//Class Piece

Piece::Piece(): Piece((pType)GetRandomValue(0,4)) {}
Piece::Piece(pType p){
    type = p;
    rotSt = 0;
    //Spawn points 
    Vector2 sps[4];
    
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
        cubes[i].Draw();
    }
}

Vector2* Piece::GetCubes(){
    
    Vector2* localPos = new Vector2[4];

    for(int i = 0; i < 4; i++){
        localPos[i] = GetLocalPos(cubes[i].GetPos());
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

void Piece::Rotate(){
    

    Vector2 newpos[4];
    Vector2 anchor = GetLocalPos(cubes[1].GetPos());

    newpos[0] = Vector2{anchor.x+1,anchor.y+1};
    newpos[1] = Vector2{anchor.x,anchor.y};
    newpos[2] = Vector2{anchor.x-1,anchor.y - 1};
    newpos[3] = Vector2{anchor.x,anchor.y - 2};
    

    for (int i = 0; i < 4; i++){
        cubes[i].SetPos(GetGlobalPos(newpos[i]));
    }
    /*switch (type){
    case L:
        
    case T:


        switch (rotSt)
        {
        case 0:


            rotSt = 1;
            break;
        case 1:
        case 2:
        case 3:
            rotSt = 0;
        
        default:
            break;
        }


        break;
    case I:
    case X:
        

        break;
    case S:
        break;
    default:
        break;
    }
    */
}


//Class Grid

Grid::Grid(Vector2 ratio, int mx): rt(ratio), MaxPieces(mx){

    pieces = new Piece*[MaxPieces];
    actp = nullptr;
    ap = 0;
    tmp = 0;

    Coords = new int*[(int)ratio.x];
    for (int i = 0; i < ratio.x; i++){
        Coords[i] = new int[(int)ratio.y];
    }

    for (int x = 0; x < ratio.x; x++){
        for(int y = 0; y < ratio.y; y++){
            Coords[x][y] = 0;
        }
    }
}

Grid::~Grid(){

    for (int i = 0; i < ap; i++){
        delete[] pieces[i];
    }
    delete[] pieces;


    for (int i = 0; i < rt.x; ++i) {
        delete[] Coords[i];
    }
    delete[] Coords;
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
}

void Grid::Tick(){

    bool col = false;

    //We spawn a new piece
    if (actp == nullptr){
        pieces[ap] = new Piece();
        actp = pieces[ap];
        ap += 1;

        col = CheckforCol(*actp);
    }
    else {
        actp->Move();

        col = CheckforCol(*actp);
    }

    if(col){
        actp = nullptr;
    }
}

// bool Grid::UpdateGrid(Vector2 pos, int act){

//     //int sz = sizeof(pos) / sizeof(pos[0]);

//     return false;
// }

bool Grid::CheckforCol(Piece p){

    Vector2* pos = p.GetCubes();
    

    int floorCord = rt.y;
    for(int i = 0; i < 4; i++){
        //Hit other pieces check
        if( Coords[(int)pos[i].x][(int)pos[i].y + 1] ||
        //Floor check
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
        Coords[(int)pos[i].x][(int)pos[i].y] = 1;
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


Vector2 GetLocalPos(Vector2 pos){

    pos.x -= GstPos.x;
    pos.y -= GstPos.y;
    pos.x /= Gscale;
    pos.y /= Gscale;

    return pos;
}

Vector2 GetGlobalPos(Vector2 pos){
    //sps[i].x *= Gscale;
        //sps[i].y *= Gscale;

        //sps[i].x += GstPos.x + offset;
        //sps[i].y += GstPos.y;

    pos.x *= Gscale;
    pos.y *= Gscale;
    pos.x += GstPos.x;
    pos.y += GstPos.y;

    return pos;

}

