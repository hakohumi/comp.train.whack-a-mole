/* 
 * File:   Mole.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:34
 */

#include <stdint.h>
#include <stdbool.h>

#include "Input.h"

#ifndef MOLE_H
#define	MOLE_H

#ifdef	__cplusplus
extern "C" {
#endif

//SW
typedef enum MoleStateType_Type{
    HOLE,   //���O���̌�
    MOLE,   //���O���o����
    HIT     //���O������
} MoleStateType;

/* ���O���\����
 * state ���O���̏�� 
 * popTime ���O���̏o������
 * popFlag ���O���̏o������ ON�ŏo��
 */
typedef struct {
    uint8_t state;
    uint8_t popTime;
    uint8_t valueForCompareSW;
    bool popFlag;
} MoleType;

//���O��1-4
MoleType mole1 = {0,0,(uint8_t)SW1,0};     
MoleType mole2 = {0,0,(uint8_t)SW2,0};
MoleType mole3 = {0,0,(uint8_t)SW3,0};
MoleType mole4 = {0,0,(uint8_t)SW4,0};

/* ���O�������֐�
 * ���O��1-4�̏������s���֐�
 */
void MoleManager(void);

/* ���O��X�����֐�
 * ���O��1�C�ɑ΂��鏈�����s���֐�
 * ���� ���O���̔ԍ�(1-4)
 */ 
void MoleXProcess(MoleType*);

/* ���O���o���֐�
 * ���� ���O���̔ԍ�(1-4)
 * �o�� ���͂ɑΉ����郂�O����state��MOLE��
 * �@�@ popTime�������_���Ɍ��肷��
 */
void OutOfHole(MoleType*);

/* ���O�����ފ֐�
 * ���� ���O���̔ԍ�(1-4)
 * �o�� ���͂ɑΉ����郂�O����state��HIT��
 * �@�@ popTime���Œ�l�Ō��肷��
 */
void Attacked(MoleType*);

/* ���O�����o���֐�
 * ���� ���O���̔ԍ�(1-4)
 * �o�� ���͂ɑΉ����郂�O����state��HOLE�ɂ���
 */
void BackToHole(MoleType*);

/* ���O���o������֐�
 * ���� ���O���o������l(0x00-0xFFFF)
 *      �o������l�͕ʓr�e�[�u������擾����
 * �@�@ �o������l��0x7FFF�̏ꍇ�A50%�̊m����TRUE��Ԃ�
 * �o�� TRUE    ���O�����o��������
 * �@�@ False   ���O�����o�������Ȃ�
 */
bool PopDecision(uint16_t);

#ifdef	__cplusplus
}
#endif

#endif	/* MOLE_H */

