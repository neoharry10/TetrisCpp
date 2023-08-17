#include <raylib.h>

#include "menu.h"
#include "logic.h"


void MenuStart(){

    Button(GetScreenWidth()/2, GetScreenHeight()/2, 30, 25, "Start");

}

Button::Button(float x, float y, float width, float height, const char* buttonText)
        : bounds({x, y, width, height}), color(RAYWHITE), text(buttonText) {}


void Button::Draw() {
    if (IsMouseOver()) {
        DrawRectangleRec(bounds, GRAY);
    } else {
        DrawRectangleRec(bounds, color);
    }
    DrawText(text, bounds.x + 20, bounds.y + 10, 20, BLACK);
}

bool Button::IsClicked() {
    return IsMouseOver() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

bool Button::IsMouseOver() {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, bounds);
}