/*
 * File:   SE_MusicSheets.h
 * Author: fuminori.hakoishi
 *
 */

#ifndef SE_MUSICSHEETS_H
#define SE_MUSICSHEETS_H

#include "Common.h"

// 音符データの要素
typedef enum {
    SE_LENGTH,
    SE_PITCH,
    SE_NOTE_ARRAY_NUM,
} SE_NoteArrayType;


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

} SE_MusicSheets_t;

void SE_MusicSheet_Initialize(void);

uint16_t SE_GetTempo(void);
uint8_t *SE_GetCurrentNote(uint16_t pos);
uint8_t SE_GetCurrentNoteLength(uint16_t pos);
uint8_t SE_GetCurrentNotePich(uint16_t pos);
uint16_t SE_GetMaxNotes(void);

#endif /* SE_sMUSICSHEETS_H */
