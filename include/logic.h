#pragma once


extern int Gscale; 
extern Vector2 GstPos;

//Local and Global depend on the globals Gscale and GstPos
//Given a raylib-real pos, it returns the local coord  / GlobalToLocal
//returns -1 if out of bounds
Vector2 GetLocalPos(Vector2 globalpos);

//Given the local coord, it returns the raylib coord pos / LocalToGlobal
//returns -1 if out of bounds
Vector2 GetGlobalPos(Vector2 localpos);

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
    void Move();
    //void FastMove();
    void Left();
    void Right();
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

    // Moves the piece Down, happens every sec / updTime
    void Move();

    //NOT USED
    // Moves the piece down fast when s/down is pressed
    //void FastMove();

    // Left arrow click
    void Left();

    // Right arrow click
    void Right();
};

class Grid {
    //ratio
    Vector2 rt;

    //rt.x * rt.y
    //0 if there is a block in a x,y place. 1 else
    int** Coords;

    //Keep which cube is in each coord
    //Cube** CoordC;
    const int MaxPieces;

    //Spawned pieces
	Piece **pieces;

    //Active Piece
    Piece *actp;

    //active pieces counter
	int ap;

    // used for the Down input 
    int tmp;

public:
    //Grid();
    Grid(Vector2 ratio, int mx); 
    ~Grid();

    //Spawn a new piece, check for collision, add to score, update coords
    void Tick();
    void Draw();

    //NOT USED YET
    //Adds or removes the given positions of the grid, act == 0 => add / act == 1 => remove
    //bool UpdateGrid(Vector2 pos, int act);

    //Update the Grid with the given piece
    void UpdateGrid(Piece p);

    //Checks if the piece down collides
    bool CheckforCol(Piece p); 
    
    //Handles the left, right and down button presses
    void CheckforInputs();

    //Doesnt allow the piece to move left/right out of the grid 
    bool CheckforBoundsL(Piece p);
    bool CheckforBoundsR(Piece p);

};