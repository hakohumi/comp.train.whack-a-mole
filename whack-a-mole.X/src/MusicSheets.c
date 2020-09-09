
#include "MusicSheets.h"

// MusicSheets
// 楽譜を管理する
// 楽譜は、テンポ、音符データ配列、最大音符数（楽譜の長さ）
// のデータを保有する

// ドレミの歌のデータ部
static const uint8_t BGMNotes_Doremi[7][NOTE_ARRAY_NUM] = {

    {6, 1}, {2, 2}, {6, 3}, {2, 2}, {4, 3}, {4, 2}, {8, 3}

};

// BGMの楽譜のインスタンス
static const MusicSheets_t BGM_Doremi = {
    // テンポ
    60,

    // データ[ ][ ]
    BGMNotes_Doremi,

    // 楽譜の長さ
    7

};

// BGM楽譜が入るポインタ変数
static MusicSheets_t *MusicSheet;

// 初期化
void MusicSheet_Initialize(void) {
    // BGM_Doremiをロード
    MusicSheet = &BGM_Doremi;
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