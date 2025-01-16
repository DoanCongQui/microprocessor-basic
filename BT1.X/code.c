#include <xc.h>

// C?u hình các bit c?u hình
#pragma config FOSC = HS        // S? d?ng th?ch anh (High-Speed Oscillator)
#pragma config WDTE = OFF       // T?t Watchdog Timer
#pragma config PWRTE = OFF      // T?t Power-up Timer
#pragma config MCLRE = ON       // S? d?ng chân MCLR
#pragma config CP = OFF         // T?t b?o v? mã ch??ng trình
#pragma config CPD = OFF        // T?t b?o v? d? li?u EEPROM
#pragma config BOREN = OFF      // T?t Brown-out Reset
#pragma config IESO = OFF       // T?t Internal/External Switchover
#pragma config FCMEN = OFF      // T?t Fail-Safe Clock Monitor
#pragma config LVP = OFF        // T?t Low-Voltage Programming
#pragma config DEBUG = OFF      // T?t ch? ?? debug

#define _XTAL_FREQ 4000000      // T?n s? th?ch anh 8 MHz

void main(void) {
    TRISD=0b00000000;

    while (1) {
        PORTD=0x00;
        __delay_ms(500);    // Tr? 500ms

        PORTD=0xFF;
        __delay_ms(500);    // Tr? 500ms
    }
}
