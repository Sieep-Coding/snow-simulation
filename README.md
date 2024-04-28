## Snow Simulation, using raylib!

This project uses raylib to create a simple "snowfall" effect.

I originally did this in Go and a lot of people seemed to like it. 

I lost those files so if anyone wants to do this in Go, i can help.

![](https://github.com/Alteryx-Motives/rain-project/blob/master/output.gif)


## Pre-compiled binary
coming soon


## Notes

#### Struct

One data structure to define raindrop position, speed, and color.

```c
typedef struct {
    Vector2 position;
    float speed;
    Color color;
} Raindrop;
```

#### Logic

No refactor here! Everything you need is in the ` main() ` function.

This loop  draws each raindrop using `Rectangle` from the ` raylib.h ` file.

If you want more customization, draw the drops as pixels instead.

```c
        for (int i = 0; i < MAX_DROPS; i++) {
            Rectangle dropRect = { drops[i].position.x, drops[i].position.y, 2, 10 }; 
            DrawRectangleRec(dropRect, drops[i].color);
        }
```

#### Customization

Make adjustments to the raindrops here.

```c
    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i].position.x = GetRandomValue(0, screenWidth);
        drops[i].position.y = GetRandomValue(-screenHeight, 0);
        drops[i].speed = (float)GetRandomValue(50, 100) / 100.0f; 
        drops[i].color = WHITE;
    }
```
