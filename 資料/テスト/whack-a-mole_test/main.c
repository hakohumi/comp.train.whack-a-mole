#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "test.h"

//単体テスト実行用マクロ定義
#define TEST_GET_RAND
#define TEST_GET_POP_TIME
#define TEST_POP_DECISION

/**********変数の宣言**********/
uint16_t i;
uint16_t j;
//乱数シード用時間
uint16_t timeForSeed;
//時間取得用の変数
time_t l_time;

/*****乱数テスト用の定義*****/
#ifdef TEST_GET_RAND
//関数実行回数
static uint16_t func_count = 0;
//乱数格納用配列
uint16_t arrayOfRandVal[10000];
bool matchFlag;
static uint16_t matchCount = 0;
#endif //TEST_GET_RAND

/*****出現時間用の定義*****/
#ifdef TEST_GET_POP_TIME
//難易度の定義
typedef enum LevelType_Type{
	EASY,
	NORMAL,
	HARD
} LevelType;
//難易度
#define LEVEL EASY
//残り時間
#define TIME 60

#define MIN_POP_TIME 100
#define MAX_POP_TIME 200
//出現時間
uint8_t popTime;
#endif //TEST_GET_POP_TIME

/*****出現判定用の定義*****/
#ifdef TEST_POP_DECISION
//判定数値
#define DECISION_NUMBER 0x7FFF
//出現回数
uint16_t popCount = 0;
#endif // TEST_POP_DECISION

/**********メインルーチン**********/
void main() {
	//現在時刻をシード値に加算
	time(&l_time);
	timeForSeed = (uint16_t)(l_time);
	AddRandSeed(timeForSeed);

/*****乱数テスト*****/
#ifdef TEST_GET_RAND
	//関数を10,000回実行する
	for (i = 0;i < 10000;i++) {
		arrayOfRandVal[i] = GetRand();
		matchFlag = false;
		for (j = 0; j < i; j++) {
			//今までに同じ乱数が取得されたか
			if (arrayOfRandVal[i] == arrayOfRandVal[j]) {
				matchFlag = true;
			}
		}
		//matchCountをインクリメント
		if (matchFlag) {
			matchCount++;
		}
		//乱数が範囲外のときassert
		assert(arrayOfRandVal[i] >= 0x0000 && arrayOfRandVal[i] <= 0xFFFF);
	}
	//matchCountの表示
	printf("ダブった回数=%d\n", matchCount);
	//同じ乱数が取得された回数が100回以上のときassert
	assert(matchCount < 1000);
#endif // TEST_GET_RAND

/*****出現時間テスト*****/
#ifdef TEST_GET_POP_TIME
	//出現時間を取得
	popTime = GetPopTime(LEVEL, TIME);
	//出現時間を表示
	printf("出現時間=%d\n", popTime);
	//出現時間が範囲外のときassert
	assert(popTime >= MIN_POP_TIME && popTime <= MAX_POP_TIME);
#endif // TEST_GET_POP_TIME

/*****出現判定テスト*****/
#ifdef TEST_POP_DECISION
	for (j = 0;j < 1000;j++) {
		//出現が判定されたときpopCountをインクリメント
		if (PopDecision(DECISION_NUMBER)) {
			popCount++;
		}
	}
	//出現回数を表示
	printf("出現回数=%d\n", popCount);
#endif // TEST_POP_DECISION
}