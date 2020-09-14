/* 
 * File:   State.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 14:50
 */

#ifndef STATE_H
#define	STATE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

//��ʏ�Ԃ̒�`    
typedef enum DisplayStateType_Type{
    TITLE,
    SELECT_LEVEL,
    HS_CLEAR,
    START_COUNT_DOWN,
    PLAYING_GAME,
    RESULT
} DisplayStateType;

//�e��ʏ�Ԃ̃A�N�V�������`(EXIT�͏ȗ�)
typedef enum ActionType_Type{
    ENTRY,
    DO
} ActionType;

//�V�X�e���S�̂̍\����
typedef struct {
    uint8_t displayState;
    uint8_t action;
} SystemStateType;

//�V�X�e���\���̕ϐ�
SystemStateType SystemState;

/* ��ʏ�ԍX�V�ϐ�
 * ��ʏ�Ԃ�ύX����
 * ���� (uint8_t)DisPlayStateType ��ʏ�Ԓ萔
 * �o�� SystemState.displayState �V�X�e���̉�ʏ��
 */
void ChangeState(uint8_t);

/* �^�C�g����ʏ����֐�
 * �^�C�g����ʂ̏������s��
 * ����
 * �o��
 */
void TitleProcess(void);

/* ��Փx�I����ʏ����֐�
 * ��Փx�I����ʂ̏������s��
 * ����
 * �o��
 */
void SelectLevelProcess(void);

/* �n�C�X�R�A�N���A�m�F�ʏ����֐�
 *�n�C�X�R�A�N���A�m�F��ʂ̏������s��
 * ����
 * �o��
 */
void HSClearProcess(void);

/* �Q�[���J�n�J�E���g�_�E����ʏ����֐�
 * �Q�[���J�n�J�E���g�_�E����ʂ̏������s��
 * ����
 * �o��
 */
void StartCountDownProcess(void);

/* �Q�[������ʏ����֐�
 * �Q�[������ʂ̏������s��
 * ����
 * �o��
 */
void PlayingGameProsess(void);

/* ���U���g��ʏ����֐�
 * ���U���g��ʂ̏������s��
 * ����
 * �o��
 */
void ResultProcess(void);

#ifdef	__cplusplus
}
#endif

#endif	/* STATE_H */

