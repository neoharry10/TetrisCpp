#include <raylib.h>
#include "logic.h"




Cube::Cube(){}
Cube::Cube(Vector2 st) : Cube(st, Vector2{(float)Gscale,(float)Gscale}) {}
Cube::Cube(Vector2 st, Vector2 sz) : pos(st), size(sz), cl(RED) {}

Cube::~Cube() {
}

void Cube::Draw(){

    //if(!tmpPos || tmpPos != pos)
    DrawRectangleV(pos, size, RED);
}
Piece::Piece(){}
Piece::Piece(pType p){
    type = p;//(pType)GetRandomValue(0,4);

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
        sps[i].x *= Gscale;
        sps[i].y *= Gscale;

        sps[i].x += GstPos.x;
        sps[i].y += GstPos.y;


        pieces[i] = Cube(sps[i]); 
    }
    
    GstPos.x += 5*Gscale; //TEsting
 
}

Piece::~Piece(){

}

void Piece::Draw(){

    for (int i = 0; i < 4; i++){
        pieces[i].Draw();
    }
}
