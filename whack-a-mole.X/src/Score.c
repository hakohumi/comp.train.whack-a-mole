#include "../header/Score.h"

void incScore(void){
    if(Score<999)
        //�X�R�A��1���Z
        Score++;
}

void SaveHighScore(uint8_t i_level){
    HighScore[i_level-1] = Score;
}

void ClearHighScore(uint8_t i_level){
    HighScore[i_level-1] = 0;
}