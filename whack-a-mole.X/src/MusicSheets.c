
#include "MusicSheets.h"

// 楽譜

typedef struct {
    uint8_t Tempo;
    // 音データ
    // Data[Pos][Note]
    // Pos 再生位置
    // Note = {Length, Pithc}
    // Length 長さ
    // Pitch 高さ
    uint8_t *Data;
    // 楽譜の長さ(音符の総数)
    uint16_t MAX_NOTE;
} MusicSheets_t;

static MusicSheets_t MusicSheets1{// テンポ
    60,
    // データ[ ][ ]
    BGMData_MusicSheets1,
    // 楽譜の長さ
    13};
// ドレミの歌
static const uint8_t BGMData_MusicSheets1[13][2] = {
    {6, 1}, {2, 2}, {6, 3}, {2, 2}, {4, 3}, {4, 2}, {8, 3}};
