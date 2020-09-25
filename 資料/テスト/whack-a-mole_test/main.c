#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "test.h"

//�P�̃e�X�g���s�p�}�N����`
#define TEST_GET_RAND
#define TEST_GET_POP_TIME
#define TEST_POP_DECISION

/**********�ϐ��̐錾**********/
uint16_t i;
uint16_t j;
//�����V�[�h�p����
uint16_t timeForSeed;
//���Ԏ擾�p�̕ϐ�
time_t l_time;

/*****�����e�X�g�p�̒�`*****/
#ifdef TEST_GET_RAND
//�֐����s��
static uint16_t func_count = 0;
//�����i�[�p�z��
uint16_t arrayOfRandVal[10000];
bool matchFlag;
static uint16_t matchCount = 0;
#endif //TEST_GET_RAND

/*****�o�����ԗp�̒�`*****/
#ifdef TEST_GET_POP_TIME
//��Փx�̒�`
typedef enum LevelType_Type{
	EASY,
	NORMAL,
	HARD
} LevelType;
//��Փx
#define LEVEL EASY
//�c�莞��
#define TIME 60

#define MIN_POP_TIME 100
#define MAX_POP_TIME 200
//�o������
uint8_t popTime;
#endif //TEST_GET_POP_TIME

/*****�o������p�̒�`*****/
#ifdef TEST_POP_DECISION
//���萔�l
#define DECISION_NUMBER 0x7FFF
//�o����
uint16_t popCount = 0;
#endif // TEST_POP_DECISION

/**********���C�����[�`��**********/
void main() {
	//���ݎ������V�[�h�l�ɉ��Z
	time(&l_time);
	timeForSeed = (uint16_t)(l_time);
	AddRandSeed(timeForSeed);

/*****�����e�X�g*****/
#ifdef TEST_GET_RAND
	//�֐���10,000����s����
	for (i = 0;i < 10000;i++) {
		arrayOfRandVal[i] = GetRand();
		matchFlag = false;
		for (j = 0; j < i; j++) {
			//���܂łɓ����������擾���ꂽ��
			if (arrayOfRandVal[i] == arrayOfRandVal[j]) {
				matchFlag = true;
			}
		}
		//matchCount���C���N�������g
		if (matchFlag) {
			matchCount++;
		}
		//�������͈͊O�̂Ƃ�assert
		assert(arrayOfRandVal[i] >= 0x0000 && arrayOfRandVal[i] <= 0xFFFF);
	}
	//matchCount�̕\��
	printf("�_�u������=%d\n", matchCount);
	//�����������擾���ꂽ�񐔂�100��ȏ�̂Ƃ�assert
	assert(matchCount < 1000);
#endif // TEST_GET_RAND

/*****�o�����ԃe�X�g*****/
#ifdef TEST_GET_POP_TIME
	//�o�����Ԃ��擾
	popTime = GetPopTime(LEVEL, TIME);
	//�o�����Ԃ�\��
	printf("�o������=%d\n", popTime);
	//�o�����Ԃ��͈͊O�̂Ƃ�assert
	assert(popTime >= MIN_POP_TIME && popTime <= MAX_POP_TIME);
#endif // TEST_GET_POP_TIME

/*****�o������e�X�g*****/
#ifdef TEST_POP_DECISION
	for (j = 0;j < 1000;j++) {
		//�o�������肳�ꂽ�Ƃ�popCount���C���N�������g
		if (PopDecision(DECISION_NUMBER)) {
			popCount++;
		}
	}
	//�o���񐔂�\��
	printf("�o����=%d\n", popCount);
#endif // TEST_POP_DECISION
}