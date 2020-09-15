#include "Level.h"

//ゲーム難易度設定関数
void SetLevel(uint8_t i_level){
    //引数が0-2の場合、難易度を設定
    if(i_level<3){
        Level = i_level;        
    }
}