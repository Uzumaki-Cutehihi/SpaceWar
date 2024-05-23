#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "ship.h"
#include "enemy.h"

bool checkCollision(SDL_Rect rect1, const SDL_Rect rect2)
{
    // Kiểm tra xem hai hình chữ nhật có giao nhau không

    if (rect1.x + rect1.w >= rect2.x   && rect2.x + rect2.w >= rect1.x &&
        rect1.y + rect1.h >= rect2.y && rect2.y + rect2.h >= rect1.y)
    {
        return true; // Có va chạm
    }
    return false; // Không có va chạm
}

int UpdateGameTimeAndScore(int& time,
                           int& speed,
                           int& score)

{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}
	if (time % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	time += TIME_INCREASEMENT;

	return time;
}


void saveHighscore(int highscore) {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highscore;
        file.close();
    }
}

int loadHighscore() {
    int highscore = 0;
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highscore;
        file.close();
    }
    return highscore;
}

#endif // LOGIC_H_INCLUDED
