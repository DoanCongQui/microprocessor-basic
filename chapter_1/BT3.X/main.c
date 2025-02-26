/*
 * File:   main.c
 * Author: dq
 *
 * Created on February 26, 2025, 1:44 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)  

#include <xc.h>

#define _XTAL_FREQ 4000000      //Thach Anh 4MHz

#include <xc.h>

void _8_LED_SANG_DON();

void main(void) {
    TRISD = 0x00;
    _8_LED_SANG_DON();
}

void _8_LED_SANG_DON() {
    unsigned char i, tempo, dat_D;
    signed char j;

    while (1) {
        tempo = 0x00;
        for (j = 7; j >= 0; j--) {
            for (i = 0; i <= j; i++) {
                dat_D = (1 << i) | tempo;  
                PORTD = dat_D;
                __delay_ms(500);  
            }
            tempo = dat_D;
        }
        PORTD = 0x00;
        __delay_ms(500);
    }
}
