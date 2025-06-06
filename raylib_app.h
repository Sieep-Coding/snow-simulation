#ifndef RAYLIB_APP_H
#define RAYLIB_APP_H

#define MAX_DROPS 300
#define MAX_SIZE 10
#include "raylib.h"

typedef struct
{
    Vector2 position;
    float speed;
    float windSpeed;
    float gravity;
    int type;
} Snowdrop;

Color snowColor = (Color){255, 255, 255, 200};
Color currentBackgroundColor = BLACK;

void DrawSnowflake(Vector2 position, float size, Color color)
{
    DrawPoly(position, 6, size, GetRandomValue(0, 360), color);
}

int snowDropSize = MAX_SIZE;
int snowDensity = MAX_DROPS;
int colorIndex = 0;
int backgroundIndex = 0;
bool soundPlaying = false;
bool blizzardToggle = false;


Color colors[] =
    {
        PINK, BLUE, GOLD, RED, LIGHTGRAY,
        GRAY, YELLOW, ORANGE, DARKGRAY,
        GREEN, LIME, DARKGREEN, SKYBLUE,
        VIOLET, DARKPURPLE, PURPLE,
        BROWN, MAGENTA, RAYWHITE, BEIGE};

Color backgroundColors[] =
    {
            BLACK, LIGHTGRAY, GRAY, DARKGRAY, SKYBLUE,
            BROWN, MAGENTA, RAYWHITE, BEIGE, BLACK};

#endif // RAYLIB_APP_H