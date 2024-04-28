#include "raylib.h"
#include <stdlib.h>

#define MAX_DROPS 200

typedef struct {
    Vector2 position;
    float speed;
    float windSpeed;
    Color color;
} Raindrop;

Color rainColor = BLUE;
int rainDropSize = 10;
int rainDensity = MAX_DROPS;

void DrawUI()
{
    const int padding = 10;
    const int buttonWidth = 100;
    const int buttonHeight = 30;

    // Draw UI background
    DrawRectangle(padding, padding, 200, 120, (Color){0, 0, 0, 200});

    // Draw rain color button
    Vector2 colorButtonPos = {padding + 10, padding + 10};
    DrawRectangleRec((Rectangle){colorButtonPos.x, colorButtonPos.y, buttonWidth, buttonHeight}, rainColor);
    DrawText("Rain Color", colorButtonPos.x + buttonWidth / 2 - MeasureText("Rain Color", 10) / 2, colorButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

    // Draw rain drop size button
    Vector2 sizeButtonPos = {padding + 10, padding + 50};
    DrawRectangle(sizeButtonPos.x, sizeButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Drop Size: %02d", rainDropSize), sizeButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Drop Size: %02d", rainDropSize), 10) / 2, sizeButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

    // Draw rain density button
    Vector2 densityButtonPos = {padding + 10, padding + 90};
    DrawRectangle(densityButtonPos.x, densityButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Density: %03d", rainDensity), densityButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Density: %03d", rainDensity), 10) / 2, densityButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);
}

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Relaxing Rain Application");

    Raindrop drops[MAX_DROPS];

    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].position.x = GetRandomValue(0, screenWidth);
        drops[i].position.y = GetRandomValue(-screenHeight, 0);
        drops[i].speed = (float)GetRandomValue(50, 100) / 100.0f;
        drops[i].color = (Color){ GetRandomValue(100, 200), GetRandomValue(100, 200), GetRandomValue(200, 255), 255 };
        drops[i].windSpeed = (float)GetRandomValue(-50, 50) / 100.0f;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        for (int i = 0; i < MAX_DROPS; i++) {
            drops[i].position.y += drops[i].speed;
            drops[i].position.x += drops[i].windSpeed;

            // If a raindrop reaches the bottom, reset its position to the top
            if (drops[i].position.y > screenHeight) {
                drops[i].position.y = GetRandomValue(-screenHeight, 0);
                drops[i].position.x = GetRandomValue(0, screenWidth);
            }
        }

        // Handle user input
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();

            // Check if rain color button is clicked
            Rectangle colorButton = {10, 10, 100, 30};
            if (CheckCollisionPointRec(mousePos, colorButton))
            {
                rainColor = (Color){ GetRandomValue(100, 250), GetRandomValue(100, 250), GetRandomValue(100, 250), 255 }; // Change rain color to a random value
            }

            // Check if rain drop size button is clicked
            Rectangle sizeButton = {10, 50, 100, 30};
            if (CheckCollisionPointRec(mousePos, sizeButton))
            {
                rainDropSize = (rainDropSize + 2) % 20; // Cycle through rain drop sizes from 2 to 20
            }

            // Check if rain density button is clicked
            Rectangle densityButton = {10, 90, 100, 30};
            if (CheckCollisionPointRec(mousePos, densityButton))
            {
                rainDensity = (rainDensity + 25) % (MAX_DROPS + 1); // Cycle through rain densities from 25 to MAX_DROPS
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < rainDensity; i++)
        {
            Rectangle dropRect = {drops[i].position.x, drops[i].position.y, rainDropSize, rainDropSize};
            DrawRectangleRec(dropRect, drops[i].color);
        }

        DrawUI();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}