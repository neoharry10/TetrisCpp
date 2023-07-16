#include <raylib.h>
#include "logic.h"

#include <iostream>


//Class Cube

Cube::Cube(){}
Cube::Cube(Vector2 st) : Cube(st, Vector2{(float)Gscale,(float)Gscale}) {}
Cube::Cube(Vector2 st, Vector2 sz) : pos(st), size(sz), cl(RED) {}

Cube::~Cube() {
}

void Cube::Draw(){

    //if(!tmpPos || tmpPos != pos)
    DrawRectangleV(pos, size, RED);
}

void Cube::Move(){

    pos.y += Gscale;
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

    for(int i = 0; i < 4; i++){
        localPos[i] = sps[i];
        localPos[i].x += offset;
    }
    
    for (int i = 0; i < 4; i++){
        sps[i].x *= Gscale;
        sps[i].y *= Gscale;

        sps[i].x += GstPos.x + offset;
        sps[i].y += GstPos.y;


        cubes[i] = Cube(sps[i]); 
    }
    
    //offset += 5*Gscale;
}

Piece::~Piece(){

}

void Piece::Draw(){

    for (int i = 0; i < 4; i++){
        cubes[i].Draw();
    }
}

Vector2* Piece::GetCubes(){

    return localPos;
}

void Piece::Move(){

    for(int i = 0; i < 4; i++){
        cubes[i].Move();
    }
}

//Class Grid

Grid::Grid(Vector2 ratio, int mx): rt(ratio), MaxPieces(mx){

    pieces = new Piece*[MaxPieces];
    actp = nullptr;
    ap = 0;

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

        col = UpdateGrid(*actp);
    }
    else {
        //actp->Move();

        col = UpdateGrid(*actp);
        
    }

    if(col){
        actp = nullptr;
    }
}

bool Grid::UpdateGrid(Vector2 pos, int act){

    //int sz = sizeof(pos) / sizeof(pos[0]);

    return false;
}

bool Grid::UpdateGrid(Piece p){

    Vector2* pos = p.GetCubes();

    std::cout << "TEST:" << pos[0].y << "\n";
    return false;
}