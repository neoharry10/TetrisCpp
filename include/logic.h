#pragma once


extern int Gscale; 
extern Vector2 GstPos;
extern Vector2 Gratio;

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
    int active;
    Cube();
    Cube(Vector2 st);
    Cube(Vector2 st, Vector2 sz);
    ~Cube();

    //Set global cube position
    void SetPos(Vector2 pos);

    //Returns the global pos of the cube
    Vector2 GetPos();

    void Draw();
    void Move();
    void Left();
    void Right();

    void Destroy();

};

//(Piece type) S = square , X is the wiggly type, the others are self explainatory
enum pType {
    L, T, I, S, X
};


class Piece{

    //Each of the cubes that this piece has
    Cube* cubes;

    pType type;
public:
    //used to center the pieces in the grid
    static int offset;

    Piece();
    Piece(pType);
    ~Piece();

    //Returns the local position of the pieces' cubes, {-1,-1} if the i-th cube doesnt exist
    Vector2* GetCubes();

    //Returns a pointer to the i-th cube
    Cube* GetCube(int);
    
    void Draw();
    // Moves the piece Down, happens every sec / updTime
    void Move();
    // Up arrow click
    void Rotate();
    // Left arrow click
    void Left();
    // Right arrow click
    void Right();
};

class Grid {
    //ratio
    Vector2 rt;

    //rt.x * rt.y
    //1 if there is a block in a x,y place. 0 else
    int** Coords;

    // 2d array of cube pointers, we keep the stopped cubes here
    Cube*** Ccoords;

    const int MaxPieces;

    //Spawned pieces
	Piece **pieces;

    //Active Piece
    Piece *actp;

    //active pieces counter
	int ap;

    //the game score
    int score, xPos, yPos;

    char scoreText[100];

    // used for the Down input 
    int tmp;

    // used for the spawning of the pieces
    bool col;

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

    //Checks if the piece collides while falling
    bool CheckforCol(Piece p); 
    
    //Handles the left, right and down button presses
    void CheckforInputs();

    //Doesnt allow the piece to move left/right out of the grid 
    bool CheckforBoundsL(Piece p);
    bool CheckforBoundsR(Piece p);

    // //Returns a pointer to the cube in the given location(localcoords)
    // //null if it doesnt exist  
    // Cube* GetCube(Vector2 localCoord);

    //Checks and deletes lines from the grid
    void CheckforPoints();

    //Adds to score depending on the lines that are filled (1 for 1 line, 2 for 2 , ...)
    void ChangeScore(int);

    //Given the y of the line deleted, it moves the above cubes down
    void Gravity(int);
};