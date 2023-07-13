#pragma once


extern int Gscale; 
extern Vector2 GstPos;


/*
class Drawable {

    public:
        void Draw();
};
*/

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

    Cube cubes[4];
    //The local grid pos of the cubes
    Vector2 localPos[4];
    pType type;

public:
    //used to center the pieces in the grid
    static int offset;

    Piece();
    Piece(pType);
    ~Piece();

     
    Vector2* GetCubes();
    void Draw();
};

class Grid {
    //ratio
    Vector2 rt;

    //0 if there is a block in a x,y place. 1 else
    int** Coords;

    //Keep which cube is in each coord
    //Cube** CoordC;
    const int MaxPieces;

    //Spawned pieces
	Piece **cubes = new Piece*[MaxPieces];

    //Active Piece
    Piece *actp = nullptr;

    //active pieces counter
	int ap = 0;

public:
    //Grid();
    Grid(Vector2 ratio, int mx); 
    ~Grid();

    //Spawn a new piece, check for collision, add to score, update map
    void Tick();
    //Adds or removes the given positions of the grid, act == 0 => add / act == 1 => remove
    void UpdateGrid(Vector2 pos, int act);
    //Update the Grid with the given piece
    void UpdateGrid(Piece p);
    void Draw();
};