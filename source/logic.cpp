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
    if(active) DrawRectangleV(pos, size, RED);
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
    //this->~Cube();
}


//Class Piece

Piece::Piece(): Piece((pType)GetRandomValue(0,4)) {}
Piece::Piece(pType p){
    type = p;

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

Cube* Piece::GetCube(int i){
    return &cubes[i];
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

            cubes[i].SetPos(GetGlobalPos(sps[i]));

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
        CheckforPoints();
    }

    if(col){
        actp = nullptr;
    }

}


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
        Ccoords[(int)pos[i].x][(int)pos[i].y] = p.GetCube(i);
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
            }
        }
    }

    if(lines){

        std::cout << "Lines : " << lines << std::endl;
        ChangeScore(lines);
    }
}

void Grid::ChangeScore(int l){



} 

// Cube* Grid::GetCube(Vector2 lc){
//     if(! Coords[(int)lc.x][(int)lc.y])
//         return NULL;

    
// }

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

