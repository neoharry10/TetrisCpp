#include <raylib.h>
#include "logic.h"

class cube;

//(piece type) S = square , X is the wiggly type, the others are self explainatory
enum pType {
    L, T, I, S, X
};

class piece{
    private:
        cube pieces[4];
        pType type;
    public:
        piece();
        ~piece();
};
piece::piece(){
    type = (pType)GetRandomValue(0,4);
}

class cube {
private:
    Vector2 pos;
public:
    cube ();
    ~cube();
};

cube::cube(/* args */) {
}

cube::~cube() {
}
