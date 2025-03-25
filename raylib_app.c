#include "raylib_app.h"
#include <stdlib.h>

void DrawUI()
{
    const int padding = 10;
    const int buttonWidth = 100;
    const int buttonHeight = 30;

    Vector2 colorButtonPos = {padding + 10, padding + 10};
    DrawRectangleRec((Rectangle){colorButtonPos.x, colorButtonPos.y, buttonWidth, buttonHeight}, snowColor);
    DrawText("Snow Color", colorButtonPos.x + buttonWidth / 2 - MeasureText("Snow Color", 10) / 2, colorButtonPos.y + buttonHeight / 2 - 5, 10, BLACK);

    Vector2 sizeButtonPos = {padding + 10, padding + 50};
    DrawRectangle(sizeButtonPos.x, sizeButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Drop Size: %02d", snowDropSize), sizeButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Drop Size: %02d", snowDropSize), 10) / 2, sizeButtonPos.y + buttonHeight / 2 - 5, 10, BLACK);

    Vector2 densityButtonPos = {padding + 10, padding + 90};
    DrawRectangle(densityButtonPos.x, densityButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText(TextFormat("Density: %03d", snowDensity), densityButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Density: %03d", snowDensity), 10) / 2, densityButtonPos.y + buttonHeight / 2 - 5, 10, BLACK);

    Vector2 windSpeedButtonPos = {padding + 10, padding + 130};
    DrawRectangle(windSpeedButtonPos.x, windSpeedButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText("Wind Speed", windSpeedButtonPos.x + buttonWidth / 2 - MeasureText("Wind Speed", 10) / 2, windSpeedButtonPos.y + buttonHeight / 2 - 5, 10, BLACK);

    Vector2 playMusicPos = {padding + 10, padding + 170};
    DrawRectangle(playMusicPos.x, playMusicPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText("Toggle Music", playMusicPos.x + buttonWidth / 2 - MeasureText("Toggle Music", 10) / 2, playMusicPos.y + buttonHeight / 2 - 5, 10, BLACK);

    Vector2 uniqueColorsPos = {padding + 10, padding + 210};
    DrawRectangle(uniqueColorsPos.x, uniqueColorsPos.y, buttonWidth, buttonHeight, snowColor);
    DrawText("Fun Colors", uniqueColorsPos.x + buttonWidth / 2 - MeasureText("Fun Colors", 10) / 2, uniqueColorsPos.y + buttonHeight / 2 - 5, 10, BLACK);

    Vector2 blizzardModePos = {padding + 10, padding + 250};
    DrawRectangle(blizzardModePos.x, blizzardModePos.y, buttonWidth, buttonHeight, GRAY);
    DrawText("Blizzard!", blizzardModePos.x + buttonWidth / 2 - MeasureText("Blizzard!", 10) / 2, blizzardModePos.y + buttonHeight / 2 - 5, 10, BLACK);

    Vector2 backgroundColorsPos = {padding + 10, padding + 290};
    DrawRectangle(backgroundColorsPos.x, backgroundColorsPos.y, buttonWidth, buttonHeight, currentBackgroundColor);
    DrawText("Background Color", backgroundColorsPos.x + buttonWidth / 2 - MeasureText("Background Color", 10) / 2, backgroundColorsPos.y + buttonHeight / 2 - 5, 10, RAYWHITE);
    
    /*
        Make sure this is always on the bottom of the UI.
        The reset button makes sense on the bottom to me.
    */
    Vector2 resetButtonPos = {padding + 10, padding + 330};
    DrawRectangle(resetButtonPos.x, resetButtonPos.y, buttonWidth, buttonHeight, GRAY);
    DrawText("Reset", resetButtonPos.x + buttonWidth / 2 - MeasureText("Reset", 10) / 2, resetButtonPos.y + buttonHeight / 2 - 5, 10, RAYWHITE);
}

int main(void)
{
    const int screenWidth = 854;
    const int screenHeight = 480;

    Color backgroundColors[] = {
        LIGHTGRAY, GRAY, DARKGRAY, SKYBLUE,
        BROWN, MAGENTA, RAYWHITE, BEIGE, BLACK};
    
    InitWindow(screenWidth, screenHeight, "Relaxing Snow Application");
    
    InitAudioDevice();
    Sound sound = LoadSound("mp3/christmas.mp3");
    SetSoundVolume(sound, 10);
    ToggleFullscreen();
    
    Snowdrop drops[MAX_DROPS];

    for (int i = 0; i < MAX_DROPS; i++) 
    {
        drops[i].position.x = GetRandomValue(0, screenWidth);
        drops[i].position.y = GetRandomValue(-screenHeight, 0);
        drops[i].speed = (float)GetRandomValue(50, 100) / 100.0f;
        drops[i].windSpeed = (float)GetRandomValue(-50, 50) / 100.0f;
        drops[i].gravity = (float)GetRandomValue(90, 110) / 100.0f;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        for (int i = 0; i < MAX_DROPS; i++) 
        {
            drops[i].position.y += drops[i].speed * drops[i].gravity;
            drops[i].position.x += drops[i].windSpeed;

            // If a snowdrop reaches the bottom, reset its position to the top
            if (drops[i].position.y > screenHeight) 
            {
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
            Rectangle uniqueColorsPosButton = {10, 210, 75, 30};
            if (CheckCollisionPointRec(mousePos, uniqueColorsPosButton))
            {
                int colorSize = sizeof(colors) / sizeof(colors[0]);
                snowColor = colors[colorIndex];
                colorIndex++;
                if (colorIndex >= colorSize)
                {
                    colorIndex = 0;
                }
            }

            Rectangle blizzardButton = {10, 250, 75, 30};
            if (CheckCollisionPointRec(mousePos, blizzardButton))
            {
                blizzardToggle = !blizzardToggle;
                for (int i = 0; i < MAX_DROPS; i++)
                {
                    if (blizzardToggle)
                    {
                        drops[i].speed = 1.35f;
                        drops[i].gravity = 1.35f;
                    }
                    else
                    {
                        drops[i].speed = (float)GetRandomValue(50, 100) / 100.0f;
                        drops[i].gravity = (float)GetRandomValue(90, 110) / 100.0f;
                    }
                }
            }

            Rectangle backgroundColorButton = {10, 290, 75, 30};
            if (CheckCollisionPointRec(mousePos, backgroundColorButton))
            {
                int backgroundColorSize = sizeof(backgroundColors) / sizeof(backgroundColors[0]);
                backgroundIndex = (backgroundIndex + 1) % backgroundColorSize;
                ClearBackground(backgroundColors[backgroundIndex]);
                if (backgroundIndex >= backgroundColorSize)
                {
                    backgroundIndex = 0;
                }
            }

            /*
                Make sure this is always on the bottom.
                The second integer in the Rectangle struct
                is the height!
                
                Also, this logic needs to get expand upon whenever 
                there is a new feature that effects 
                the Snowflake polygon.
            */
            Rectangle resetButton = {10, 330, 75, 30};
            if (CheckCollisionPointRec(mousePos, resetButton))
            {
                if (soundPlaying == true)
                {
                    StopSound(sound);
                    soundPlaying = false;
                }

                snowDropSize = 10;
                snowDensity = MAX_DROPS;

                snowColor = (Color){255, 255, 255, 200};                

                for (int i = 0; i < MAX_DROPS; i++)
                {
                    drops[i].windSpeed = (float)GetRandomValue(-50, 50) / 100.0f;
                    drops[i].position.x = GetRandomValue(0, screenWidth);
                    drops[i].position.y = GetRandomValue(-screenHeight, 0);
                    drops[i].speed = (float)GetRandomValue(50, 100) / 100.0f;
                    drops[i].gravity = (float)GetRandomValue(90, 110) / 100.0f;
                    drops[i].position.x += drops[i].windSpeed;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(backgroundColors[backgroundIndex - 1]);

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