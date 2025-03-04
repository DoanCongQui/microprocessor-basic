/*
 * File:   main.c
 * Author: dq
 *
 * Created on March 4, 2025, 2:34 PM
 */

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
#include "lcd.h"
#include <math.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000  
unsigned char push_count;

void import_port()
{
    ANSEL =ANSELH = 0;
    TRISE1 = 0;
    TRISE2 = 0;
    
    PORTE=0;
    TRISB = 0x07;
    nRBPU = 0;
    WPUB = 0x07;
    
    IOCB = 0x07;
    
    RBIF = 0;
    RBIE = 1;
    GIE = 1;
    
    PORTB;
}

void main(void) {
    PORTB = 0x07;
    import_port();
    push_count = 0;
    lcd_init();
    lcd_gotoxy(0, 0);
    lcd_puts("S1");
    lcd_gotoxy(0, 1); 
    lcd_puts("00"); 
    lcd_gotoxy(7, 0);
    lcd_puts("S2");
    lcd_gotoxy(7, 1); 
    lcd_puts("00"); 
    lcd_gotoxy(14, 0);
    lcd_puts("S3");
    lcd_gotoxy(14, 1); 
    lcd_puts("00"); 
    while(1);
}

void __interrupt() isr(void)
{
    PORTB;
    RBIF = 0;
    char data_1[4];
    char data_2[4];
    char data_3[4];
    __delay_ms(50);
    
    if (!RB0)
    {
        push_count++;
        if(push_count>10) {push_count=0;}
        lcd_gotoxy(0, 1);
        sprintf(data_1, "%.2d", push_count);
        lcd_puts(data_1);
    }
    
    if (!RB1)
    {
        push_count++;
        if(push_count>10) {push_count=0;}
        lcd_gotoxy(7, 1);
        sprintf(data_2, "%.2d", push_count);
        lcd_puts(data_2);
    }
    
    if (!RB2)
    {
        push_count++;
        if(push_count>10) {push_count=0;}
        lcd_gotoxy(14, 1);
        sprintf(data_3, "%.2d", push_count);
        lcd_puts(data_3);
    }
}

