#include "LED.h"

// LEDbitsの値から、bitに対応したLEDを表示させる
void UpdateLED(uint8_t i_LEDbits) {
    LED1 = ~(i_LEDbits & 1 << 0);
    LED2 = ~((i_LEDbits & 1 << 1) && 1 << 1);
    LED3 = ~((i_LEDbits & 1 << 2) && 1 << 2);
    LED4 = ~((i_LEDbits & 1 << 3) && 1 << 3);
    LED5 = ~((i_LEDbits & 1 << 4) && 1 << 4);
    LED6 = ~((i_LEDbits & 1 << 5) && 1 << 5);
    LED7 = ~((i_LEDbits & 1 << 6) && 1 << 6);
    // LED8 = ~((i_LEDbits & 1 << 7) && 1 << 7);
}

void LED_AllOff() {
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    LED3 = LED_OFF;
    LED4 = LED_OFF;
    LED5 = LED_OFF;
    LED6 = LED_OFF;
    LED7 = LED_OFF;
    // LED8 = LED_OFF;
}