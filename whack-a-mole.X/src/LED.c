#include "LED.h"
#ifdef NOUSE
// LEDbitsの値から、bitに対応したLEDを表示させる

void UpdateLED(uint8_t i_LEDbits) {
    LED1 = ~(i_LEDbits & 1 << 0);
    LED2 = ~((i_LEDbits & 1 << 1) && 1 << 1);
    LED3 = ~((i_LEDbits & 1 << 2) && 1 << 2);
    LED4 = ~((i_LEDbits & 1 << 3) && 1 << 3);
    LED5 = ~((i_LEDbits & 1 << 4) && 1 << 4);
    LED6 = ~((i_LEDbits & 1 << 5) && 1 << 5);
    // LED7 = ~((i_LEDbits & 1 << 6) && 1 << 6);
    // LED8 = ~((i_LEDbits & 1 << 7) && 1 << 7);
}
#endif

void UpdateLED(uint8_t i_LEDbits) {
    LED_AllOff();

    if (i_LEDbits > 50) {
        LED1 = LED2 = LED3 = LED4 = LED5 = LED6 = LED_ON;
    } else if (i_LEDbits > 40) {
        LED1 = LED2 = LED3 = LED4 = LED5 = LED_ON;
    } else if (i_LEDbits > 30) {
        LED1 = LED2 = LED3 = LED4 = LED_ON;
    } else if (i_LEDbits > 20) {
        LED1 = LED2 = LED3 = LED_ON;
    } else if (i_LEDbits > 10) {
        LED1 = LED2 = LED_ON;
    } else if (i_LEDbits > 0) {
        LED1 = LED_ON;
    } else {
    }
}

void LED_AllOff() {
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    LED3 = LED_OFF;
    LED4 = LED_OFF;
    LED5 = LED_OFF;
    LED6 = LED_OFF;
    // LED7 = LED_OFF;
    // LED8 = LED_OFF;
}
