/*
 * File:   Score.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:57
 */

#include <stdint.h>

#ifndef SCORE_H
#define SCORE_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint16_t Score;

/* �X�R�A���Z�֐�
 * Score��1��������
 * ����
 * �o�� Score(�ő�999)
 */
void IncScore(void);

/* �n�C�X�R�A�L�^�֐�
 * �w�肳�ꂽ��Փx��HighScore��Score�̒l�ŋL�^����
 * ���� Score
 * �o�� void
 */
void SaveHighScore(uint8_t i_level, uint16_t i_score);

/* �n�C�X�R�A�N���A�֐�
 * �w�肳�ꂽ��Փx��HighScore��0�N���A����
 * ���� ��Փx
 * �o�� void
 */
// void ClearHighScore(uint8_t i_level);

/* �n�C�X�R�A�擾�֐�
 * �w�肳�ꂽ��Փx��HighScore��EEEPROM����擾����
 * ���� ��Փx
 * �o�� HighScore uint16_t
 */

uint16_t GetHighScore(uint8_t i_level);

#ifdef __cplusplus
}
#endif

#endif /* SCORE_H */
