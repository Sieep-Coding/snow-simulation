#ifndef RAYLIB_APP_H
#define RAYLIB_APP_H

#define MAX_DROPS 300
#define MAX_SIZE 10
#include "raylib.h"

void DrawSnowflake(Vector2 position, float size, Color color)
{
    DrawPoly(position, 6, size, GetRandomValue(0, 360), color);
}

Color snowColor = (Color){255, 255, 255, 200};
int snowDropSize = MAX_SIZE;
int snowDensity = MAX_DROPS;
bool soundPlaying = false;

typedef struct {
    Vector2 position;
    float speed;
    float windSpeed;
    float gravity;
    int type;
} Snowdrop;
#endif //RAYLIB_APP_H