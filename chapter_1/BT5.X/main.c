/*
 * File:   main.c
 * Author: dq
 *
 * Created on February 26, 2025, 2:07 PM
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
#include <stdio.h>

#define _XTAL_FREQ 4000000      //Thach Anh 4MHz

void _16_LED_CT(unsigned char n);
void _16_LED_SANG_DUOI(unsigned char n);
void _16_LED_SANG_DAN(unsigned char n);
void Run(unsigned char n);

void main(void) {
    Run(2);
}

void _16_LED_CT(unsigned char n)
{
    while(n--)
    {
        PORTC = 0xFF;
        PORTD = 0xFF;
        __delay_ms(300);
        PORTC = 0x00;
        PORTD = 0x00;
        __delay_ms(300);
    }
}

void _16_LED_SANG_DUOI(unsigned char n)
{
    unsigned int i;
    PORTC = 0x00;
    while(n--){
        for(i = 0; i < 8; i++) 
        {
            PORTD=(unsigned char)(0x80 >> i);
            __delay_ms(300);   // Delay 0.1s   
        }
        PORTD = 0x00;
        for(i = 0; i < 8; i++) 
        {
            PORTC=(unsigned char)(0x80 >> i);
            __delay_ms(300);   // Delay 0.1s   
        }
        PORTC = 0x00;
    }
}

void _16_LED_SANG_DAN(unsigned char n)
{
    PORTD = 0x00;
    PORTC = 0x00;
    unsigned int i;
    while(n--)
    {
        for(i = 0; i < 8; i++) 
        {
            PORTC = PORTC | (0x01 << i);
            __delay_ms(100);
        }
        PORTC = 0xFF;
        PORTD = 0x00;
        for(i = 0; i < 8; i++) 
        {
            PORTD = PORTD | (0x01 << i);
            __delay_ms(100);
        }
    }
}

void Run(unsigned char n)
{
    TRISC = 0x00;
    TRISD = 0x00;
    while(n--)
    {
        _16_LED_CT(4);
        _16_LED_SANG_DUOI(2);
        _16_LED_SANG_DAN(3);
    }
    PORTC = 0xFF;
    PORTD = 0xFF;
    __delay_ms(300);
    PORTC = 0x00;
    PORTD = 0x00;
    while(1);
}
