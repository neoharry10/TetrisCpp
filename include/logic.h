#pragma once


extern int Gscale; 
extern Vector2 GstPos;

class Cube {
    Vector2 pos;
    Vector2 size;
    Color cl;

    //temp to keep pos, used to check if we need to redraw it or not
    //int tmpPos = 0; 
public:
    Cube();
    Cube(Vector2 st);
    Cube(Vector2 st, Vector2 sz);
    ~Cube();

    void Draw();
};

//(Piece type) S = square , X is the wiggly type, the others are self explainatory
enum pType {
    L, T, I, S, X
};


class Piece{

        Cube pieces[4];
        pType type;

    public:
        Piece();
        Piece(pType);
        ~Piece();

        void Draw();
};