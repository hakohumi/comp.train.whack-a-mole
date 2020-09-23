/* 
 * File:   State.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 14:50
 */

#ifndef STATE_H
#define STATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//画面状態の定義
typedef enum DisplayStateType_Type {
    TITLE,
    SELECT_LEVEL,
    HS_CLEAR,
    START_COUNT_DOWN,
    PLAYING_GAME,
    RESULT
} DisplayStateType;

//各画面状態のアクションを定義(EXITは省略)
typedef enum ActionType_Type {
    ACTION_ENTRY,
    ACTION_DO
} ActionType;

//システム全体の構造体
typedef struct {
    uint8_t displayState;
    uint8_t action;
} SystemStateType;

//システム構造体変数
extern SystemStateType SystemState;

/* 画面状態更新変数
 * 画面状態を変更する
 * 入力 (uint8_t)DisPlayStateType 画面状態定数
 * 出力 SystemState.displayState システムの画面状態
 */
void ChangeState(uint8_t);

/* タイトル画面処理関数
 * タイトル画面の処理を行う
 * 入力
 * 出力
 */
void TitleProcess(void);

/* 難易度選択画面処理関数
 * 難易度選択画面の処理を行う
 * 入力
 * 出力
 */
void SelectLevelProcess(void);

/* ハイスコアクリア確認面処理関数
 *ハイスコアクリア確認画面の処理を行う
 * 入力
 * 出力
 */
void HSClearProcess(void);

/* ゲーム開始カウントダウン画面処理関数
 * ゲーム開始カウントダウン画面の処理を行う
 * 入力
 * 出力
 */
void StartCountDownProcess(void);

/* ゲーム中画面処理関数
 * ゲーム中画面の処理を行う
 * 入力
 * 出力
 */
void PlayingGameProcess(void);

/* リザルト画面処理関数
 * リザルト画面の処理を行う
 * 入力
 * 出力
 */
void ResultProcess(void);

#ifdef __cplusplus
}
#endif

#endif /* STATE_H */
