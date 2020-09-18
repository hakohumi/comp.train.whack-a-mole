#include "Score.h"

#include "Level.h"
#include "memory.h"

//スコア
uint16_t Score;

void IncScore(void) {
    if (Score < 999)
        //�X�R�A��1���Z
        Score++;
}

void SaveHighScore(uint8_t i_level, uint16_t i_score) {
    uint8_t l_addrL  = EEPROM_ADDR_ERROR;
    uint8_t l_addrH  = EEPROM_ADDR_ERROR2;
    uint16_t l_Score = i_score;

    switch (i_level) {
        case EASY:
            l_addrL = EEPROM_ADDR_HIGHSCORE_EASY_L;
            l_addrH = EEPROM_ADDR_HIGHSCORE_EASY_H;
            break;
        case NORMAL:
            l_addrL = EEPROM_ADDR_HIGHSCORE_NORMAL_L;
            l_addrH = EEPROM_ADDR_HIGHSCORE_NORMAL_H;
            break;
        case HARD:
            l_addrL = EEPROM_ADDR_HIGHSCORE_HARD_L;
            l_addrH = EEPROM_ADDR_HIGHSCORE_HARD_H;
            break;
        default:
            break;
    }

    DATAEE_WriteByte(l_addrH, (l_Score & 0xFF00) >> 8);
    DATAEE_WriteByte(l_addrL, l_Score & 0x00FF);
}

// void ClearHighScore(uint8_t i_level) {
//     switch (i_level) {
//         case EASY:
//             DATAEE_WriteByte(EEPROM_ADDR_HIGHSCORE_EASY_L, 0);
//             DATAEE_WriteByte(EEPROM_ADDR_HIGHSCORE_EASY_H, 0);
//             break;
//         case NORMAL:
//             DATAEE_WriteByte(EEPROM_ADDR_HIGHSCORE_NORMAL_L, 0);
//             DATAEE_WriteByte(EEPROM_ADDR_HIGHSCORE_NORMAL_H, 0);
//             break;
//         case HARD:
//             DATAEE_WriteByte(EEPROM_ADDR_HIGHSCORE_HARD_L, 0);
//             DATAEE_WriteByte(EEPROM_ADDR_HIGHSCORE_HARD_H, 0);
//             break;
//         default:
//             break;
//     }
// }

uint16_t GetHighScore(uint8_t i_level) {
    uint16_t l_highscore = 0xFFFF;
    uint8_t l_addr       = EEPROM_ADDR_ERROR;

    switch (i_level) {
        case EASY:
            l_addr = EEPROM_ADDR_HIGHSCORE_EASY_L;
            break;
        case NORMAL:
            l_addr = EEPROM_ADDR_HIGHSCORE_NORMAL_L;
            break;
        case HARD:
            l_addr = EEPROM_ADDR_HIGHSCORE_HARD_L;
            break;
        default:
            break;
    }

    // 下位ビット
    l_highscore = 0x00FF & (uint16_t)(DATAEE_ReadByte(l_addr));
    // 上位ビット
    l_highscore |= (uint16_t)(DATAEE_ReadByte(l_addr + 1)) << 8;

    return l_highscore;
}