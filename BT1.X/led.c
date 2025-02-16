#include "led.h"

void _8_LED() {
    for(unsigned int i = 0; i < 100; i++) {
        PORTD = 0x00;
        __delay_ms(100);
        PORTD = 0xFF;
        __delay_ms(100);
    }
}

void LED_SANG_DUOI() {
    unsigned char data = 0x80;
    for (unsigned char i = 0; i < 8; i++) {
        PORTC = data >> i;
        __delay_ms(100);
    }
}

void _8_LED_SANG_DUOI_BIT() {
    unsigned int i;
    PORTC = 0x00;
    for(i = 0; i < 8; i++) {
        PORTD = (unsigned char)(0x80 >> i);
        __delay_ms(100);
    }
}

void _16_LED_SANG_DUOI_ARRAY() {
    unsigned char DATA[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
    
    PORTC = 0;
    for (unsigned int i = 0; i < 8; i++) {
        PORTD = DATA[i];
        __delay_ms(100);
    }
    PORTD = 0;

    for (unsigned char i = 0; i < 8; i++) {
        PORTC = DATA[i];
        __delay_ms(100);
    }
    PORTC = 0;
}

void _16_LED_SANG_DUOI_BIT() {
    unsigned int i;
    PORTC = 0x00;
    for(i = 0; i < 8; i++) {
        PORTD = (unsigned char)(0x80 >> i);
        __delay_ms(100);
    }
    PORTD = 0x00;

    for(i = 0; i < 8; i++) {
        PORTC = (unsigned char)(0x80 >> i);
        __delay_ms(100);
    }
    PORTC = 0x00;
}

