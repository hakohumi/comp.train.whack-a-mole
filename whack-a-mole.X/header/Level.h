/* 
 * File:   Level.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:37
 */

#ifndef LEVEL_H
#define	LEVEL_H

#ifdef	__cplusplus
extern "C" {
#endif

//ゲーム難易度の定義
typedef enum LevelType_Type{
    EASY = 1,
    NORMAL,
    HARD,
}LevelType;

//ゲーム難易度グローバル変数
uint8_t Level;

/* 難易度設定関数
 * 入力 ゲーム難易度
 * 出力　Levelを変更する
 */
void SetLevel(uint8_t);

#ifdef	__cplusplus
}
#endif

#endif	/* LEVEL_H */

