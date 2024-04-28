#include "raylib.h"
#include <stdlib.h>

#define MAX_DROPS 200

typedef struct {
    Vector2 position;
    float speed;
    float windSpeed;
    Color color;
} Raindrop;

int main(void)
{
    const int screenWidth = 700;
    const int screenHeight = 450;

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
            // If a raindrop reaches the bottom, reset its position to the top
            if (drops[i].position.y > screenHeight) {
                drops[i].position.y = GetRandomValue(-screenHeight, 0);
                drops[i].position.x = GetRandomValue(0, screenWidth);
                drops[i].position.y += drops[i].speed;
                drops[i].position.x += drops[i].windSpeed;
            }
        }
        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < MAX_DROPS; i++) {
            Rectangle dropRect = { drops[i].position.x, drops[i].position.y, 2, 10 }; 
            DrawRectangleRec(dropRect, drops[i].color);
        }
        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}
