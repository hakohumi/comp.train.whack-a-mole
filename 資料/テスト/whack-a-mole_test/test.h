#pragma once

#include <stdint.h>
#include <stdbool.h>

/* �e�X�g�Ɏg�p����֐����L�q */
void AddRandSeed(uint16_t);

/* �e�X�g����֐����L�q */
uint16_t GetRand(void);

//���O���o�����Ԏ擾�֐�
uint8_t GetPopTime(uint8_t, uint8_t);

//���O���o������
bool PopDecision(uint16_t);