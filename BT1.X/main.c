#include <xc.h>

#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = ON      
#pragma config CP = OFF         
#pragma config CPD = OFF       
#pragma config BOREN = OFF      
#pragma config IESO = OFF       
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        
#pragma config DEBUG = OFF     

#define _XTAL_FREQ 4000000      //Thach Anh 4MHz

void main(void) {
    TRISD=0b00000000;

    while (1) {
        PORTD=0x00;
        __delay_ms(500);   // Delay 0.5s

        PORTD=0xFF;
        __delay_ms(500);    
    }
}
