#include "Level.h"

//ゲーム難易度グローバル変数
uint8_t Level;

uint8_t *STR_LEVEL_EASY   = "EASY";
uint8_t *STR_LEVEL_NORMAL = "NORMAL";
uint8_t *STR_LEVEL_HARD   = "HARD";

//ゲーム難易度設定関数
void SetLevel(uint8_t i_level) {
    //引数が0-2の場合、難易度を設定
    if (i_level < 3) {
        Level = i_level;
    }
}