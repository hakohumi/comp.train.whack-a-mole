/*
 * File:   BGM_MusicSheets.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:46 PM
 */

#ifndef BGM_MUSICSHEETS_H
#define BGM_MUSICSHEETS_H

#include "Common.h"

// 音符データの要素
typedef enum {
    BGM_LENGTH,
    BGM_PITCH,
    BGM_NOTE_ARRAY_NUM,
} BGM_NoteArrayType;

// 楽譜クラス
typedef struct {
    // テンポ
    uint16_t Tempo;
    // 音符データ
    // Data[Pos][Note]
    // Pos 再生位置
    // Note = {Length, Pich}
    // Length 長さ
    // Pitch 高さ
    uint8_t *Notes;
    // 楽譜の長さ(音符の総数)
    uint16_t MAX_NOTE;

} BGM_MusicSheets_t;

void BGM_MusicSheet_Initialize(void);

uint16_t GetBGMTempo(void);
uint8_t *GetBGMCurrentNote(uint16_t pos);
uint8_t GetBGMCurrentNoteLength(uint16_t pos);
uint8_t GetBGMCurrentNotePich(uint16_t pos);
uint16_t GetBGMMaxNotes(void);

#endif /* BGM_sMUSICSHEETS_H */
