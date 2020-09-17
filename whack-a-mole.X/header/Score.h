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

extern uint16_t HighScore[3];
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
 * �o�� HighScore[��Փx-1]
 */
void SaveHighScore(uint8_t);

/* �n�C�X�R�A�N���A�֐�
 * �w�肳�ꂽ��Փx��HighScore��0�N���A����
 * ����
 * �o�� HighScore[��Փx-1]
 */
void ClearHighScore(uint8_t);

#ifdef __cplusplus
}
#endif

#endif /* SCORE_H */
