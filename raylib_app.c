#include "raylib.h"
#include <stdlib.h>

#define MAX_DROPS 300

typedef struct {
    Vector2 position;
    float speed;
    float windSpeed;
} Raindrop;

Color rainColor = (Color){0, 0, 0, 200};
int rainDropSize = 10;
int rainDensity = MAX_DROPS;

void DrawUI()
{
    const int padding = 10;
    const int buttonWidth = 100;
    const int buttonHeight = 30;

    DrawRectangle(padding, padding, 200, 120, (Color){0, 0, 0, 200});

    Vector2 colorButtonPos = {padding + 10, padding + 10};
    DrawRectangleRec((Rectangle){colorButtonPos.x, colorButtonPos.y, buttonWidth, buttonHeight}, rainColor);
    DrawText("Rain Color", colorButtonPos.x + buttonWidth / 2 - MeasureText("Rain Color", 10) / 2, colorButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

    Vector2 sizeButtonPos = {padding + 10, padding + 50};
    DrawRectangle(sizeButtonPos.x, sizeButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Drop Size: %02d", rainDropSize), sizeButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Drop Size: %02d", rainDropSize), 10) / 2, sizeButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

    Vector2 densityButtonPos = {padding + 10, padding + 90};
    DrawRectangle(densityButtonPos.x, densityButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Density: %03d", rainDensity), densityButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Density: %03d", rainDensity), 10) / 2, densityButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);
}

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Relaxing Snow Application");

    Raindrop drops[MAX_DROPS];

    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].position.x = GetRandomValue(0, screenWidth);
        drops[i].position.y = GetRandomValue(-screenHeight, 0);
        drops[i].speed = (float)GetRandomValue(50, 100) / 100.0f;
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

        // user input
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();

            Rectangle colorButton = {10, 10, 100, 30};
            if (CheckCollisionPointRec(mousePos, colorButton))
            {
                // Cycle through colors when the color button is clicked
                rainColor = (Color){ (unsigned char)(rainColor.r + 50 > 255 ? 100 : rainColor.r + 50),
                                      (unsigned char)(rainColor.g + 50 > 255 ? 100 : rainColor.g + 50),
                                      (unsigned char)(rainColor.b + 50 > 255 ? 100 : rainColor.b + 50),
                                      255 };
            }

            Rectangle sizeButton = {10, 50, 100, 30};
            if (CheckCollisionPointRec(mousePos, sizeButton))
            {
                rainDropSize = (rainDropSize + 2) % 20;
            }

            Rectangle densityButton = {10, 90, 100, 30};
            if (CheckCollisionPointRec(mousePos, densityButton))
            {
                rainDensity = (rainDensity + 25) % (MAX_DROPS + 1);
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < rainDensity; i++)
        {
            DrawCircle(drops[i].position.x, drops[i].position.y, rainDropSize / 2, rainColor);
        }

        DrawUI();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}