#include <sys/stat.h>
#include <limits.h>
#include <string.h>

#define NOB_IMPLEMENTATION
#include "nob.h"
#include "raylib.h"
#include <stdlib.h>

#define MAX_DROPS 300
#define MAX_SIZE 10

typedef struct {
    Vector2 position;
    float speed;
    float windSpeed;
    float gravity;
} Snowdrop;


Color snowColor = (Color){255, 255, 255, 200};
int snowDropSize = MAX_SIZE;
int snowDensity = MAX_DROPS;

void DrawUI()
{
    const int padding = 10;
    const int buttonWidth = 100;
    const int buttonHeight = 30;

    DrawRectangle(padding, padding, 200, 150, (Color){0, 0, 0, 200});

    Vector2 colorButtonPos = {padding + 10, padding + 10};
    DrawRectangleRec((Rectangle){colorButtonPos.x, colorButtonPos.y, buttonWidth, buttonHeight}, snowColor);
    DrawText("Snow Color", colorButtonPos.x + buttonWidth / 2 - MeasureText("Snow Color", 10) / 2, colorButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

    Vector2 sizeButtonPos = {padding + 10, padding + 50};
    DrawRectangle(sizeButtonPos.x, sizeButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Drop Size: %02d", snowDropSize), sizeButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Drop Size: %02d", snowDropSize), 10) / 2, sizeButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

    Vector2 densityButtonPos = {padding + 10, padding + 90};
    DrawRectangle(densityButtonPos.x, densityButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Density: %03d", snowDensity), densityButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Density: %03d", snowDensity), 10) / 2, densityButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

    Vector2 windSpeedButtonPos = {padding + 10, padding + 130};
    DrawRectangle(windSpeedButtonPos.x, windSpeedButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText("Wind Speed", windSpeedButtonPos.x + buttonWidth / 2 - MeasureText("Wind Speed", 10) / 2, windSpeedButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);
}


void DrawSnowflake(Vector2 position, float size, Color color)
{
    DrawPoly(position, 6, size, GetRandomValue(0, 360), color);
}

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, "gcc",
                         "-Wall", "-Wextra",
                         "-std=c99",
                         "-o", "snowfall",
                         "raylib_app.c",
                         "-lraylib",
                         "-lm", "-lpthread", "-ldl", "-lGL", "-lX11");

    if (!nob_cmd_run_sync(cmd)) return 1;

    const int screenWidth = 1920;
    const int screenHeight = 1080;


    InitWindow(screenWidth, screenHeight, "Relaxing Snow Application");
    ToggleFullscreen();

    Snowdrop drops[MAX_DROPS];

    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].position.x = GetRandomValue(0, screenWidth);
        drops[i].position.y = GetRandomValue(-screenHeight, 0);
        drops[i].speed = (float)GetRandomValue(50, 100) / 100.0f;
        drops[i].windSpeed = (float)GetRandomValue(-50, 50) / 100.0f;
        drops[i].gravity = (float)GetRandomValue(90, 110) / 100.0f;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        for (int i = 0; i < MAX_DROPS; i++) {
            drops[i].position.y += drops[i].speed * drops[i].gravity;
            drops[i].position.x += drops[i].windSpeed;

            // If a snowdrop reaches the bottom, reset its position to the top
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
                // Cycle through shades of gray when the color button is clicked
                snowColor.r = (snowColor.r + 50 > 255) ? 100 : snowColor.r + 50;
                snowColor.g = snowColor.r;
                snowColor.b = snowColor.r;
            }

            Rectangle sizeButton = {10, 50, 100, 30};
            if (CheckCollisionPointRec(mousePos, sizeButton))
            {
                snowDropSize = (snowDropSize + 2) % 20;
            }

            Rectangle densityButton = {10, 90, 100, 30};
            if (CheckCollisionPointRec(mousePos, densityButton))
            {
                snowDensity = (snowDensity + 25) % (MAX_DROPS + 1);
            }

            Rectangle windSpeedButton = {10, 130, 100, 30};
            if (CheckCollisionPointRec(mousePos, windSpeedButton))
            {
                for (int i = 0; i < MAX_DROPS; i++)
                {
                    drops[i].windSpeed = (float)GetRandomValue(-100, 100) / 100.0f;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < snowDensity; i++)
        {
            DrawSnowflake(drops[i].position, snowDropSize, snowColor);
        }

        DrawUI();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
