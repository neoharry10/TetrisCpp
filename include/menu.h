#pragma once


//The three states of the game that require their unique ui 
enum States {
    Menu, Game, Over
};


extern States GameSt;

class Button {
private:
    Rectangle bounds;
    Color color;
    const char* text;

public:
    Button(float x, float y, float width, float height, const char* buttonText);

    void Draw();
    bool IsClicked();
    bool IsMouseOver();
};

/*
class Menu{

    Button* buttons;
    int bCC;    
public:

    Menu(*buttons);

    void Draw(){
        for(int i = 0; i < bCC; i++){
            buttons[i].Draw();
        }
    }

}
*/