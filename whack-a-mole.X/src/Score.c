#include "Score.h"

//ハイスコア配列[難易度-1]
uint16_t HighScore[3];

//スコア
uint16_t Score;

void IncScore(void) {
    if (Score < 999)
        //�X�R�A��1���Z
        Score++;
}

void SaveHighScore(uint8_t i_level) {
    HighScore[i_level] = Score;
}

void ClearHighScore(uint8_t i_level) {
    HighScore[i_level] = 0;
}