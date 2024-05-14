#include "raylib.h"
#include <stdlib.h>

#define MAX_DROPS 400

typedef struct {
   Vector2 position;
   float speed;
   float windSpeed;
} snowdrop;

Color snowColor = (Color){0, 0, 0, 200};
int snowDropSize = 10;
int snowDensity = MAX_DROPS;

void DrawUI()
{
   const int padding = 10;
   const int buttonWidth = 100;
   const int buttonHeight = 30;

   DrawRectangle(padding, padding, 200, 120, (Color){0, 0, 0, 200});

   Vector2 colorButtonPos = {padding + 10, padding + 10};
   DrawRectangleRec((Rectangle){colorButtonPos.x, colorButtonPos.y, buttonWidth, buttonHeight}, snowColor);
   DrawText("snow Color", colorButtonPos.x + buttonWidth / 2 - MeasureText("snow Color", 10) / 2, colorButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

   Vector2 sizeButtonPos = {padding + 10, padding + 50};
   DrawRectangle(sizeButtonPos.x, sizeButtonPos.y, buttonWidth, buttonHeight, GRAY);
   DrawText(TextFormat("Drop Size: %02d", snowDropSize), sizeButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Drop Size: %02d", snowDropSize), 10) / 2, sizeButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

   Vector2 densityButtonPos = {padding + 10, padding + 90};
   DrawRectangle(densityButtonPos.x, densityButtonPos.y, buttonWidth, buttonHeight, GRAY);
   DrawText(TextFormat("Density: %03d", snowDensity), densityButtonPos.x + buttonWidth / 2 - MeasureText(TextFormat("Density: %03d", snowDensity), 10) / 2, densityButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);

   Vector2 windSpeedButtonPos = {padding + 10, padding + 130};
   DrawRectangle(windSpeedButtonPos.x, windSpeedButtonPos.y, buttonWidth, buttonHeight, GRAY);
   DrawText("Change Wind Speed", windSpeedButtonPos.x + buttonWidth / 2 - MeasureText("Change Wind Speed", 8) / 2, windSpeedButtonPos.y + buttonHeight / 2 - 5, 10, WHITE);
}

int main(void)
{
   const int screenWidth = 900;
   const int screenHeight = 750;

   InitWindow(screenWidth, screenHeight, "R-Snow");

   snowdrop drops[MAX_DROPS];

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
               // Cycle through colors when the color button is clicked
               snowColor = (Color){ (unsigned char)(snowColor.r + 50 > 255 ? 100 : snowColor.r + 50),
                                     (unsigned char)(snowColor.g + 50 > 255 ? 100 : snowColor.g + 50),
                                     (unsigned char)(snowColor.b + 50 > 255 ? 100 : snowColor.b + 50),
                                     255 };
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
           DrawCircle(drops[i].position.x, drops[i].position.y, snowDropSize / 2, snowColor);
       }

       DrawUI();

       EndDrawing();
   }

   CloseWindow();

   return 0;
}