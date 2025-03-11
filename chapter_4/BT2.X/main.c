/*
 * File:   main.c
 * Author: dq
 *
 * Created on March 11, 2025, 2:15 PM
 */

// CONFIG 1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#define _XTAL_FREQ 4000000

void CGRAM();
void import_port();

const char dat_line1[] = {'Q','u', 0x00,' ','C','o','u','n','t','e','r',' ','1'}; 
const char cgram_dat[] = {
    2, 4, 0, 12, 4, 4, 14, 0, // í --
    0x99};

void main()
{       
    char data[4];
    import_port();
    lcd_init(); 
    CGRAM();
    lcd_putc('\f'); 
    lcd_gotoxy(2, 0);
    for(int i = 0 ;i <= sizeof(dat_line1)-1; i++){ lcd_putc(dat_line1[i]);}
    lcd_gotoxy(8, 1); 
    lcd_puts("00"); 
    while(1){
        if(TMR1 > 30) TMR1 = 0;
        sprintf(data, "%.2d", TMR1);
        lcd_gotoxy(8, 1); 
        lcd_puts(data); 
    }
    
}

void CGRAM()
{
    unsigned char i;
    i = 0;
    lcd_put_byte(0,0x40); 
    while(lcd_busy()); 
    while(cgram_dat[i]!=0x99) 
    { 
        lcd_put_byte(1,cgram_dat[i]); 
        while(lcd_busy()); 
        i++;
    }
}

void import_port()
{
    ANSEL = ANSELH = 0x00;
    
    TRISC0 = 1;
    TMR1=0;
    TMR1IF=0;
    TMR1CS=1;
    T1OSCEN=0;
    GIE=PEIE=TMR1IE=0;
    T1CKPS1=0; T1CKPS0=0;
    T1SYNC=0;
    TMR1ON=1;
}



