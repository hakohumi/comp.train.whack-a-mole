
#include "MusicSheets.h"

#include "Buzzer.h"

// MusicSheets
// 楽譜を管理する
// 楽譜は、テンポ、音符データ配列、最大音符数（楽譜の長さ）
// のデータを保有する

// ドレミの歌のデータ部
static const uint8_t BGMNotes_Doremi[7][NOTE_ARRAY_NUM] = {

    {6, DO},
    {2, RE},
    {6, MI},
    {2, RE},
    {4, MI},
    {4, RE},
    {8, MI}

};

// BGMの楽譜のインスタンス
static const MusicSheets_t BGM_Doremi = {
    // テンポ
    106,

    // データ[ ][ ]
    BGMNotes_Doremi,

    // 楽譜の長さ
    7

};

// 音程デバッグ用楽譜
static const uint8_t DEBUG_PICH_DO[8][NOTE_ARRAY_NUM] = {

    {4, RA},
    {4, SI},
    {4, DO2},
    {4, DO},
    {4, SO},
    {4, RA},
    {4, SI},
    {4, DO2}

};

static const MusicSheets_t BGM_DO = {

    30,
    DEBUG_PICH_DO,
    8

};

// リリース用コロブチカ楽譜

static const MusicSheets_t BGM_Tetris = {

};

/* -------------------------------------------------- */

// BGM楽譜が入るポインタ変数
static MusicSheets_t *MusicSheet;

// 初期化

void MusicSheet_Initialize(void) {
    // BGM_Doremiをロード
    MusicSheet = &BGM_Doremi;

    // 音程確認用
    //    MusicSheet = &BGM_DO;
}

// -------------------------------------------------------------------
// ゲッター
// -------------------------------------------------------------------

// BGMのテンポを取得

uint8_t GetBGMTempo(void) {
    return MusicSheet->Tempo;
}

// BGMの指定された位置の音符を取得

uint8_t *GetBGMCurrentNote(uint16_t pos) {
    return MusicSheet->Notes + (pos * 2);
}

uint8_t GetBGMCurrentNoteLength(uint16_t pos) {
    return *(MusicSheet->Notes + (pos * 2));
}

uint8_t GetBGMCurrentNotePich(uint16_t pos) {
    return *(MusicSheet->Notes + (pos * 2) + 1);
}

// BGMの最大音符数を取得

uint16_t GetBGMMaxNotes(void) {
    return MusicSheet->MAX_NOTE;
}