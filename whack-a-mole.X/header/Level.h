/* 
 * File:   Level.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:37
 */

#include <stdint.h>

#ifndef LEVEL_H
#define LEVEL_H

#ifdef __cplusplus
extern "C" {
#endif

//ゲーム難易度の定義
typedef enum LevelType_Type {
    EASY,
    NORMAL,
    HARD
} LevelType;

//ゲーム難易度グローバル変数
uint8_t Level;

/* 難易度設定関数
 * 入力 ゲーム難易度
 * 出力　Levelを変更する
 */
void SetLevel(uint8_t);

extern uint8_t *STR_LEVEL_EASY;
extern uint8_t *STR_LEVEL_NORMAL;
extern uint8_t *STR_LEVEL_HARD;

#define STR_LEVEL_EASY_LEN 4
#define STR_LEVEL_NORMAL_LEN 6
#define STR_LEVEL_HARD_LEN 4

#ifdef __cplusplus
}
#endif

#endif /* LEVEL_H */
