/*
 * File:   main.c
 * Author: dq
 *
 * Created on March 4, 2025, 3:00 PM
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

void CGRAM();
void _8_LED_DUOI(unsigned char n);
void import_port();

const char dat_line1[] = {'B',0x02,'i',' ','T',0x00,'p',' ','N','g',0x01,'t'};

// Thay ??i tên //
const char dat_line2[] = {0x05,'o',0x02,'n',' ','C',0x03,'n','g',' ','Q','u',0x04}; 

const char cgram_dat[] = {
    4, 10, 6, 1, 7, 9, 15, 0, //? 
    4, 8, 6, 1, 7, 9, 15, 0 , // ?
    2, 1, 14, 1, 15, 17, 15, 0 , // à --
    
    // Thay ??i tên //
    12, 18, 12, 18, 18, 18, 12, 0,  // ô --
    2, 4, 0, 12, 4, 4, 14, 0, // í --
    0X0E,0X09,0X09,0X1D,0X09,0X09,0X0E,0X00, // Ð
    0x99 };

void main(void) {
    unsigned char j;
    lcd_init(); 
    CGRAM();
    lcd_putc('\f');
    import_port();
    PORTB;
    while(1)
    {
        lcd_gotoxy(2, 0);
        for(j=0; j<=11; j++) {lcd_putc(dat_line1[j]);}
        lcd_gotoxy(2, 1);
        for(j=0; j<=12; j++) {lcd_putc(dat_line2[j]);}
        __delay_ms(700);
        lcd_putc('\f');
        __delay_ms(700);
    }
}

void __interrupt() isr(void)
{
    PORTB;
    __delay_ms(50);
    _8_LED_DUOI(1);
//    while(1);
    INTF = 0;
    
}

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

void _8_LED_DUOI(unsigned char n){
    while(n--){
        TRISB = 0x20;
        PORTB = 0x08;
        __delay_ms(500);
        TRISB = 0x20;
        PORTB = 0x10;
        __delay_ms(500);
        TRISB = 0x08;
        PORTB = 0x10;
        __delay_ms(500);
        TRISB = 0x08;
        PORTB = 0x20;
        __delay_ms(500);
        TRISB = 0x10;
        PORTB = 0x20;
        __delay_ms(500);
        TRISB = 0x10;
        PORTB = 0x08;
        __delay_ms(500);
    }
    PORTB = 0x00;
    TRISB0 = 1;
}
