/*
 * File:   MusicSheets.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:46 PM
 */

#ifndef MUSICSHEETS_H
#define MUSICSHEETS_H

#include "Common.h"


// 音符データの要素
typedef enum {
    LENGTH,
    PITCH,
    NOTE_ARRAY_NUM,
} NoteArrayType;

// 楽譜クラス
typedef struct {
    // テンポ
    uint8_t Tempo;
    // 音符データ
    // Data[Pos][Note]
    // Pos 再生位置
    // Note = {Length, Pich}
    // Length 長さ
    // Pitch 高さ
    uint8_t *Notes;
    // 楽譜の長さ(音符の総数)
    uint16_t MAX_NOTE;

} MusicSheets_t;

void MusicSheet_Initialize(void);

uint8_t GetBGMTempo(void);
uint8_t *GetBGMCurrentNote(uint16_t pos);
uint8_t GetBGMCurrentNoteLength(uint16_t pos);
uint8_t GetBGMCurrentNotePich(uint16_t pos);
uint16_t GetBGMMaxNotes(void);

#endif /* MUSICSHEETS_H */
