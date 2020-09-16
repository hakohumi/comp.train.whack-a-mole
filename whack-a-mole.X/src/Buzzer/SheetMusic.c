

#include <__null.h>

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

static const uint8_t BGMNotes_Doremi[7][NOTE_ARRAY_NUM] = {

    {4, DO},
    {4, RE},
    {4, MI},
    {4, FA},
    {4, SO},
    {4, RA_},
    {4, SI}

};

// BGMの楽譜のインスタンス
static const SheetMusic_t SM_BGM_Doremi = {
    // テンポ
    106,

    // データ[ ][ ]
    BGMNotes_Doremi,

    // 楽譜の長さ
    7

};

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// リリース用コロブチカ楽譜
/* -------------------------------------------------- */

static const uint8_t BGMNotes_Tetris[][NOTE_ARRAY_NUM] = {
    {8, MI2}, // 1
    {4, SI},
    {4, DO2},
    {4, RE2},
    {4, DO2},
    {4, SI},
    {8, RA_},
    {4, RA_},
    {4, DO2},
    {8, MI2},
    {4, RE2},
    {4, DO2},
    {2, SI},
    {4, SI},
    {4, DO2},
    {8, RE2},
    {8, MI2},
    {8, DO2},
    {8, RA_},
    {8, RA_},
    {4, REST},
    {4, REST}

};

// 楽譜インスタンス
static const SheetMusic_t SM_BGM_Tetris = {

    302, BGMNotes_Tetris, sizeof (BGMNotes_Tetris) / sizeof (uint8_t *)

};

/* -------------------------------------------------- */
/* -------------------------------------------------- */
// テスト用効果音楽譜
/* -------------------------------------------------- */

static const uint8_t SENotes_DO[3][NOTE_ARRAY_NUM] = {

    {1, DO2},
    {1, RE2},
    {1, MI2},

};

// SEの楽譜のインスタンス
static const SheetMusic_t SM_SE_Doremi = {
    // テンポ
    230,

    // データ[ ][ ]
    SENotes_DO,

    // 楽譜の長さ
    3

};
/* -------------------------------------------------- */

/* -------------------------------------------------- */


// 初期化
// 入力 楽譜ポインタのアドレス
//      指定する楽譜の番号

void SheetMusic_Initialize(SheetMusic_t **i_SheetMusic,
        uint8_t i_SheetMusicNum) {
    switch (i_SheetMusicNum) {
        case SM_BGM_DOREMI:
            *i_SheetMusic = &SM_BGM_Doremi;
            break;
        case SM_BGM_TETRIS:
            *i_SheetMusic = &SM_BGM_Tetris;
            break;
        case SM_SE_DOREMI:
            *i_SheetMusic = &SM_SE_Doremi;
        default:
            *i_SheetMusic = NULL;
            break;
    }
}

// -------------------------------------------------------------------
// ゲッター
// -------------------------------------------------------------------

// テンポを取得

uint16_t SM_GetTempo(SheetMusic_t *i_SheetMusic) {
    return i_SheetMusic->Tempo;
}

// 指定された位置の音符を取得

uint8_t *SM_GetCurrentNote(SheetMusic_t *i_SheetMusic, uint16_t pos) {
    return i_SheetMusic->Notes + (pos * 2);
}

uint8_t SM_GetCurrentNotePich(SheetMusic_t *i_SheetMusic, uint16_t pos) {
    return *(i_SheetMusic->Notes + (pos * 2) + 1);
}

uint8_t SM_GetCurrentNoteLength(SheetMusic_t *i_SheetMusic, uint16_t pos) {
    return *(i_SheetMusic->Notes + (pos * 2));
}

// 最大音符数を取得

uint16_t SM_GetMaxNotes(SheetMusic_t *i_SheetMusic) {
    return i_SheetMusic->MAX_NOTE;
}