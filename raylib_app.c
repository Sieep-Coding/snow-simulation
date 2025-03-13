#include "raylib.h"
#include <stdlib.h>

#define MAX_DROPS 300
#define MAX_SIZE 10

typedef struct {
    Vector2 position;
    float speed;
    float windSpeed;
    float gravity;
    int type;
} Snowdrop;

Color snowColor = (Color){255, 255, 255, 200};
int snowDropSize = MAX_SIZE;
int snowDensity = MAX_DROPS;
bool soundPlaying = false;

void DrawUI()
{
    const int padding = 10;
    const int buttonWidth = 100;
    const int buttonHeight = 30;

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

    Vector2 playMusicPos = {padding + 10, padding + 170};
    DrawRectangle(playMusicPos.x, playMusicPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText("Toggle Music", playMusicPos.x + buttonWidth / 2 - MeasureText("Toggle Music", 10) / 2, playMusicPos.y + buttonHeight / 2 - 5, 11, WHITE);
}

void DrawSnowflake(Vector2 position, float size, Color color)
{
    DrawPoly(position, 6, size, GetRandomValue(0, 360), color);
}


int main(void)
{
    const int screenWidth = 854;
    const int screenHeight = 480;
    
    InitWindow(screenWidth, screenHeight, "Relaxing Snow Application");
    
    InitAudioDevice();
    Sound sound = LoadSound("mp3/christmas.mp3");
    //ToggleFullscreen();
    
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

            Rectangle colorButton = {10, 10, 75, 30};
            if (CheckCollisionPointRec(mousePos, colorButton))
            {
                snowColor.r = (snowColor.r + 50 > 255) ? 100 : snowColor.r + 50;
                snowColor.g = snowColor.r;
                snowColor.b = snowColor.r;
            }

            Rectangle sizeButton = {10, 50, 75, 30};
            if (CheckCollisionPointRec(mousePos, sizeButton))
            {
                snowDropSize = (snowDropSize + 2) % 20;
            }
            
            Rectangle densityButton = {10, 90, 75, 30};
            if (CheckCollisionPointRec(mousePos, densityButton))
            {
                snowDensity = (snowDensity + 25) % (MAX_DROPS + 1);
            }

            Rectangle windSpeedButton = {10, 130, 75, 30};
            if (CheckCollisionPointRec(mousePos, windSpeedButton))
            {
                for (int i = 0; i < MAX_DROPS; i++)
                {
                    drops[i].windSpeed = (float)GetRandomValue(-100, 100) / 100.0f;
                }
            }
            
            Rectangle playMusicButton = {10, 170, 75, 30};
            if (CheckCollisionPointRec(mousePos, playMusicButton))
            {
                if (soundPlaying) 
                {
                    soundPlaying = false;
                    StopSound(sound);
                } 
                else
                {
                    soundPlaying = true;
                    PlaySound(sound);
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

    UnloadSound(sound);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
