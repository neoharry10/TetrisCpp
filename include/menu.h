#pragma once


//The three states of the game that require their unique ui 
enum States {
    Menu, Game, Over
};


extern States GameSt;

void MenuStart();


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
