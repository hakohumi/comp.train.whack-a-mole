/*
 * File:   SheetMusic.h
 * Author: fuminori.hakoishi
 *
 */

#ifndef SHEETMUSIC_H
#define SHEETMUSIC_H

#include "Common.h"

// 音符データの要素
typedef enum {
    NOTE_LENGTH,
    NOTE_PITCH,
    NOTE_ARRAY_NUM,
} NoteArrayType;

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

} SheetMusic_t;

void SheetMusic_Initialize(void);

uint16_t SM_GetTempo(SheetMusic_t *i_SheetMusic);
uint8_t *SM_GetCurrentNote(SheetMusic_t *i_SheetMusic, uint16_t pos);

uint8_t SM_GetCurrentNoteLength(SheetMusic_t *i_SheetMusic, uint16_t pos);
uint8_t SM_GetCurrentNotePich(SheetMusic_t *i_SheetMusic, uint16_t pos);
uint16_t SM_GetMaxNotes(SheetMusic_t *i_SheetMusic);

#endif /* SHEETMUSIC_H */
