#include <bits/stdc++.h>
#include "defs.h"
#include "enemy.h"
#include "bullet.h"
#include "defs.h"
#include "energy.h"
#include "graphics.h"
#include "logic.h"
#include "ship.h"
#include "boss.h"


using namespace std;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int time = 0;
    int score = 0;
    int highscore = loadHighscore();
    int acceleration = 0;

    Graphics graphics;
    graphics.init();
    Mix_Music * gMusic = graphics.loadMusic("Sound\\background.mp3");
    graphics.play(gMusic);
    Mix_Chunk * gChange = graphics.loadSound("Sound\\change.mp3");
    Mix_Chunk * gKill = graphics.loadSound("Sound\\kill.mp3");
    Mix_Chunk * gEnd = graphics.loadSound("Sound\\gameover.mp3");
    Mix_Chunk * gShoot = graphics.loadSound("Sound\\shooting.mp3");
    Mix_Chunk * gClick = graphics.loadSound("Sound\\click.mp3");


    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND));

    Ship ship;
    Sprite spaceship;
    SDL_Texture* spaceshipTexture = graphics.loadTexture(SPACE_SPRITE_FILE);
    spaceship.init(spaceshipTexture,SPACE_FRAMES ,SPACE_CLIPS);

    Bullet bullet;
    Sprite lazer;
    SDL_Texture* lazerTexture = graphics.loadTexture(LAZER_SPRITE_FILE);
    lazer.init(lazerTexture, LAZER_FRAMES, LAZER_CLIPS);

    Enemy enemy1(ENEMY_TYPE_1);
    Enemy enemy2 (ENEMY_TYPE_2);
    Enemy enemy3 (ENEMY_TYPE_1);
    Enemy enemy4 (ENEMY_TYPE_2);

    Sprite ship1;
    SDL_Texture* ship1Texture = graphics.loadTexture(ENEMY1_SPRITE_FILE);
    ship1.init(ship1Texture, ENEMY1_FRAMES, ENEMY1_CLIPS);

    Sprite ship2;
    SDL_Texture* ship2Texture = graphics.loadTexture(ENEMY2_SPRITE_FILE);
    ship2.init(ship2Texture, ENEMY2_FRAMES, ENEMY2_CLIPS);

    Sprite ship3;
    SDL_Texture* ship3Texture = graphics.loadTexture(ENEMY3_SPRITE_FILE);
    ship3.init(ship3Texture, ENEMY3_FRAMES, ENEMY3_CLIPS);

    Energy energy1(ENERGY_1);

    Sprite fuel;
    SDL_Texture* fuelTexture = graphics.loadTexture(FUEL_SPRITE_FILE);
    fuel.init(fuelTexture,FUEL_FRAMES ,FUEL_CLIPS );

    Boss boss;
    Sprite alien;
    SDL_Texture* alienTexture = graphics.loadTexture(BOSS_SPRITE_FILE);
    alien.init(alienTexture,  BOSS_FRAMES, BOSS_CLIPS);

    TTF_Font* font = graphics.loadFont("asset/Roboto-Black.ttf", 26);
    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* SCOREText = graphics.renderText("SCORE", font, color);
    SDL_Texture* HIGHSCOREText = graphics.renderText("BESTSCORE", font, color);
    SDL_Texture* scoreText = graphics.renderText(std::to_string(score).c_str(), font, color);
    SDL_Texture* highscoreText = graphics.renderText(std::to_string(highscore).c_str(), font, color);

    SDL_Texture* menuTexture = graphics.loadTexture("img/mainmenu.png");
    SDL_Texture* endTexture = graphics.loadTexture("img/end.png");
    SDL_Texture* soundONButtonTexture = graphics.loadTexture("img/sound_on.png");
    SDL_Texture* soundOFFButtonTexture = graphics.loadTexture("img/sound_off.png");
    SDL_Texture* gamePause = graphics.loadTexture("img/gamePause.png");
    SDL_Texture* gamePlayTexture = graphics.loadTexture("img/gamePlay.png");


    bool quit = false;
    bool music = true;
    bool soundButton = true;
    bool delay = false;
    int state = 0; // 0:menu -> 1:more -> 2:gameplay -> 3: end
    bool die = false;
    int mouse_x, mouse_y;
    SDL_Event event;
    while(!quit) {
        if(state == 0) {
            graphics.prepareScene(menuTexture);
            updateScoreText(graphics, font, highscore, color, scoreText);
            graphics.renderTexture(scoreText,1000,540);

            if(music) {
                graphics.play(gMusic);
            }else{
                graphics.stop(gMusic);
            }

            while(SDL_PollEvent(&event)!=0){
                if(event.type == SDL_MOUSEBUTTONDOWN) {
                        SDL_GetMouseState(&mouse_x,&mouse_y);
                    if(mouse_x >470 && mouse_x<610 ){
                        if(mouse_y > 250 && mouse_y <320){
                            graphics.play(gClick);
                            state = 2;
                        } else if(mouse_y > 370 && mouse_y < 440){
                            graphics.play(gClick);
                            state = 1;
                        } else if(mouse_y > 490 && mouse_y <560) {
                            graphics.play(gClick);
                            quit = true;
                        }
                    }else if(mouse_x > 20 && mouse_x <100 && mouse_y > 30 && mouse_y < 100){
                            graphics.play(gClick);
                            music = !music;
                            soundButton = !soundButton;
                            break;
                    }
                }
            }

        if (soundButton) {
                graphics.renderTexture(soundONButtonTexture, 20, 30);
            } else {
                graphics.renderTexture(soundOFFButtonTexture, 20, 30);
            }
            graphics.presentScene();
        }

        else if(state == 1) {
            graphics.prepareScene(gamePlayTexture);
            while (SDL_PollEvent(&event)!= 0){
                if(event.type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&mouse_x,&mouse_y);
                    if(mouse_x > 320 && mouse_y > 510 && mouse_x < 450 && mouse_y < 560){
                        graphics.play(gClick);
                        state = 0;
                    }else if(mouse_x > 550 && mouse_y > 510 && mouse_x < 710 && mouse_y < 560) {
                        graphics.play(gClick);
                        state = 2;
                    }
                }
            }
    graphics.presentScene();
        }
        else if(state == 2 && !die) {
            int staticks = SDL_GetTicks64();
            int fps = 30;
            UpdateGameTimeAndScore(time, acceleration, score);
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            while(SDL_PollEvent(&event)!=0) {
                if(event.type == SDL_QUIT) {
                    quit = true;
                }
                ship.HandleEvent(event);
                bullet.HandleEvent(event, ship);

                if(currentKeyStates[SDL_SCANCODE_UP]) graphics.play(gChange);
                if(currentKeyStates[SDL_SCANCODE_DOWN]) graphics.play(gChange);
                if(currentKeyStates[SDL_SCANCODE_SPACE]) graphics.play(gShoot);
                if(currentKeyStates[SDL_SCANCODE_ESCAPE]) delay = !delay;
            }
           if(delay) {
            graphics.renderTexture(gamePause,130,100);
            graphics.presentScene();

            while(delay) {
                while(SDL_PollEvent(&event)!= 0 ){
                    if(event.type == SDL_QUIT) {
                        quit = true;
                        delay = false;
                    }
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                        delay = false;
                    }
                }
            }
           }
           spaceship.tick(); lazer.tick();
           ship1.tick(); ship2.tick(); ship3.tick();
           fuel.tick(); alien.tick();



            background.scroll(BG_SPEED); graphics.render(background);

            SDL_Rect* ship_rect = spaceship.getCurrentClip();
            SDL_Rect shipRect = {ship.GetPosX(),ship.GetPosY(), ship_rect->w, ship_rect->h};

            SDL_Rect* enemy1_rect = ship1.getCurrentClip();
            SDL_Rect enemy1Rect = {enemy1.GetPosX() + 60, enemy1.GetPosY() + 10, enemy1_rect->w - 80, enemy1_rect->h };


            SDL_Rect* enemy2_rect = ship2.getCurrentClip();
            SDL_Rect enemy2Rect = {enemy2.GetPosX() , enemy2.GetPosY(), enemy2_rect->w , enemy2_rect->h};


            SDL_Rect* enemy3_rect = ship3.getCurrentClip();
            SDL_Rect enemy3Rect = {enemy3.GetPosX() + 20, enemy3.GetPosY() + 30, enemy3_rect->w +50 , enemy3_rect->h +20};

            SDL_Rect* boss_rect = alien.getCurrentClip();
            SDL_Rect bossRect = {boss.GetPosX(), boss.GetPosY(), boss_rect-> w, boss_rect->h};

            SDL_Rect* energy1_rect = fuel.getCurrentClip();
            SDL_Rect energy1Rect = {energy1.GetPosX() + 40, energy1.GetPosY() + 30, energy1_rect->w + 30, energy1_rect->h + 20};

            ship.Move();
            ship.LogicMove();
            graphics.render(ship.posX, ship.posY, spaceship);
            // enemy chuyen dong
             if(score >= 50)  { enemy1.Move(acceleration + 1); graphics.render(enemy1.posX, enemy1.posY, ship1);}
            if(score >= 100) {enemy2.Move(acceleration +2); graphics.render(enemy2.posX, enemy2.posY, ship2);}
            // energy chuyen dong
            if(score>=500) {enemy3.Move(acceleration); graphics.render(enemy3.posX, enemy3.posY,ship3);}
            if(score>=500000) {boss.Move(acceleration); graphics.render(boss.posX, boss.posY, alien);}
            if(energy1.IsEaten()){
                energy1 = Energy(ENERGY_1); energy1.SetEaten(false);}
            if(score>1000){
                    energy1.Move(0);graphics.render(energy1.posX, energy1.posY, fuel);
                }
                if(enemy1.IsDie()){ enemy1 = Enemy(ENEMY_TYPE_1); score+= 100; enemy1.SetDie(false);}
                if(enemy2.IsDie()){ enemy2 = Enemy(ENEMY_TYPE_2);   score+= 60; enemy2.SetDie(false);}
                if(enemy3.IsDie()){enemy3 = Enemy(ENEMY_TYPE_1); score+= 70; enemy3.SetDie(false);}
                if(boss.IsDie()) {boss.SetDie(false);}

            for(auto& bullet : bullet.bullets) {
                if(bullet.IsHit()) {bullet.SetHit(false);}
            }

            bullet.Move();

            for (auto& bullet : bullet.bullets) { graphics.render(bullet.posX, bullet.posY, lazer);}
            if(checkCollision(shipRect, enemy1Rect) ){
                graphics.play(gEnd);
                die = true;
                state = 3;
            }

            if(checkCollision(shipRect, enemy2Rect) ){
                graphics.play(gEnd);
                die = true;
                state = 3;
            }

            if(checkCollision(shipRect, enemy3Rect) ){
                graphics.play(gEnd);
                die = true;
                state = 3;
            }


            if (checkCollision(shipRect, energy1Rect)) {
                energy1.SetEaten(true);
                score += 500;
            }

            if(checkCollision(shipRect, bossRect)) {
                graphics.play(gEnd);
                die = true;
                state = 3;
            }

            for(auto& bullet : bullet.bullets) {
                SDL_Rect* bullet_rect = lazer.getCurrentClip();
               SDL_Rect bulletRect = {bullet.GetPosX(), bullet.GetPosY(), bullet_rect->w , bullet_rect->h};
               if(checkCollision(enemy1Rect, bulletRect)){ graphics.play(gKill); enemy1.SetDie(true); bullet.SetHit(true);}
                if(checkCollision(enemy2Rect, bulletRect)){graphics.play(gKill); enemy2.SetDie(true);bullet.SetHit(true);}
                if(checkCollision(enemy3Rect, bulletRect)){graphics.play(gKill); enemy3.SetDie(true);bullet.SetHit(true);}
            }


              bullet.bullets.erase(std::remove_if(bullet.bullets.begin(), bullet.bullets.end(), [](Bullet& b) { return b.IsHit(); }), bullet.bullets.end());
            if (score > highscore) { highscore = score; saveHighscore(highscore);}
            updateScoreText(graphics, font, score, color, scoreText);
            graphics.renderTexture(scoreText, 890, 20);

            updateScoreText(graphics, font, highscore, color, scoreText);
            graphics.renderTexture(scoreText, 890, 60);


            graphics.renderTexture(HIGHSCOREText, 730, 60);
            graphics.renderTexture(SCOREText, 730, 20);

            graphics.presentScene();
            int frame_stick = SDL_GetTicks64() - staticks;
            if(frame_stick < 1000/fps){
                SDL_Delay(1000/fps - frame_stick);
            }
            }
        else if(state == 3) {
            graphics.presentScene();
            graphics.prepareScene(endTexture);


            while (SDL_PollEvent(&event)!=0) {
                if(event.type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&mouse_x,&mouse_y);
                    if(mouse_x > 440 && mouse_x < 640 && mouse_y > 350 && mouse_y < 400){
                         graphics.play(gClick);
                        score = 0;
                        acceleration = 0;
                        enemy1.Reset();
                        enemy2.Reset();
                        enemy3.Reset();
                        bullet.Reset();
                        die = false;
                        state = 2;
                        break;
                    } else if(mouse_x > 470 && mouse_x < 600 && mouse_y > 460 && mouse_y < 500){
                        graphics.play(gClick);
                        quit = true;
                    }
                }
            }
             graphics.presentScene();
        }

    }
    SDL_DestroyTexture(ship.texture);
    SDL_DestroyTexture(spaceshipTexture); spaceshipTexture = nullptr;
    SDL_DestroyTexture(ship1Texture); ship1Texture = nullptr;
    SDL_DestroyTexture(fuelTexture); fuelTexture = nullptr;
    SDL_DestroyTexture(ship2Texture); ship2Texture = nullptr;
    SDL_DestroyTexture(ship3Texture); ship3Texture = nullptr;
    SDL_DestroyTexture(alienTexture); alienTexture = nullptr;
     graphics.quit();
     return 0;
}
