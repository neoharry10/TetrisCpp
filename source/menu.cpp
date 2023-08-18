#include <raylib.h>
#include <iostream>

#include "menu.h"
#include "logic.h"



Button::Button(float x, float y, float width, float height, const char* buttonText)
        : bounds({x, y, width, height}), color(RAYWHITE), text(buttonText) {}


void Button::Draw() {
    if (IsMouseOver()) {
        DrawRectangleRec(bounds, LIGHTGRAY);
    } else {
        DrawRectangleRec(bounds, color);
    }


    // Calculate text width and height
    int textWidth = MeasureText(text, 20);
    // Assumes a fixed height for the font size 20
    int textHeight = 20;  

    DrawText(text, bounds.x + (bounds.width - textWidth) / 2,
     bounds.y + (bounds.height - textHeight) / 2, 20, BLACK);
}

bool Button::IsClicked() {
    return IsMouseOver() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

bool Button::IsMouseOver() {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, bounds);
}