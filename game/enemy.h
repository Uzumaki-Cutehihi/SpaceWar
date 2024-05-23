#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "defs.h"
#include <cstdlib>
#include <ctime>
#define ENEMY_POSITION_RANGE 250


struct Enemy{
    int posX;
    int posY;
    int E_WIDTH;
    int E_HEIGHT;
    int type;
    SDL_Rect* rect;

    bool isDie; //trung dan

    Enemy(int _type = 0) {
        posX = 0;
        posY = 0;
        type = _type;
        isDie = false;
        srand(time(NULL));
        if (type == ENEMY_TYPE_1) {
            posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
            posY = rand() % (0 - 490 ) ;
        }else if (type == ENEMY_TYPE_2) {
            posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
            posY = rand() % (100-320);
        }
    }
    void Move(const int &acceleration) {
        posX += -(ENEMY_SPEED + acceleration); //Cập nhật vị trí theo hướng ngược lại của tốc độ di chuyển của kẻ địch.
        if (posX + MAX_ENEMY_WIDTH < 0) {
            posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH; //đảm bảo kẻ địch xuất hiện bên phải màn hình ngoài màn hình
        }
    }

    int GetType() {
        if (type == ENEMY_TYPE_1) {
            return ENEMY_TYPE_1;
        } else {
            return ENEMY_TYPE_2;
        }
    }

    int GetSpeed(const int &acceleration) {
        return ENEMY_SPEED + acceleration;
    }

    int GetPosX() {
        return posX;
    }

    int GetPosY() {
        return posY;
    }
    int GetWidth(){
        return E_WIDTH;
    }
    int GetHeight(){
        return E_HEIGHT;
    }
    void SetDie(bool die) {
        isDie = die;
    }
    bool IsDie() {
        return isDie;
    }

    void Reset() {
        isDie = false;
        if (type == ENEMY_TYPE_1) {
            posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
            posY = rand() % (50-460) ;
        } else if (type == ENEMY_TYPE_2) {
            posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
            posY = rand() % (100-320);
        }
    }
};


#endif // ENEMY_H_INCLUDED
