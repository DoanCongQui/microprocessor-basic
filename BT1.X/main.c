/*
 * File:   main.c
 * Author: dq
 *
 * Created on February 12, 2025, 9:48 PM
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

void _8_LED();
void LED_SANG_DUOI();
void _8_LED_SANG_DUOI_BIT();
void _16_LED_SANG_DUOI_ARRAY();
void _16_LED_SANG_DUOI_BIT();

void main(void) {
    TRISC = 0x00;
    TRISD = 0x00;
//    _8_LED_SANG_DUOI();
    while(1)
    {
        _16_LED_SANG_DUOI_BIT();
    }
}

void _8_LED()
{
   unsigned int i;
   for(i = 0; i < 100; i++) 
   {
        PORTD=0x00;
        __delay_ms(100);   // Delay 0.1s

        PORTD=0xFF;
        __delay_ms(100);    
    }
}

void _8_LED_SANG_DUOI_BIT()
{
    unsigned int i;
    PORTC = 0x00;
    for(i = 0; i < 8; i++) 
    {
        PORTD=(unsigned char)(0x80 >> i);
        __delay_ms(100);   // Delay 0.1s   
    }
}

void LED_SANG_DUOI()  
{  
    PORTC = 0x80;  // = 1 0 0 0 0 0 0 0  
    __delay_ms(100);  

    PORTC = 0x40;  // = 0 1 0 0 0 0 0 0  
    __delay_ms(100);  

    PORTC = 0x20;  // = 0 0 1 0 0 0 0 0  
    __delay_ms(100);  

    PORTC = 0x10;  // = 0 0 0 1 0 0 0 0  
    __delay_ms(100);  

    PORTC = 0x08;  // = 0 0 0 0 1 0 0 0  
    __delay_ms(100);  

    PORTC = 0x04;  // = 0 0 0 0 0 1 0 0  
    __delay_ms(100);  

    PORTC = 0x02;  // = 0 0 0 0 0 0 1 0  
    __delay_ms(100);  

    PORTC = 0x01;  // = 0 0 0 0 0 0 0 1  
    __delay_ms(100);  
    
}  

void _16_LED_SANG_DUOI_ARRAY()
{
    unsigned char DATA[]={ 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
    PORTC = 0;
    for (unsigned int i=0; i<8; i++)
    {
        PORTD = DATA[i];
        __delay_ms(100);
    }
    PORTD = 0;
    
    for (unsigned char i=0; i<8; i++)
    {
        PORTC = DATA[i];
        __delay_ms(100);
    }
    PORTC = 0;
}

void _16_LED_SANG_DUOI_BIT()
{
    unsigned int i;
    PORTC = 0x00;
    for(i = 0; i < 8; i++) 
    {
        PORTD=(unsigned char)(0x80 >> i);
        __delay_ms(100);   // Delay 0.1s   
    }
    PORTD = 0x00;
    
    for(i = 0; i < 8; i++) 
    {
        PORTC=(unsigned char)(0x80 >> i);
        __delay_ms(100);   // Delay 0.1s   
    }
    PORTC = 0x00;
}


