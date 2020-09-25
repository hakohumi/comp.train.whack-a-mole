#include "test.h"

/* �e�X�g�Ɏg�p����ϐ����L�q */
// 16bit �V�[�h�l
static uint16_t seedX = 1, seedY = 1;

/**************************************/

/* �e�X�g�Ɏg�p����֐����L�q */
//�V�[�h�l��ύX����֐�
void AddRandSeed(uint16_t i_val) {
    seedY += i_val;
}

/******************************/

/* �e�X�g����֐����L�q */
//�����擾�֐�
uint16_t GetRand(void) {
    uint16_t t = (seedX ^ (seedX << 5));

    seedX = seedY;
    return seedY = (seedY ^ (seedY >> 1)) ^ (t ^ (t >> 3));
}

//���O���\�����Ԏ擾�֐�
uint8_t GetPopTime(uint8_t i_level, uint8_t i_time) {
    uint8_t minPopTime;
    uint8_t maxPopTime;
    uint8_t retVal;

    if (i_level <= 2) {
        minPopTime = 100 >> (i_level);
        maxPopTime = 50 * (4 - i_level);
    }
    else {
        minPopTime = 0;
        maxPopTime = 0;
    }
    if (i_time <= 60) {
        retVal = minPopTime + ((maxPopTime - minPopTime) / 60) * i_time;
    }
    else {
        retVal = 0;
    }
    return retVal;
}

//���O���o������
bool PopDecision(uint16_t i_decisionNumber) {
    bool retVal = false;

    if (GetRand() < i_decisionNumber) {
        retVal = true;
    }
    return retVal;
}