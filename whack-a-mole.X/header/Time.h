/* 
 * File:   Time.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:10
 */

#ifndef TIME_H
#define	TIME_H

#ifdef	__cplusplus
extern "C" {
#endif

//�c�莞��
uint8_t Time;

//�����K��l�p����
uint16_t TimeForRand;

/* �y�i���e�B�֐�
 * �y�i���e�B�𔭐�������
 * ����
 * �o�� Time �c�莞��
 */
void Penalty(void);

/* �J�E���g�_�E���֐�
 * �J�E���g�_�E�����s��
 * ����
 * �o�� Time �c�莞��
 */
void CountDown(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_H */

