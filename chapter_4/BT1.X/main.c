/*
 * File:   main.c
 * Author: dq
 *
 * Created on March 11, 2025, 2:06 PM
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

void delay100us(unsigned int n);
void import_port();

void main()
{
    char data[4];
    import_port();
    lcd_init();
    lcd_gotoxy(2, 0);
    lcd_puts("QUI Counter 0");
    lcd_gotoxy(8, 1); 
    lcd_puts("00"); 
    
    while(1){
       
        if(!RA4)
        {
            delay100us(1500);
            while(!RA4){
                delay100us(1500);
                if(TMR0 > 25) TMR0 = 0;
                sprintf(data, "%.2d", TMR0);
                lcd_gotoxy(8, 1); 
                lcd_puts(data);
            }
            
         }
           
    }
}

void import_port()
{
    ANSEL = ANSELH = 0;

    TRISA4 = 1;
    TMR0  = 0;
    TMR0IF =0;
    T0CS = 1;
    GIE = PEIE = TMR0IE = 0;
    PSA = 1; PS2=PS1=PS0=0; 
    T0SE = 1;
}


void delay100us(unsigned int n)
{ 
    while(n--) 
    {
        TMR1H= 255; TMR1L= 231;
        TMR1IF = 0;//xóa c? ng?t
        TMR1CS = 0; //ch? ?? ??nh th?i
        GIE=PEIE =TMR1IE = 0;// c?m ng?t
        T1CKPS1 = 1; T1CKPS0 = 0;//prescaler= 4
        TMR1ON = 1; //cho phép Timer 1 ho?t ??ng
        T1SYNC=1; //không ??ng b? xung ck
        while(TMR1IF==0); 
    }
}
