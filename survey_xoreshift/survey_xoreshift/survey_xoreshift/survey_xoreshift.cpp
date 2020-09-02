// survey_xoreshift.cpp : このファイルには 'main'
// 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <Windows.h>
#include <inttypes.h>
#include <time.h>

#include <chrono>
#include <iostream>

using namespace std;

#define EXE_NUM 10000
#define TEST_CNT 10

enum random_type {
    RAND,
    BIT16,
    BIT32,
    BIT64,
    BIT96,
    BIT128,
};

void algo_random(uint8_t type);
void out_sizeof(void);

void out_average1(void);
void out_average3(void);
void out_cycle(void);

uint16_t xor16(void);
uint32_t xor32(void);
uint32_t xor64(void);
void xorshift(uint8_t);
double algo_measure1(uint8_t type);
double algo_measure2(uint8_t type);
double algo_measure3(uint8_t type);

double calc_average1(uint8_t type);
double calc_average3(uint8_t type);
uint32_t calc_rand_cycle(uint8_t type);

uint32_t calc_average_cycle(uint32_t var);

int main() {
    std::cout << "xorshift テスト" << endl << endl;

    clock_t start = clock();

    // 実行環境の各型のサイズを表示
    out_sizeof();

    // out_average1();

    cout << endl;

    out_average3();

    cout << endl;

    out_cycle();

    printf("\nTotal program execution time:\n");
    printf("%lf[ms]\n", (static_cast<double>(clock()) - start));
}
void out_cycle() {
    for (int c = 0; c < 99; c++) {
        calc_average_cycle(calc_rand_cycle(RAND));
    }

    printf("rand()の周期100回分の平均: %ld\n", calc_rand_cycle(RAND));

    for (int c = 0; c < 99; c++) {
        calc_average_cycle(calc_rand_cycle(BIT16));
    }

    printf("xor16()の周期100回分の平均: %u\n",
           calc_average_cycle(calc_rand_cycle(BIT16)));

    // printf("xor32()の周期: %" PRIu32 "\n", calc_rand_cycle(BIT32));
    // printf("xor64()の周期: %" PRIu32 "\n", calc_rand_cycle(BIT64));
    // printf("xor96()の周期: %" PRIu32 "\n", calc_rand_cycle(BIT96));
    // printf("xor128()の周期: %" PRIu32 "\n", calc_rand_cycle(BIT128));
}

uint32_t calc_average_cycle(uint32_t var) {
    static uint32_t total = 0, count = 0;

    total += var;

    return total / ++count;
}

void out_average1() {
    // パターン1の時間の計測方法
    printf("rand()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average1(RAND));
    printf("xorshift()\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average1(BIT32));

    printf("xor16()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average1(BIT16));
    printf("xor32()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average1(BIT32));
    printf("xor64()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average1(BIT64));
    printf("xor96()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average1(BIT96));
    printf("xor128()\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average1(BIT128));
}

void out_average3() {
    // パターン2の時間の計測方法
    printf("rand()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average3(RAND));
    printf("xorshift()\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average3(BIT32));

    printf("xor16()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average3(BIT16));
    printf("xor32()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average3(BIT32));
    printf("xor64()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average3(BIT64));
    printf("xor96()\t\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average3(BIT96));
    printf("xor128()\tを\t%d回実行した時間の10個の平均: %lf[ms]\n",
           EXE_NUM,
           calc_average3(BIT128));
}

double calc_average1(uint8_t type) {
    double total = 0;

    for (int test_cnt = 0; test_cnt < TEST_CNT; test_cnt++) {
        total += algo_measure1(type);
    }
    return total / TEST_CNT;
}

double calc_average3(uint8_t type) {
    double total = 0;

    for (int test_cnt = 0; test_cnt < TEST_CNT; test_cnt++) {
        total += algo_measure3(type);
    }
    return total / TEST_CNT;
}

double algo_measure1(uint8_t type) {
    clock_t start = clock();

    const int loop = 1000;

    for (int i = 0; i < loop; i++) {
        algo_random(type);
    }

    clock_t end = clock();

    const double time =
        static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0 / loop;
    return time;
}

double algo_measure2(uint8_t type) {
    clock_t start = clock();

    algo_random(type);

    return (static_cast<double>(clock()) - start);
}

double algo_measure3(uint8_t type) {
    chrono::system_clock::time_point start, end;

    start = chrono::system_clock::now();

    algo_random(type);

    end = chrono::system_clock::now();

    double time = static_cast<double>(
        chrono::duration_cast<chrono::microseconds>(end - start).count() /
        1000.0);

    return time;
}

void algo_random(uint8_t type) {
    switch (type) {
        case RAND:
            for (int c = EXE_NUM; c > 0; c--) {
                rand();
            }
            break;
        case BIT16:
        case BIT32:
        case BIT64:
        case BIT96:
        case BIT128:
            for (int c = EXE_NUM; c > 0; c--) {
                xorshift(type);
            }
            break;

        default:
            cout << "algo_random error" << endl;
            break;
    }
}

uint16_t xor16(void) {
    static uint16_t x = 1, y = 1;
    uint16_t t = (x ^ (x << 5));
    x          = y;
    return y   = (y ^ (y >> 1)) ^ (t ^ (t >> 3));
}

uint32_t xor32(void) {
    static uint32_t y = 2463534242;
    y                 = y ^ (y << 13);
    y                 = y ^ (y >> 17);
    return y          = y ^ (y << 5);
}

uint32_t xor64(void) {
    static uint64_t x = 88172645463325252ULL;
    x                 = x ^ (x << 13);
    x                 = x ^ (x >> 7);
    return x          = x ^ (x << 17);
}

uint32_t xor96(void) {
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    uint32_t t;

    t        = (x ^ (x << 3)) ^ (y ^ (y >> 19)) ^ (z ^ (z << 6));
    x        = y;
    y        = z;
    return z = t;
}

uint32_t xor128(void) {
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;

    t        = x ^ (x << 11);
    x        = y;
    y        = z;
    z        = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

void xorshift(uint8_t type) {
    switch (type) {
        case BIT16:
            xor16();
            break;
        case BIT32:
            xor32();
            break;
        case BIT64:
            xor64();
            break;
        case BIT96:
            xor96();
            break;
        case BIT128:
            xor128();
            break;
        default:
            cout << "error" << endl;
            break;
    }
}

uint32_t calc_rand_cycle(uint8_t type) {
    uint32_t init_rand = 0;
    uint32_t count     = 0;

    switch (type) {
        case RAND:
            init_rand = rand();
            while (init_rand != rand()) {
                count++;
            }
            break;

        case BIT16:
            init_rand = xor16();
            while (init_rand != xor16()) {
                count++;
            }
            break;

        case BIT32:
            init_rand = xor32();
            while (init_rand != xor32()) {
                count++;
            }
            break;

        case BIT64:
            init_rand = xor64();
            while (init_rand != xor64()) {
                count++;
            }
            break;

        case BIT96:
            init_rand = xor96();
            while (init_rand != xor96()) {
                count++;
            }
            break;

        case BIT128:
            init_rand = xor128();
            while (init_rand != xor128()) {
                count++;
            }
            break;

        default:
            cout << "error" << endl;
            break;
    }

    return count;
}

void out_sizeof() {
    double *dbl_pnt;
    int *int_pnt;
    long *long_pnt;
    long long *longlong_pnt;

    printf("> Basic data type:\n");
    printf("  sizeof (char)     = %d\n", sizeof(char));
    printf("  sizeof (uchar)    = %d\n", sizeof(unsigned char));
    printf("  sizeof (short)    = %d\n", sizeof(short));
    printf("  sizeof (ushort)   = %d\n", sizeof(unsigned short));
    printf("  sizeof (int)      = %d\n", sizeof(int));
    printf("  sizeof (*int)     = %d\n", sizeof(int_pnt));
    printf("  sizeof (float)    = %d\n", sizeof(float));
    printf("  sizeof (double)   = %d\n", sizeof(double));
    printf("  sizeof (*double)  = %d\n", sizeof(dbl_pnt));

    printf("  sizeof (long)      = %d\n", sizeof(long));
    printf("  sizeof (*long)     = %d\n", sizeof(long_pnt));

    printf("  sizeof (long long )      = %d\n", sizeof(long long));
    printf("  sizeof (*long long )     = %d\n", sizeof(longlong_pnt));

    printf("  RAND_MAX           = %d\n", RAND_MAX);
    cout << endl;
}