/*
 * File:   main.c
 * Author: dq
 *
 * Created on March 11, 2025, 3:36 PM
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
void delay100us(unsigned int n);

const char dat_line1[] = {'B',0x02,'i',' ','T',0x00,'p',' ','T','i','m','e','r',' ', '0'};

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

void main()
{       
    char data[4];
    unsigned char j;
    import_port();
    lcd_init(); 
    CGRAM();
    lcd_putc('\f'); 
    while(1)
    {
        for(j = 0; j<3; j++)
        {
            lcd_gotoxy(0, 0);
            for(int i = 0 ;i < sizeof(dat_line1); i++){ lcd_putc(dat_line1[i]);}
            lcd_gotoxy(0, 1); 
            for(int i = 0 ;i < sizeof(dat_line2); i++){ lcd_putc(dat_line2[i]);} 
            delay100us(7000);
            lcd_putc('\f');
            delay100us(7000);
        }
        lcd_putc('\f');
        
        for(j = 0; j<2; j++)
        {
            lcd_gotoxy(0, 0);
            for(int i = 0 ;i < sizeof(dat_line1); i++){ lcd_putc(dat_line1[i]);}
            lcd_gotoxy(0, 1); 
            for(int i = 0 ;i < sizeof(dat_line2); i++){ lcd_putc(dat_line2[i]);} 
            delay100us(20000);
            for (int i = 0; i < 17; i++) {
            lcd_ShiftLeft();
            __delay_ms(200);
            }
            lcd_puts("\f");
        }
        
        for(j = 0; j<2; j++)
        {
            lcd_gotoxy(0, 0);
            for(int i = 0 ;i < sizeof(dat_line1); i++){ lcd_putc(dat_line1[i]);}
            lcd_gotoxy(0, 1); 
            for(int i = 0 ;i < sizeof(dat_line2); i++){ lcd_putc(dat_line2[i]);} 
            delay100us(20000);
            for (int i = 0; i < 17; i++) {
            lcd_ShiftRight();
            __delay_ms(200);
            }
            lcd_puts("\f");
        }
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

// Timer 1
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