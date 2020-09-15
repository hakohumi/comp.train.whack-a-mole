

#include "SheetMusic.h"

// SheetMusic
// SEの楽譜を管理する
// 楽譜は、テンポ、音符データ配列、最大音符数（楽譜の長さ）
// のデータを保有する

/* -------------------------------------------------- */
// 楽譜データ
/* -------------------------------------------------- */
/* -------------------------------------------------- */
// ドレミの歌のデータ部
/* -------------------------------------------------- */

static const uint8_t BGMNotes_Doremi[7][BGM_NOTE_ARRAY_NUM] = {

    {4, DO}, {4, RE},  {4, MI}, {4, FA},
    {4, SO}, {4, RA_}, {4, SI}

};

// BGMの楽譜のインスタンス
static const SheetMusic_t BGM_Doremi = {
    // テンポ
    106,

    // データ[ ][ ]
    BGMNotes_Doremi,

    // 楽譜の長さ
    7

};

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// 音程デバッグ用楽譜
/* -------------------------------------------------- */

static const uint8_t DEBUG_PICH_DO[8][BGM_NOTE_ARRAY_NUM] = {

    {4, RA_}, {4, SI}, {4, DO2}, {4, DO}, {4, SO},
    {4, RA_}, {4, SI}, {4, DO2}

};

static const SheetMusic_t BGM_DO = {

    30, DEBUG_PICH_DO, 8

};

/* -------------------------------------------------- */
// リリース用コロブチカ楽譜
/* -------------------------------------------------- */

static const uint8_t BGMNotes_Tetris[][BGM_NOTE_ARRAY_NUM] = {
    {8, MI2},  // 1
    {4, SI},  {4, DO2},  {4, RE2}, {4, DO2}, {4, SI},  {8, RA_},
    {4, RA_}, {4, DO2},  {8, MI2}, {4, RE2}, {4, DO2}, {2, SI},
    {4, SI},  {4, DO2},  {8, RE2}, {8, MI2}, {8, DO2}, {8, RA_},
    {8, RA_}, {4, REST}, {4, REST}

};

// 楽譜インスタンス
static const SheetMusic_t BGM_Tetris = {

    302, BGMNotes_Tetris, sizeof(BGMNotes_Tetris) / sizeof(uint8_t *)

};

/* -------------------------------------------------- */
/* -------------------------------------------------- */
// テスト用効果音楽譜
/* -------------------------------------------------- */

static const uint8_t SENotes_DO[3][SE_NOTE_ARRAY_NUM] = {

    {1, DO2},
    {1, RE2},
    {1, MI2},

};

// SEの楽譜のインスタンス
static const SheetMusic_t SE_DO = {
    // テンポ
    230,

    // データ[ ][ ]
    SENotes_DO,

    // 楽譜の長さ
    3

};
/* -------------------------------------------------- */

/* -------------------------------------------------- */

// BGM楽譜が入るポインタ変数
static SheetMusic_t *BGM_MusicSheet;
// SE楽譜が入るポインタ変数
static SheetMusic_t *SE_MusicSheet;

// 初期化

void MusicSheet_Initialize(void) {
    // BGM_Doremiをロード
    BGM_MusicSheet = &BGM_Doremi;
    // SE_Doremiをロード
    SE_MusicSheet = &SE_DO;
}

// -------------------------------------------------------------------
// ゲッター
// -------------------------------------------------------------------

// テンポを取得
uint16_t SM_GetTempo(SheetMusic_t *i_SheetMusic) { return i_SheetMusic->Tempo; }

// 指定された位置の音符を取得
uint8_t *SM_GetCurrentNote(SheetMusic_t *i_SheetMusic, uint16_t pos) {
    return i_SheetMusic->Notes + (pos * 2);
}

uint8_t SM_GetCurrentNotePich(SheetMusic_t *i_SheetMusic, uint16_t pos) {
    return *(i_MusicSheet->Notes + (pos * 2) + 1);
}

uint8_t SM_GetCurrentNoteLength(SheetMusic_t *i_SheetMusic, uint16_t pos) {
    return *(i_MusicSheet->Notes + (pos * 2));
}

// 最大音符数を取得
uint16_t SM_GetMaxNotes(SheetMusic_t *i_SheetMusic) {
    return i_MusicSheet->MAX_NOTE;
}