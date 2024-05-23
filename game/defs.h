#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <SDL.h>
#include <bits/stdc++.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Hello World!"

const char* BACKGROUND = "img\\background.png";

#define SPEED_INCREASEMENT 5
#define SCORE_INCREASEMENT 6
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define TIME_MAX 800
#define MAX_HEIGHT 300

//enemy
#define ENEMY_MAX_HEIGHT 300
#define ENEMY_MIN_HEIGHT 330
#define ENEMY_POSITION_RANGE 250
#define ENEMY1_RANGE 100
#define ENEMY2_RANGE 250
#define ENEMY3_RANGE 500
#define ENEMY_TYPE_1 1
#define ENEMY_TYPE_2 2

#define ENERGY_1 1
#define ENERGY_2 0

#define GROUND_SPEED 5
#define ENEMY_SPEED 10
#define MAX_ENEMY_WIDTH 100

#define ENERGY_SPEED 7
#define MAX_ENERGY_WIDTH 100

#define BG_SPEED 5
#define CHEST_SPEED 5
#define MAX_CHEST_WIDTH 100

const char*  SPACE_SPRITE_FILE = "img\\ship1.png";
const int SPACE_CLIPS[][4] = {
     {0, 0 , 160, 43 },
    {160, 0 , 160, 43 },
    {320, 0 , 160, 43 },
    {480, 0 , 160, 43 },
    {640, 0 , 160, 43 },
    {800, 0 , 160, 43 },
    {960, 0 , 160, 43 },
    {1120, 0 , 160, 43 },
};
const int SPACE_FRAMES = sizeof(SPACE_CLIPS)/sizeof(int)/4;

const char* FUEL_SPRITE_FILE = "img\\fuel.png";
const int FUEL_CLIPS[][4] = {
    {0,0,100,100},
};
const int FUEL_FRAMES = sizeof(FUEL_CLIPS) / sizeof(FUEL_CLIPS[0]);

const char* LAZER_SPRITE_FILE = "img\\laser.png";
const int LAZER_CLIPS[][4] = {
    {0, 0, 70, 29},
};
const int LAZER_FRAMES = sizeof(LAZER_CLIPS) / sizeof(LAZER_CLIPS[0]);

const char* ENEMY1_SPRITE_FILE = "img\\enemyship1.png";
const int ENEMY1_CLIPS[][4] = {
     {0, 0 , 160, 43 },
    {160, 0 , 160, 43 },
    {320, 0 , 160, 43 },
    {480, 0 , 160, 43 },
    {640, 0 , 160, 43 },
    {800, 0 , 160, 43 },
    {960, 0 , 160, 43 },
    {1120, 0 , 160, 43 },
};
const int ENEMY1_FRAMES = sizeof(ENEMY1_CLIPS)/sizeof(int)/4;

const char* ENEMY2_SPRITE_FILE = "img\\enemyship2.png";
const int ENEMY2_CLIPS[][4] = {
     {0, 0 , 160, 65 },
    {160, 0 , 160, 65 },
    {320, 0 , 160, 65 },
    {480, 0 , 160, 65 },
    {640, 0 , 160, 65 },
    {800, 0 , 160, 65 },
    {960, 0 , 160, 65 },
    {1120, 0 , 160, 65 },
};
const int ENEMY2_FRAMES = sizeof(ENEMY2_CLIPS)/sizeof(int)/4;

const char* ENEMY3_SPRITE_FILE = "img\\meteor.png";
const int ENEMY3_CLIPS[][4] = {
     {0, 0 , 75, 70 },
     {75, 0 , 75, 70 },
     {135, 0 , 75, 70 },
     {210, 0 , 75, 70 },
     {285, 0 , 75, 70 },
};
const int ENEMY3_FRAMES = sizeof(ENEMY3_CLIPS)/sizeof(int)/4;

const char* BOSS_SPRITE_FILE = "img\\boss.png";
const int BOSS_CLIPS[][4] = {
     {0, 0 , 275, 350 },
     {275, 0 , 275, 350 },
     {550, 0 , 275, 350 },
     {825, 0 , 275, 350 },
     {1100, 0 , 275, 350 },
     {1375, 0 , 275, 350 },
     {1650, 0 , 275, 350 },
     {1925, 0 , 275, 350 },
     {2200, 0 , 275, 350 },
};
const int BOSS_FRAMES = sizeof(BOSS_CLIPS)/sizeof(int)/4;


#endif // DEFS_H_INCLUDED
