
#include "BGM_MusicSheets.h"

// BGMMusicSheets
// BGMの楽譜を管理する
// 楽譜は、テンポ、音符データ配列、最大音符数（楽譜の長さ）
// のデータを保有する

/* -------------------------------------------------- */
// ドレミの歌のデータ部
/* -------------------------------------------------- */

static const uint8_t BGMNotes_Doremi[7][BGM_NOTE_ARRAY_NUM] = {

    {4, DO},
    {4, RE},
    {4, MI},
    {4, FA},
    {4, SO},
    {4, RA_},
    {4, SI}

};

// BGMの楽譜のインスタンス
static const BGM_MusicSheets_t BGM_Doremi = {
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

    {4, RA_},
    {4, SI},
    {4, DO2},
    {4, DO},
    {4, SO},
    {4, RA_},
    {4, SI},
    {4, DO2}

};

static const BGM_MusicSheets_t BGM_DO = {

    30,
    DEBUG_PICH_DO,
    8

};

/* -------------------------------------------------- */
// リリース用コロブチカ楽譜
/* -------------------------------------------------- */

static const uint8_t BGMNotes_Tetris[][BGM_NOTE_ARRAY_NUM] = {
    {8, MI2},  //1
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
static const BGM_MusicSheets_t BGM_Tetris = {

    302,
    BGMNotes_Tetris,
    sizeof(BGMNotes_Tetris) / sizeof(uint8_t *)

};

/* -------------------------------------------------- */

// BGM楽譜が入るポインタ変数
static BGM_MusicSheets_t *BGM_MusicSheet;

// 初期化

void BGM_MusicSheet_Initialize(void) {
    // BGM_Doremiをロード
    BGM_MusicSheet = &BGM_Doremi;

    // 音程確認用
    //    MusicSheet = &BGM_DO;
}

// -------------------------------------------------------------------
// ゲッター
// -------------------------------------------------------------------

// BGMのテンポを取得

uint16_t GetBGMTempo(void) {
    return BGM_MusicSheet->Tempo;
}

// BGMの指定された位置の音符を取得

uint8_t *GetBGMCurrentNote(uint16_t pos) {
    return BGM_MusicSheet->Notes + (pos * 2);
}

uint8_t GetBGMCurrentNoteLength(uint16_t pos) {
    return *(BGM_MusicSheet->Notes + (pos * 2));
}

uint8_t GetBGMCurrentNotePich(uint16_t pos) {
    return *(BGM_MusicSheet->Notes + (pos * 2) + 1);
}

// BGMの最大音符数を取得
uint16_t GetBGMMaxNotes(void) {
    return BGM_MusicSheet->MAX_NOTE;
}