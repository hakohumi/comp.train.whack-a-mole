
#include "SE_MusicSheets.h"

// SE_MusicSheets
// SEの楽譜を管理する
// 楽譜は、テンポ、音符データ配列、最大音符数（楽譜の長さ）
// のデータを保有する

/* -------------------------------------------------- */
// 楽譜データ
/* -------------------------------------------------- */

/* -------------------------------------------------- */

// SE楽譜が入るポインタ変数
static SE_MusicSheets_t *SE_MusicSheet;

// 初期化

void SE_MusicSheet_Initialize(void) {
    // SE_Doremiをロード
    //    SE_MusicSheet = &SE_Tetris;
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