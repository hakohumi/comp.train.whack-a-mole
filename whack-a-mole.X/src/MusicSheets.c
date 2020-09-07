
#include "MusicSheets.h"

// ドレミの歌のデータ部
static const uint8_t BGMNotes_Doremi[7][NOTE_ARRAY_NUM] = {
    {6, 1},
    {2, 2},
    {6, 3},
    {2, 2},
    {4, 3},
    {4, 2},
    {8, 3}

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

static MusicSheets_t *this;

void InitializeBGM(void) {
    this = &BGM_Doremi;
}

// -------------------------------------------------------------------
// ゲッター
// -------------------------------------------------------------------

uint8_t GetBGMTempo(void) {
    return this->Tempo;
}

uint8_t **GetBGMNotes(void) {
    return this->Notes;
}

uint8_t *GetBGMNote(uint16_t pos) {
    return 0;
}

uint16_t GetBGMMaxNotes(void) {
    return this->MAX_NOTE;
}