#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "ship.h"
#define BULLET_SPEED 20
struct Bullet {
    int posX, posY;
    int B_SPEED;
    int B_WIDTH;
    int B_HEIGHT;
    bool isMove;
    bool isHit;

    std::vector<Bullet> bullets;
    Bullet(){
        posX = 200;
        posY = SCREEN_HEIGHT/2;
        B_SPEED = 10;
        B_WIDTH = 0;
        B_HEIGHT = 0;
        isMove = false;
        isHit = false;
    }

    Bullet(int x, int y, int speed, int width, int height) {
        posX = x;
        posY = y;
        B_SPEED = speed;
        B_WIDTH = width;
        B_HEIGHT = height;
        isMove = false;
        isHit = false;
    }

    void HandleEvent(SDL_Event& e, Ship& ship){
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
            switch(e.key.keysym.scancode){
            case SDL_SCANCODE_SPACE:

                    bullets.push_back(Bullet(ship.posX+70, ship.posY+10,BULLET_SPEED,0,0));

                break;
            }
        }
    }


    void Move(){
        for(auto& bullet : bullets){
            bullet.posX += bullet.B_SPEED;
        }
    }
    void SetHit(bool hit){
        isHit = hit;
    }
    bool IsHit(){
        return isHit;
    }
    int GetPosX(){
        return posX;
    }
    int GetPosY(){
        return posY;
    }
    void Reset() {
        bullets.clear();
    }
};




#endif // BULLET_H_INCLUDED
