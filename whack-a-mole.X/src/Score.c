#include "../header/Score.h"

void incScore(void){
    if(Score<999)
        //スコアを1加算
        Score++;
}

void SaveHighScore(uint8_t i_level){
    HighScore[i_level-1] = Score;
}

void ClearHighScore(uint8_t i_level){
    HighScore[i_level-1] = 0;
}