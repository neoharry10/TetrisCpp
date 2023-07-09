#include <raylib.h>
#include "logic.h"




cube::cube(){}
cube::cube(Vector2 st, Vector2 sz) : pos(st) {

    DrawRectangleV(st, sz, RED);
}

cube::~cube() {
}

piece::piece(){
    type = (pType)GetRandomValue(0,4);
 
}

piece::~piece(){

}