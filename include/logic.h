

class cube {
    Vector2 pos;
public:
    cube();
    cube(Vector2 st, Vector2 sz);
    ~cube();
};

//(piece type) S = square , X is the wiggly type, the others are self explainatory
enum pType {
    L, T, I, S, X
};


class piece{
        cube pieces[4];
        pType type;
    public:
        piece();
        ~piece();
};