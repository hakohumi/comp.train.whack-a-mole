
#include "SE_MusicSheets.h"

// SE_MusicSheets
// SEの楽譜を管理する
// 楽譜は、テンポ、音符データ配列、最大音符数（楽譜の長さ）
// のデータを保有する

/* -------------------------------------------------- */
// 楽譜データ
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
static const SE_MusicSheets_t SE_DO = {
    // テンポ
    230,

    // データ[ ][ ]
    SENotes_DO,

    // 楽譜の長さ
    3

};
/* -------------------------------------------------- */

/* -------------------------------------------------- */

// SE楽譜が入るポインタ変数
static SE_MusicSheets_t *SE_MusicSheet;

// 初期化

void SE_MusicSheet_Initialize(void) {
    // SE_Doremiをロード
    SE_MusicSheet = &SE_DO;
}

// -------------------------------------------------------------------
// ゲッター
// -------------------------------------------------------------------

// SEのテンポを取得

uint16_t SE_GetTempo(void) {
    return SE_MusicSheet->Tempo;
}

// SEの指定された位置の音符を取得

uint8_t *SE_GetCurrentNote(uint16_t pos) {
    return SE_MusicSheet->Notes + (pos * 2);
}

uint8_t SE_GetCurrentNoteLength(uint16_t pos) {
    return *(SE_MusicSheet->Notes + (pos * 2));
}

uint8_t SE_GetCurrentNotePich(uint16_t pos) {
    return *(SE_MusicSheet->Notes + (pos * 2) + 1);
}

// SEの最大音符数を取得

uint16_t SE_GetMaxNotes(void) {
    return SE_MusicSheet->MAX_NOTE;
}