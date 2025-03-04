/*
 * File:   main.c
 * Author: dq
 *
 * Created on March 4, 2025, 1:59 PM
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
    TRISB0 = 1;
    nRBPU = 0;
    WPUB = 0x01;
    
    INTEDG = 1;
    INTF = 0;
    INTE = 1;
    GIE = 1;
}

void main(void) {
    import_port();
    push_count = 0;
    lcd_init();
    lcd_gotoxy(5, 0);
    lcd_puts("CONG QUI");
    lcd_gotoxy(8, 1); 
    lcd_puts("00"); 
    while(1);
}

void __interrupt() isr(void)
{
    INTF = 0;
    char data[4];
    __delay_ms(50);
    push_count++;
    
    if(push_count>20) {push_count=0;}
    lcd_gotoxy(8, 1);
    sprintf(data, "%.2d", push_count);
    lcd_puts(data); 
}

