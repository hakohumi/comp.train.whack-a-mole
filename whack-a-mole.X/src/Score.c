#include "Score.h"

void incScore(void){
    if(Score<999)
        //ƒXƒRƒA‚ð1‰ÁŽZ
        Score++;
}

void SaveHighScore(uint8_t i_level){
    HighScore[i_level] = Score;
}

void ClearHighScore(uint8_t i_level){
    HighScore[i_level] = 0;
}