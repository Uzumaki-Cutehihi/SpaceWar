#ifndef ENERGY_H_INCLUDED
#define ENERGY_H_INCLUDED

#define ENERGY_POSITION_RANGE 250

struct Energy {
    int posX;
    int posY;
    bool isEaten;
    int type;

    Energy(int _type = 0){
        posX =0;
        posY = 0;
        type = _type;
        isEaten = false;
        srand(time(NULL));
        if(type == ENERGY_1){
            posX = rand() % (SCREEN_WIDTH + ENERGY_POSITION_RANGE) + SCREEN_WIDTH;
            posY = rand() %  (100-490) ;

        }else if(type == ENERGY_2) {
            posX = rand() % (SCREEN_WIDTH + ENERGY_POSITION_RANGE) + SCREEN_WIDTH;
            posY = rand() % (100-350);
        }
    }

    void Move(const int &acceleration) {
        posX += -(ENERGY_SPEED + acceleration);
        if(posX + MAX_ENERGY_WIDTH < 0) {
            posX = rand() % (SCREEN_WIDTH + ENERGY_POSITION_RANGE) + SCREEN_WIDTH;
            if(type == ENERGY_1) {
                posY = rand() % (150-480);
            }
        }
    }

    int GetSpeed(const int &acceleration) {
        return ENERGY_SPEED + acceleration;
    }

    int GetPosX() {
        return posX;
    }

    int GetPosY() {
        return posY;
    }

    void SetEaten(bool eaten) {
        isEaten = eaten;
    }

    bool IsEaten() {
        return isEaten;
    }
};

#endif // ENERGY_H_INCLUDED
