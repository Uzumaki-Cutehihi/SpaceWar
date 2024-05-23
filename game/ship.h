#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "defs.h"
#include "graphics.h"
#include "enemy.h"
#include "logic.h"
#include <bits/stdc++.h>

using namespace std;
#define UP 1
#define DOWN 2
struct Ship
{
    static const int FLY_SPEED = 10;
    static const int FALL_SPEED = 10;

    int posX;
    int posY;
    int status;

    SDL_Texture* texture;
    SDL_Rect* rect;
    Ship()
    {
        posX = 150;
        posY = 200;
        status = 0;

        texture = nullptr;
    }

    void HandleEvent(SDL_Event&e)
    {
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0  )
        {
            if(e.key.keysym.sym == SDLK_UP) {
                status = UP;
            }
            if(e.key.keysym.sym == SDLK_DOWN){
                status = DOWN;
            }
        }
    }

    void Move()
    {
        if(status == UP){

                posY = posY - FLY_SPEED;

        }
        else if(status == DOWN)
        {

                posY = posY + FLY_SPEED;

        }
    }
      int GetPosX()
    {
        return posX;
    }

    int GetPosY()
    {
        return posY;
    }
    void Reset() {
        posX = 150;
        posY = 200;
        status = 0;
    }
    void LogicMove()
    {
        if(posY > SCREEN_HEIGHT) {
            posY = -40;
        }
        if(posY < -40) {
            posY = SCREEN_HEIGHT;
        }
    }
};
bool CheckCollision(Ship& ship, SDL_Rect& char_clip, Enemy& enemy, SDL_Rect& enemy_clip)
{
    bool collide = false;

    int left_a = ship.GetPosX();
    int right_a = ship.GetPosX() + char_clip.w;
    int top_a = ship.GetPosY();
    int bottom_a = ship.GetPosY() + char_clip.h;

    if (enemy.GetType() == ENEMY_TYPE_1)
    {
        const int TRASH_PIXEL_1 = 25;
        const int TRASH_PIXEL_2 = 30;

        int left_b = enemy.GetPosX();
        int right_b = enemy.GetPosX() + enemy.GetWidth();
        int top_b = enemy.GetPosY();
        int bottom_b = enemy.GetPosY() + enemy.GetHeight();

        if (right_a - TRASH_PIXEL_1 >= left_b && left_a + TRASH_PIXEL_1 <= right_b)
        {
            if (bottom_a - TRASH_PIXEL_2 >= top_b)
            {
                collide = true;
            }
        }
    }
    else
    {
        const int TRASH_PIXEL_1 = 22;
        const int TRASH_PIXEL_2 = 18;

        int left_b = enemy.GetPosX() + TRASH_PIXEL_1;
        int right_b = enemy.GetPosX() + enemy_clip.w - TRASH_PIXEL_1;
        int top_b = enemy.GetPosY();
        int bottom_b = enemy.GetPosY() + enemy_clip.h - TRASH_PIXEL_2;

        if (right_a >= left_b && left_a <= right_b)
        {
            if (top_a <= bottom_b && top_a >= top_b)
            {
                collide = true;
            }

            if (bottom_a >= bottom_b && bottom_a <= top_b)
            {
                collide = true;
            }
        }
    }

    return collide;
}


#endif // SHIP_H_INCLUDED
