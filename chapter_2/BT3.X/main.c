/*
 * File:   main.c
 * Author: dq
 *
 * Created on February 27, 2025, 5:00 PM
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

#define _XTAL_FREQ 4000000  

void CGRAM();
void _Delay(unsigned char n);

const char dat_line1[] = {0x00,'o',0x03,'n',' ','C',0x04,'n','g',' ','Q','u',0x05}; 
const char dat_line2[] = "\nMSSV: 22696151"; 
const char dat_line3[] = "NgS: 01-12-2004\n";
const char dat_line4[] = {'N',0x06,'i','S', ':', ' ', 'B',0x01, 'n',' ', 'T', 'r', 'e'};
const char dat_line5[] = {'H','K','T','T',':',' ','B','T','r','i','-','B','T','r','e'};
const char dat_line6[] = {'L',0x02,'p',':',' ', 0x00, 'H',0x00,'T','M','T','1','8','A','T','T'};
const char cgram_dat[] = {
    0X0E,0X09,0X09,0X1D,0X09,0X09,0X0E,0X00, // Ð
    1, 10, 20, 8, 20, 28, 16, 12, // ?
    8, 22, 2, 12, 18, 18, 12, 0, // ?
    2, 1, 14, 1, 15, 17, 15, 0 , // à
    12, 18, 12, 18, 18, 18, 12, 0,  // ô 
    2, 4, 0, 12, 4, 4, 14, 0, // í
    0, 6, 2, 12, 18, 18, 12, 0, // ?
    0x99 };

void main(void) {
    unsigned char i,j;
    
    lcd_init(); 
    CGRAM();
    lcd_putc('\f');
    while(1){
        /*
         ==========================
         *         LCD 1          *
         ==========================
         */
        for(i = 0; i<3; i++)
        {
            for(j=0; j<=12; j++) {lcd_putc(dat_line1[j]);}
            lcd_puts(dat_line2);
            __delay_ms(700);
            lcd_putc('\f');
            __delay_ms(700);
        }
        lcd_putc('\f');
        
        /*
         ==========================
         *         LCD 2          *
         ==========================
         */
        lcd_gotoxy(0,0); 
        for(i=0; i<=14; i++) {lcd_putc(dat_line3[i]);}
        lcd_gotoxy(0,1);
        for(i=0; i<=12; i++) {lcd_putc(dat_line4[i]);}
        __delay_ms(2000);
        for (int i = 0; i < 17; i++) {
            lcd_ShiftLeft();
            __delay_ms(200);
        }
        lcd_puts("\f");

        /*
         ==========================
         *         LCD 3          *
         ==========================
         */
        for(i=0;i<=14;i++) {lcd_putc(dat_line5[i]);}
        lcd_putc('\n');
        for(i=0;i<=16;i++) {lcd_putc(dat_line6[i]);}
        __delay_ms(2000);
        for (int i = 0; i < 17; i++) {
            lcd_ShiftRight();
            __delay_ms(200);
        }
        lcd_putc('\f');
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